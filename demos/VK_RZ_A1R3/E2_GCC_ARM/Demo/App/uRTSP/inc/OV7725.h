#ifndef OV7725_H_
#define OV7725_H_

#include <mbed.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "dcache-control.h"
#include "DisplayBace.h"

//video frame sync event flag
#define EVF_V_FRAME			   		(1ul << 1)
#define EVF_TERMINATE			   	(1ul << 9)

//Video buffer components
typedef union
{
	struct
	{
		uint16_t B : 5;
		uint16_t G : 6;
		uint16_t R : 5;
	} CLR;
	uint16_t 	data;
} RGB_pixel_t;

typedef union
{
	struct
	{
		uint8_t Y0;	//Y
		uint8_t U;	//Cb
		uint8_t Y1;	//Y
		uint8_t V;	//Cr
	} CMP;
	uint8_t 	dat[4];
	uint16_t	luma[2];
	uint32_t 	chroma;
	uint32_t    data;
} YUY2_macropixel_t;


#define VIDEO_FRAME(name, w, h, p)				\
union											\
{												\
	uint8_t 			frameBUF[w*h*p];		\
	RGB_pixel_t			RGB[w*h];               \
	RGB_pixel_t         RGB_2D[h][w];           \
	YUY2_macropixel_t	YUY2[(w*h)/2];		    \
	YUY2_macropixel_t	YUY2_2D[h][w/2];	    \
	uint16_t			lumaPLANE[w*h];			\
	uint16_t			lumaPLANE_2D[h][w];		\
	uint32_t			chromaPLANE[(w*h)/2];	\
	uint32_t			chromaPLANE_2D[h][w/2];	\
} name

/* Video input and LCD layer 0 output */
#define VIDEO_FORMAT           (DisplayBase::VIDEO_FORMAT_YCBCR422)
#define GRAPHICS_FORMAT        (DisplayBase::GRAPHICS_FORMAT_YCBCR422)
#define WR_RD_WRSWA            (DisplayBase::WR_RD_WRSWA_32_16BIT)
#define DATA_SIZE_PER_PIC      (2u)

#define CAM_PIXEL_WIDTH     640
#define CAM_PIXEL_HEIGHT    480

#define VIDEO_PIXEL_HW       CAM_PIXEL_WIDTH
#define VIDEO_PIXEL_VW       CAM_PIXEL_HEIGHT

//#define VIDEO_PIXEL_HW       (320u)  /* VGA */
//#define VIDEO_PIXEL_VW       (240u)  /* VGA */

#define FRAME_BUFFER_STRIDE    (((VIDEO_PIXEL_HW * DATA_SIZE_PER_PIC) + 31u) & ~31u)
#define FRAME_BUFFER_HEIGHT    (VIDEO_PIXEL_VW)

#define OV7725_I2C_SLAVE_ADDR	(0x42)

#define CAM_SCL 	P1_6
#define CAM_SDA		P1_7

//pixel size in bytes
#define CAMPIX_DATA_SIZE_BYTES    2u

typedef VIDEO_FRAME(VideoBuffer_t, VIDEO_PIXEL_HW, VIDEO_PIXEL_VW, DATA_SIZE_PER_PIC);

typedef struct {
	int height;
	int width;
	size_t size;
	uint8_t * buf;
} camera_fb_t;

class OV7725 : public Thread, private NonCopyable<OV7725>
{
public:
	OV7725()
	: Thread(osPriorityRealtime, OS_STACK_SIZE*2)
    , _irqVframe(this)
	, _cb_Vframe(this)
	, _notify(NULL)
	{
		_display = NULL;
		_pVbuff = NULL;
		_channel = DisplayBase::VIDEO_INPUT_CHANNEL_0;
	    _everyXframe = 0;
	    _vframe_count = 0;
	    _idxVidBuff = 0;
	    _bSwapable = false;

	    fb = new camera_fb_t;
	    fb->height = VIDEO_PIXEL_VW;
	    fb->width = VIDEO_PIXEL_HW;
	    fb->buf = NULL;
	    fb->size = 0;
    };
    virtual ~OV7725(){
    	_ev_flags.set(EVF_TERMINATE);
    	join();
    	delete fb;
    };

    size_t getSize(void) { return fb->size; }
    uint8_t *getfb(void) { return fb->buf; }
    int getWidth(void) const { return fb->width; }
    int getHeight(void) const { return fb->height;  }

    DisplayBase::graphics_error_t Init(DisplayBase& Display, uint16_t cap_width=0, uint16_t cap_height=0);
    virtual void SetExtInConfig(DisplayBase::video_ext_in_config_t * p_cfg);
    DisplayBase::graphics_error_t Start(DisplayBase::video_input_channel_t channel, VideoBuffer_t * pVBuf, bool bSwapable=false);
    void Notify( Callback<void()> func, uint16_t e ) { _notify = func; _everyXframe = e; }
    void swapvb(void);
    void * getvb(void);

    void setfb( void * jpgfb, size_t size ) { fb->buf = (uint8_t *)jpgfb; fb->size = size; }

protected:

    void IntCallbackFunc_Vfield(void);
    void OnVFrame(void);

    virtual bool Initialize();

    VideoBuffer_t * _pVbuff;

    /* Interrupt */
    CThunk<OV7725> _irqVframe;

    /* callback */
    CThunk<OV7725> _cb_Vframe;

    Callback<void()>  _notify;

private:
    static const PinName _camera_pin[];
    static const char _InitRegTable[][2];

    DisplayBase *    _display;

    DisplayBase::video_input_channel_t _channel;

    EventFlags _ev_flags;

    uint8_t _everyXframe;
    uint32_t _vframe_count;
    uint8_t _idxVidBuff;
    bool _bSwapable;

    camera_fb_t * fb;
};

#endif //OV7725_H_
