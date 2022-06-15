/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#include "OV7725.h"
#include "dcache-control.h"
#include "JPEG_Converter.h"
#include "OV7725Streamer.h"
#include "CRtspSession.h"

#include "SdhiConnect.hpp"
#include "FATFileSystem.h"
#include "USBMSD.h"
//#include  "rtx_lib.h"



/**** User Selection *********/
/** Network setting **/
#define USE_DHCP               1                 /* Select  0(static configuration) or 1(use DHCP) */
#if (USE_DHCP == 0)
  #define IP_ADDRESS           "192.168.0.2"     /* IP address      */
  #define SUBNET_MASK          "255.255.255.0"   /* Subnet mask     */
  #define DEFAULT_GATEWAY      "192.168.0.3"     /* Default gateway */
#endif

/** JPEG out setting **/
#define JPEG_ENCODE_QUALITY    75                /* JPEG encode quality (min:1, max:75 (Considering the size of JpegBuffer, about 75 is the upper limit.)) */
#define VFIELD_INT_SKIP_CNT    0                 /* A guide for GR-LYCHEE.  0:60fps, 1:30fps, 2:20fps, 3:15fps, 4:12fps, 5:10fps */
/*****************************/
#define DEFAULT_BLOCK_SIZE  512
#define HEAP_BLOCK_DEVICE_SIZE (162 * DEFAULT_BLOCK_SIZE)

#define LED_ON                 0
#define LED_OFF                1
#define BUTTON_PRESSED         0
#define BUTTON_RELEASED        1


#include "EthernetInterface.h"

EthernetInterface network;
DisplayBase Display;

HeapBlockDevice disk(HEAP_BLOCK_DEVICE_SIZE, DEFAULT_BLOCK_SIZE);
FATFileSystem ram("RAM");
USBMSD *usb = NULL;
SDHIConnect storage("SD");

#include "platglue.h"

DigitalOut led1(LED1, 0);
DigitalOut led2(LED2, 0);
InterruptIn button(BUTTON1);

DigitalOut TP2(D9, 0);
DigitalOut TP3(D10, 0);
DigitalOut TP4(D11, 0);

static uint8_t Jpeg[1024 * 64] __attribute__((section("NC_BSS"),aligned(32)));
static uint8_t JpegBuffer[2][1024 * 64] __attribute__((section("NC_BSS"),aligned(32)));
static VideoBuffer_t VideoBuffer[1] __attribute__((section("NC_BSS"),aligned(32)));

static JPEG_Converter Jcu;
static size_t JpegSIZE;
static size_t jcu_encode_size[2];
static int jcu_buf_index_write = 0;
static int jcu_buf_index_write_done = 0;
static int jcu_buf_index_read = 0;
static volatile int jcu_encoding = 0;
static volatile int image_change = 0;
static volatile int saveREQUEST = 0;
static volatile int saved = 0;
static uint8_t jpg_quality = JPEG_ENCODE_QUALITY;

static Thread mainTask(osPriorityNormal, OS_STACK_SIZE*8);

Thread t(osPriorityAboveNormal);
EventQueue jpg_queue;

/** Stream for the camera video */
CStreamer *streamer = NULL;
/** Session to handle the RTSP communication */
CRtspSession *session = NULL;

/** Camera class */
OV7725 cam;

static void BTNpressed_callback(void)
{
	if(!saved)
		saveREQUEST = 1;
}

static void USB_callback()
{
	jpg_queue.call(usb, &USBMSD::process);
}

void saveJPEG()
{
	if(usb && usb->configured())
	{
		FILE *fp;

		usb->disconnect();
		delay(200);
		fp = fopen("/RAM/PIC_latest.jpg", "w+");
		if(fp)
		   fwrite(Jpeg, 1, JpegSIZE, fp);
		fclose(fp);
		delay(200);
		usb->connect();
	}

	if(storage.browsable())
	{
		FILE *fp;
	    char fname[50];
	    uint64_t STMP = Kernel::get_ms_count();

        snprintf(fname, sizeof(fname), "/SD/PIC_%llu.jpg", STMP);
        fp = fopen(fname, "w+");
        if(fp)
            fwrite(Jpeg, 1, JpegSIZE, fp);
        fclose(fp);
        printf("Saving Pic_%llu[%u]\r\n", STMP, JpegSIZE);
	}
	saved = 0;
}

