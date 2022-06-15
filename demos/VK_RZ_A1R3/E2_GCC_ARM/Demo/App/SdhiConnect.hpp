#ifndef SDHI_CONNECT_HPP
#define SDHI_CONNECT_HPP

#include "mbed.h"
#include "FATFileSystem.h"
#include "SDHIBlockDevice.hpp"

class SDHIConnect {

public:

    SDHIConnect(const char *name);

    bool connect();

    bool disconnect();

    void wait_connect();

    void handleEvents(DigitalOut& led);

    bool format(int allocation_unit = 0);

    bool checkSlot();

    bool browsable();

    FATFileSystem * get_fs(void) { return &_fs; }

private:
    bool inserted();

    FATFileSystem _fs;
    SDHIBlockDevice _sd;

    bool _bInserted;
    bool _bBrowsable;
};

#endif
