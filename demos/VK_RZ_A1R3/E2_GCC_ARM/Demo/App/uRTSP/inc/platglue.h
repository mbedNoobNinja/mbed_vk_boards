#pragma once

#ifdef ARDUINO_ARCH_ESP32
#include "platglue-esp32.h"
#elif defined(__MBED__)
#include "platglue-mbed.h"
#else
#include "platglue-posix.h"
#endif