void jpgFrameOver(void)
{
    jcu_buf_index_read = jcu_buf_index_write_done;

    if(saveREQUEST && !saved)
    {
    	JpegSIZE = jcu_encode_size[jcu_buf_index_read];
    	memcpy(Jpeg, JpegBuffer[jcu_buf_index_read], JpegSIZE);
    	saveREQUEST = 0;
    	saved = 1;
    }

    cam.setfb(&JpegBuffer[jcu_buf_index_read], jcu_encode_size[jcu_buf_index_read]);

    image_change = 1;

    TP2 = 0; TP3 = 1;
}

static void JcuEncodeCallBackFunc(JPEG_Converter::jpeg_conv_error_t err_code) {
    if (err_code == JPEG_Converter::JPEG_CONV_OK) {
    	jcu_buf_index_write_done = jcu_buf_index_write;

        jpg_queue.call(Callback<void()>(jpgFrameOver));

        if (jpg_quality < JPEG_ENCODE_QUALITY )
        {
        	Jcu.SetQuality(++jpg_quality);
        }
    }
    else
    {
		printf("Line %d, error %d\r\n", __LINE__, err_code);
        Jcu.SetQuality(jpg_quality=(2*JPEG_ENCODE_QUALITY)/3);
    }
    jcu_encoding = 0;
}

static void VFrame_callback()
{
    JPEG_Converter::bitmap_buff_info_t bitmap_buff_info;
    JPEG_Converter::encode_options_t   encode_options;

    bitmap_buff_info.width              = VIDEO_PIXEL_HW;
    bitmap_buff_info.height             = VIDEO_PIXEL_VW;
    bitmap_buff_info.format             = JPEG_Converter::WR_RD_YCbCr422;
    bitmap_buff_info.buffer_address     = cam.getvb();
    //bitmap_buff_info.buffer_address     = frame_gray.data;

    encode_options.encode_buff_size     = sizeof(JpegBuffer[0]);
    encode_options.p_EncodeCallBackFunc = &JcuEncodeCallBackFunc;
    encode_options.input_swapsetting    = JPEG_Converter::WR_RD_WRSWA_32_16_8BIT;

    jcu_encoding = 1;
    if (jcu_buf_index_read == jcu_buf_index_write) {
        jcu_buf_index_write ^= 1;  // toggle
    }
    jcu_encode_size[jcu_buf_index_write] = 0;
    //dcache_invalid(JpegBuffer[jcu_buf_index_write], sizeof(JpegBuffer[0]));
    if (Jcu.encode(&bitmap_buff_info, JpegBuffer[jcu_buf_index_write], &jcu_encode_size[jcu_buf_index_write], &encode_options) != JPEG_Converter::JPEG_CONV_OK)
    {
        jcu_encode_size[jcu_buf_index_write] = 0;
        jcu_encoding = 0;
    }
    else
    {
        TP2 = 1;
    }
    cam.swapvb();
}



static void Start_Video_Camera(void)
{
    // Initialize the background to black
    for (uint32_t i = 0; i < sizeof(VideoBuffer[0].frameBUF); i += 2) {
        VideoBuffer[0].frameBUF[i + 0] = 0x10;
        VideoBuffer[0].frameBUF[i + 1] = 0x80;

//        VideoBuffer[1].frameBUF[i + 0] = 0x80;
//        VideoBuffer[1].frameBUF[i + 1] = 0x10;
    }

    // Camera
    cam.Init(Display);
    cam.Start(DisplayBase::VIDEO_INPUT_CHANNEL_0, VideoBuffer, (sizeof(VideoBuffer)/sizeof(VideoBuffer[0])) > 1 );
    cam.Notify(VFrame_callback, 1);
}

