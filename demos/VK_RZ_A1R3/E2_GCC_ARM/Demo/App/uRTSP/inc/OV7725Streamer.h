#pragma once

#include "CStreamer.h"
#include "OV7725.h"

class OV7725Streamer : public CStreamer
{
    //bool m_showBig;
    OV7725 &_cam;

public:
    OV7725Streamer(SOCKET aClient, OV7725 &cam);

    virtual void    streamImage(uint32_t curMsec);
};
