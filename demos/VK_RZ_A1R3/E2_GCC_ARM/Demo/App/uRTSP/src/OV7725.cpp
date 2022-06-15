#include "OV7725.h"


#define TAG "OV7725"


DigitalOut TP1(D8, 0);

const PinName OV7725::_camera_pin[] = {
        /* data pin */
        P6_12, P6_13, P6_14, P6_15, P1_8, P1_9, P1_10, P1_11,
        /* control pin */
        P7_8,       /* DV0_CLK   */
        P7_9,       /* DV0_Vsync */
        P7_10       /* DV0_Hsync */
    };

const char OV7725::_InitRegTable[][2] = {
    {0x0D, 0x41}, /* COM4 */
    {0x0F, 0xC5}, /* COM6 */
#if 0 /* 30fps(24MHz) */
    {0x11, 0x01}, /* CLKRC */
#else /* 60fps(48MHz) */
    {0x11, 0x00}, /* CLKRC */
#endif
    {0x14, 0x1F}, /* COM9 Drop VSYNC/HREF */
    {0x15, 0x40}, /* COM10 HSYNC*/
    {0x17, 0x22}, /* HSTART */
    {0x18, 0xA4}, /* HSIZE */
    {0x19, 0x07}, /* VSTRT */
    {0x1A, 0xF0}, /* VSIZE */
    {0x22, 0x99}, /* BDBase */
    {0x23, 0x02}, /* BDMStep */
    {0x24, 0x60}, /* AEW */
    {0x25, 0x50}, /* AEB */
    {0x26, 0xA1}, /* VPT */
    {0x29, 0xA0}, /* HOutSize */
    {0x2A, 0x00}, /* EXHCH */
    {0x2B, 0x00}, /* EXHCL */
    {0x2C, 0xF0}, /* VOutSize */
    {0x32, 0x00}, /* HREF */
    {0x33, 0x01}, /* DM_LNL */
    {0x3D, 0x03}, /* COM12 */
    {0x42, 0x7F}, /* TGT_B */
    {0x4D, 0x09}, /* FixGain */
    {0x63, 0xE0}, /* AWB_Ctrl0 */
    {0x64, 0xFF}, /* DSP_Ctrl1 */
    {0x65, 0x20}, /* DSP_Ctrl2 */
    {0x66, 0x00}, /* DSP_Ctrl3 */
    {0x67, 0x48}, /* DSP_Ctrl4 */
    {0x6B, 0xAA}, /* AWBCtrl3 */
    {0x7E, 0x04}, /* GAM1 */
    {0x7F, 0x0E}, /* GAM2 */
    {0x80, 0x20}, /* GAM3 */
    {0x81, 0x43}, /* GAM4 */
    {0x82, 0x53}, /* GAM5 */
    {0x83, 0x61}, /* GAM6 */
    {0x84, 0x6D}, /* GAM7 */
    {0x85, 0x76}, /* GAM8 */
    {0x86, 0x7E}, /* GAM9 */
    {0x87, 0x86}, /* GAM10 */
    {0x88, 0x94}, /* GAM11 */
    {0x89, 0xA1}, /* GAM12 */
    {0x8A, 0xBA}, /* GAM13 */
    {0x8B, 0xCF}, /* GAM14 */
    {0x8C, 0xE3}, /* GAM15 */
    {0x8D, 0x26}, /* SLOP */
    {0x90, 0x05}, /* EDGE1 */
    {0x91, 0x01}, /* DNSOff */
    {0x92, 0x05}, /* EDGE2 */
    {0x93, 0x00}, /* EDGE3 */
    {0x94, 0x80}, /* MTX1 */
    {0x95, 0x7B}, /* MTX2 */
    {0x96, 0x06}, /* MTX3 */
    {0x97, 0x1E}, /* MTX4 */
    {0x98, 0x69}, /* MTX5 */
    {0x99, 0x86}, /* MTX6 */
    {0x9A, 0x1E}, /* MTX_Ctrl */
    {0x9B, 0x00}, /* BRIGHT */
    {0x9C, 0x20}, /* CNST */
    {0x9E, 0x81}, /* UVADJ0 */
    {0xA6, 0x04}, /* SDE */
};