static void main_task(void) {
    printf("********* PROGRAM START ***********\r\n");

    printf("Network Setting up...\r\n");

#if (USE_DHCP == 0)
    network.set_dhcp(false);
    if (network.set_network(IP_ADDRESS, SUBNET_MASK, DEFAULT_GATEWAY) != 0) { //for Static IP Address (IPAddress, NetMasks, Gateway)
        printf("Network Set Network Error \r\n");
    }
#endif

    printf("\r\nConnecting...\r\n");

    if (network.connect() != 0) {
        printf("Network Connect Error \r\n");
        return;
    }
    SocketAddress sa;
    printf("MAC Address is %s\r\n", network.get_mac_address());

    if ( network.get_ip_address(&sa) != NSAPI_ERROR_OK )
    {
    	printf ("Network Error : No Connection!\r\n");
    	return;
    }
    printf("IP Address is %s\r\n", sa.get_ip_address());

    if ( network.get_netmask(&sa) != NSAPI_ERROR_OK )
    {
    	printf ("Network Error : No Connection!\r\n");
    	return;
    }
    printf("NetMask is %s\r\n", sa.get_ip_address());

    if ( network.get_gateway(&sa) != NSAPI_ERROR_OK )
    {
    	printf ("Network Error : No Connection!\r\n");
    	return;
    }
    printf("Gateway Address is %s\r\n", sa.get_ip_address());
    printf("Network Setup OK\r\n");

    t.start(callback(&jpg_queue, &EventQueue::dispatch_forever));

    Jcu.SetQuality(jpg_quality=JPEG_ENCODE_QUALITY);

    Start_Video_Camera();

    printf("running RTSP server\r\n");

	//uint32_t msecPerFrame = 50;
	//static uint64_t lastimage = Kernel::get_ms_count();

    SOCKET rtspServer;
    SOCKET rtspClient = NULL;                                      // RTSP socket to handle an client

    rtspServer = new TCPSocket();

    rtspServer->open(&network);
    rtspServer->bind(8554);
    rtspServer->listen();

	while (true)
	{
		// If we have an active client connection, just service that until gone
		if (session)
		{
			session->handleRequests(0); // we don't use a timeout here,
			// instead we send only if we have new enough frames

			//uint64_t now = Kernel::get_ms_count();
			//if (now > lastimage + msecPerFrame || now < lastimage)
			if ( image_change )
			{ // handle clock rollover
			    jcu_buf_index_read = jcu_buf_index_write_done;
			    image_change = 0;

			    //int toSend = jcu_encode_size[jcu_buf_index_read];

			    //TP2 = 0;

				uint64_t now = Kernel::get_ms_count();

				session->broadcastCurrentFrame(now);
				TP3 = 0;
				//lastimage = now;
			}

			// Handle disconnection from RTSP client
			if (session->m_stopped)
			{
				printf("RTSP client closed connection\r\n");
				delete session;
				delete streamer;
				session = NULL;
				streamer = NULL;
				led1 = 0;
			}
		}
		else
		{
			rtspClient = rtspServer->accept();
			// Handle connection request from RTSP client
			if (rtspClient)
			{
				printf("RTSP client started connection\r\n");
				//streamer = new SimStreamer(rtspClient, true); // our streamer for UDP/TCP based RTP transport
				streamer = new OV7725Streamer(rtspClient, cam); // our streamer for UDP/TCP based RTP transport

				session = new CRtspSession(rtspClient, streamer); // our threads RTSP session and state
				led1 = 1;
				delay(100);
			}
		}
	}
}

int main(void)
{
	button.rise(BTNpressed_callback);
    mainTask.start(callback(main_task));

    disk.init();
    FATFileSystem::format(&disk);
    ram.mount(&disk);

    USBMSD msd(&disk);
    usb = &msd;
    msd.attach(USB_callback);

    while (true)
    {
    	storage.handleEvents(led2);
    	if(saved)
            saveJPEG();
    }
}
