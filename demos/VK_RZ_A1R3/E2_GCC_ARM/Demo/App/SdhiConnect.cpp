#include "SdhiConnect.hpp"
#include "iodefine.h"
#include "rza_io_regrw.h"

#define  SDHI1_SDINFO1_INFO3                 (0x0008u)
#define  SDHI1_SDINFO1_INFO4                 (0x0010u)
#define  SDHI1_SDINFO1_INFO5                 (0x0020u)

#define  SDHI1_SDINFO1_INFO3_SHIFT           (3u)
#define  SDHI1_SDINFO1_INFO4_SHIFT           (4u)
#define  SDHI1_SDINFO1_INFO5_SHIFT           (5u)

SDHIConnect::SDHIConnect(const char *name) : _fs(name), _sd(MBED_CONF_SDHI_CH)
{
	_bInserted = false;
	_bBrowsable = false;
}

bool SDHIConnect::inserted()
{
	_bInserted = checkSlot();
    return _bInserted;
}

bool SDHIConnect::checkSlot()
{
    return (RZA_IO_RegRead_16(MBED_CONF_SDHI_CH? &SDHI1.SD_INFO1 : &SDHI0.SD_INFO1, SDHI1_SDINFO1_INFO5_SHIFT, SDHI1_SDINFO1_INFO5))? true : false;
}

bool SDHIConnect::format(int allocation_unit)
{
    if (checkSlot())
    {
        _fs.unmount();
        _fs.format(&_sd, allocation_unit);
        _fs.mount(&_sd);
        return true;
    }
    return false;
}

bool SDHIConnect::connect()
{
    if(inserted() && !_bBrowsable)
    {
    	_sd.init();
    	_bBrowsable = (_fs.mount(&_sd))? false : true;
        return _bBrowsable;
    }

    return false;
}

bool SDHIConnect::disconnect() {
	if(!inserted() && _bBrowsable)
	{
        _bBrowsable = (_fs.unmount())? true : false;
        _sd.deinit();
        return !_bBrowsable;
    }
	else
		return false;
}

void SDHIConnect::wait_connect(void)
{
    while(!connect()) {
        ThisThread::sleep_for(100ms);
    }
}

bool SDHIConnect::browsable()
{
	return (_bInserted && _bBrowsable);
}

void SDHIConnect::handleEvents(DigitalOut& led)
{
	bool cd = checkSlot();

	if(cd != _bInserted)
	{
		if(cd)
		{
			if(connect())
				led = 1;
		}
		else
		{
			if(disconnect())
				led = 0;
		}
	}

}
