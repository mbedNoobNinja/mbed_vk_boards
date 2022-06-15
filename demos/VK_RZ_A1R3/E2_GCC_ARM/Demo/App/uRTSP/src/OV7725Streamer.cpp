
#include "OV7725Streamer.h"
#include <assert.h>



OV7725Streamer::OV7725Streamer(SOCKET aClient, OV7725 &cam) : CStreamer(aClient, cam.getWidth(), cam.getHeight()), _cam(cam)
{
    printf("Created streamer width=%d, height=%d\r\n", cam.getWidth(), cam.getHeight());
}

void OV7725Streamer::streamImage(uint32_t curMsec)
{
    //_cam.run();// queue up a read for next time

    BufPtr bytes = _cam.getfb();
    streamFrame(bytes, _cam.getSize(), curMsec);
}