bool OV7725::Initialize()
{
    char sw_reset_cmd[2] = {0x12, 0x80};
    int ret;
    I2C mI2c_(CAM_SDA, CAM_SCL);
    mI2c_.frequency(150000);

    if (mI2c_.write(OV7725_I2C_SLAVE_ADDR, sw_reset_cmd, sizeof(sw_reset_cmd)) != 0) {
        return false;
    }
    ThisThread::sleep_for(1);

    for (uint32_t i = 0; i < (sizeof(_InitRegTable) / sizeof(_InitRegTable[0])) ; i++) {
        ret = mI2c_.write(OV7725_I2C_SLAVE_ADDR, _InitRegTable[i], sizeof(_InitRegTable[i])/sizeof(_InitRegTable[i][0]));
        if (ret != 0) {
            return false;
        }
    }

    return true;
}


void OV7725::SetExtInConfig(DisplayBase::video_ext_in_config_t * p_cfg) {
    p_cfg->inp_format     = DisplayBase::VIDEO_EXTIN_FORMAT_BT601; /* BT601 8bit YCbCr format */
    p_cfg->inp_pxd_edge   = DisplayBase::EDGE_RISING;              /* Clock edge select for capturing data          */
    p_cfg->inp_vs_edge    = DisplayBase::EDGE_RISING;              /* Clock edge select for capturing Vsync signals */
    p_cfg->inp_hs_edge    = DisplayBase::EDGE_RISING;              /* Clock edge select for capturing Hsync signals */
    p_cfg->inp_endian_on  = DisplayBase::OFF;                      /* External input bit endian change on/off       */
    p_cfg->inp_swap_on    = DisplayBase::OFF;                      /* External input B/R signal swap on/off         */
    p_cfg->inp_vs_inv     = DisplayBase::SIG_POL_NOT_INVERTED;     /* External input DV_VSYNC inversion control     */
    p_cfg->inp_hs_inv     = DisplayBase::SIG_POL_NOT_INVERTED;     /* External input DV_HSYNC inversion control     */
    p_cfg->inp_f525_625   = DisplayBase::EXTIN_LINE_525;           /* Number of lines for BT.656 external input */
    p_cfg->inp_h_pos      = DisplayBase::EXTIN_H_POS_YCBYCR;       /* Y/Cb/Y/Cr data string start timing to Hsync reference */
    p_cfg->cap_vs_pos     = 4+21;                                  /* Capture start position from Vsync */
    p_cfg->cap_hs_pos     = 68;                                    /* Capture start position form Hsync */
    p_cfg->cap_width      = CAM_PIXEL_WIDTH;                       /* Capture width Max */
    p_cfg->cap_height     = CAM_PIXEL_HEIGHT;                      /* Capture height Max */
}


DisplayBase::graphics_error_t OV7725::Init(DisplayBase& Display, uint16_t cap_width, uint16_t cap_height)
{
    DisplayBase::graphics_error_t error;
    DisplayBase::video_input_sel_t video_input_sel;

    DigitalOut pwdn(P6_11);
    DigitalOut rstb(P7_11);

    pwdn = 0;
    rstb = 0;
    ThisThread::sleep_for(10 + 1);
    rstb = 1;
    ThisThread::sleep_for(1 + 1);

    _display = &Display;

    error = _display->Graphics_init(NULL);
    if (error != DisplayBase::GRAPHICS_OK) {
        printf("Line %d, error %d\n", __LINE__, error);
        return error;
    }

#if CAMERA_MODULE == MODULE_VDC
  video_input_sel = DisplayBase::INPUT_SEL_EXT;
  error = _display->Graphics_Dvinput_Port_Init((PinName *)_camera_pin, sizeof(_camera_pin)/sizeof(_camera_pin[0]));
#elif CAMERA_MODULE == MODULE_CEU
  video_input_sel = DisplayBase::INPUT_SEL_CEU;
  error = Display.Graphics_Ceu_Port_Init(cmos_camera_pin, sizeof(cmos_camera_pin)/sizeof(cmos_camera_pin[0]));
#endif
  if( error != DisplayBase::GRAPHICS_OK) {
      printf("Line %d, error %d\n", __LINE__, error);
      return error;
  }

  DisplayBase::video_ext_in_config_t ext_in_config;

  Initialize();
  SetExtInConfig(&ext_in_config);

  if (cap_width != 0) {
      ext_in_config.cap_width  = cap_width;                             /* Capture width */
  }
  if (cap_height != 0) {
      ext_in_config.cap_height = cap_height;                            /* Capture height */
  }

  error = _display->Graphics_Video_init(video_input_sel, &ext_in_config);

  if( error != DisplayBase::GRAPHICS_OK ) {
      printf("Line %d, error %d\n", __LINE__, error);
      return error;
  }

  return DisplayBase::GRAPHICS_OK;
}

DisplayBase::graphics_error_t OV7725::Start(DisplayBase::video_input_channel_t channel, VideoBuffer_t * pvB, bool bSwapable)
{
    // Video capture setting (progressive form fixed)

	if (!_display || !pvB)
		return DisplayBase::GRAPHICS_VDC5_ERR;

	_pVbuff = pvB;
	_bSwapable = bSwapable;

    _channel = channel;

    _display->Video_Write_Setting(
    	_channel,
        DisplayBase::COL_SYS_NTSC_358,
		(void*)&_pVbuff[_idxVidBuff = 0].frameBUF,
        FRAME_BUFFER_STRIDE,
        VIDEO_FORMAT,
        WR_RD_WRSWA,
        VIDEO_PIXEL_VW,
        VIDEO_PIXEL_HW
    );
    // Interrupt callback function setting (Field end signal for recording function in scaler 0)
    _irqVframe.callback(&OV7725::IntCallbackFunc_Vfield);
    _display->Graphics_Irq_Handler_Set(DisplayBase::INT_TYPE_S0_VFIELD, 0, (void (*)(DisplayBase::int_type_t))_irqVframe.entry());

    _cb_Vframe.callback(&OV7725::OnVFrame);
    start( (void (*)())_cb_Vframe.entry());

    DisplayBase::graphics_error_t error;

    /* Video write process start */
    error = _display->Video_Start(_channel);
    if (error != DisplayBase::GRAPHICS_OK) {
        printf("Line %d, error %d\n", __LINE__, error);
        return error;
    }

  #if CAMERA_MODULE == MODULE_VDC
    /* Video write process stop */
    error = _display->Video_Stop(_channel);
    if (error != DisplayBase::GRAPHICS_OK) {
        printf("Line %d, error %d\n", __LINE__, error);
        return error;
    }

    /* Video write process start */
    error = _display->Video_Start(_channel);
    if (error != DisplayBase::GRAPHICS_OK) {
        printf("Line %d, error %d\n", __LINE__, error);
        return error;
    }
  #endif

    return DisplayBase::GRAPHICS_OK;
}

//void OV7725::IntCallbackFunc_Vfield(DisplayBase::int_type_t int_type)
void OV7725::IntCallbackFunc_Vfield(void)
{
    if (_vframe_count > 0)
    {
    	_vframe_count--;
    }
    else
    {
    	TP1 = 1;
    	_ev_flags.set(EVF_V_FRAME);

        if(_everyXframe)
        	_vframe_count = _everyXframe;
    }
}

void OV7725::OnVFrame(void)
{
	bool running = true;
	uint32_t flags_read;
	while (running)
	{
		flags_read = _ev_flags.wait_any(EVF_V_FRAME | EVF_TERMINATE);

		switch (flags_read)
		{
		case EVF_V_FRAME :
			if ( _notify )
				_notify.call();
	    	TP1 = 0;
			break;
		case EVF_TERMINATE :
			running = false;
			break;
		default:
			printf ("Got Unexpected Event!\r\n");
			break;
		}
	}
}


void * OV7725::getvb(void)
{
	if (_bSwapable)
		return (void*)&_pVbuff[_idxVidBuff ? 0 : 1].frameBUF;
	else
		return (void*)&_pVbuff[_idxVidBuff].frameBUF;
}

void OV7725::swapvb(void)
{
	if ( _bSwapable && _display )
	{
		core_util_critical_section_enter();
		DisplayBase::graphics_error_t error;
		//dcache_invalid((_pVbuff)[_idxVidBuff? 0 : 1].frameBUF, sizeof((_pVbuff)[_idxVidBuff? 0 : 1].frameBUF));
		if ((error = _display->Video_Write_Change(_channel, _pVbuff[(_idxVidBuff = _idxVidBuff? 0 : 1)].frameBUF, FRAME_BUFFER_STRIDE)) != DisplayBase::GRAPHICS_OK)
			printf("Line %d, error %d\n", __LINE__, error);
		core_util_critical_section_exit();
	}

}


