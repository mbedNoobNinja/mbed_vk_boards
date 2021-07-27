
/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "PeripheralPins.h"

/************IRQ***************/
enum {
    IRQ0,IRQ1,
    IRQ2,IRQ3,
    IRQ4,IRQ5,
    IRQ6,IRQ7,
} IRQNo;
const PinMap PinMap_IRQ[] = {
    {P1_4 , IRQ0, 2},
    {P1_5 , IRQ1, 2},
    {P1_13, IRQ5, 2},
    {P1_14, IRQ6, 2},
    {P1_15, IRQ7, 2},
    {P6_9 , IRQ2, 4},
    {P6_10, IRQ3, 4},
    {   NC,   NC, 0}
};

/************PINMAP***************/
const PinFunc PIPC_0_tbl[] = {
//   pin      func     pm
    {P6_9 , 5, -1}, /* TIOC3C */
    {P6_10, 5, -1}, /* TIOC3D */
    //{P6_10  , 3      , 0 }, /* SSITxD0 */
    //{P6_6   , 3      , 0 }, /* SSITxD3 */
    {   NC, 0, -1}
};

/************ADC***************/
const PinMap PinMap_ADC[] = {
    {P1_13, AN5, 1},
    {P1_14, AN6, 1},
    {   NC,  NC, 0}
};

/************I2C***************/
const PinMap PinMap_I2C_SDA[] = {
    {P1_5 , I2C_2, 1},
    {P1_7 , I2C_3, 1},
    {   NC,    NC, 0}
};

const PinMap PinMap_I2C_SCL[] = {
    {P1_4 , I2C_2, 1},
    {P1_6 , I2C_3, 1},
    {   NC,    NC, 0}
};

/************UART***************/
const PinMap PinMap_UART_TX[] = {
    {P6_15, UART0, 5},
    {P3_15, UART1, 5},
    {   NC,    NC, 0}
};

const PinMap PinMap_UART_RX[] = {
    {P6_14, UART0, 5},
    {P0_2 , UART1, 2},
    {   NC,    NC, 0}
};

const PinMap PinMap_UART_CTS[] = {
    {P6_13, UART0, 5},
    {P4_0 , UART1, 5},
    {   NC,    NC, 0}
};

const PinMap PinMap_UART_RTS[] = {
    {P6_12, UART0, 5},
    {P4_1 , UART1, 5},
    {   NC,    NC, 0}
};

/************SPI***************/
const PinMap PinMap_SPI_SCLK[] = {
    {P6_0 , SPI_0, 3},
    {P6_12, SPI_1, 3},
    {   NC,    NC, 0}
};

const PinMap PinMap_SPI_MOSI[] = {
    {P6_2 , SPI_0, 3},
    {P6_14, SPI_1, 3},
    {   NC,    NC, 0}
};

const PinMap PinMap_SPI_MISO[] = {
    {P6_3 , SPI_0, 3},
    {P6_15, SPI_1, 3},
    {   NC,    NC, 0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {P6_1 , SPI_0, 3},
    {P6_13, SPI_1, 3},
    {   NC,    NC, 0}
};

/************PWM***************/
const PinMap PinMap_PWM[] = {
    {P6_9 , PWM_TIOC3C, 5},
    {   NC,    NC, 0}
};

/************CAN***************/
const PinMap PinMap_CAN_RD[] = {
    {   NC,    NC, 0}
};

const PinMap PinMap_CAN_TD[] = {
    {P6_10, CAN_1, 6},
    {   NC,    NC, 0}
};

const PinMap PinMap_SDHI_D0[] = {
/*  {P3_4  , SDHI_0, 2}, Unaccessable (used for SDRAM) */
    {P7_3  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_D1[] = {
/*  {P3_5  , SDHI_0, 2}, Unaccessable (used for SDRAM) */
    {P7_2  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_D2[] = {
/*  {P3_0  , SDHI_0, 2}, Unaccessable (used for SDRAM) */
    {P7_7  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_D3[] = {
/*  {P3_1  , SDHI_0, 2}, Unaccessable (used for SDRAM) */
    {P7_6  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_CLK[] = {
/*  {P3_3  , SDHI_0, 2}, Unaccessable (used for SDRAM) */
    {P7_4  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_CMD[] = {
/*  {P3_2  , SDHI_0, 2}, Unaccessable (used for SDRAM) */
    {P7_5  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_CD[] = {
/*  {P3_7  , SDHI_0, 2}, Unaccessable (used for SDRAM) */
    {P7_0  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_WP[] = {
/*  {P3_6  , SDHI_0, 2}, Unaccessable (used for SDRAM) */
    {P7_1  , SDHI_1, 3},
    {NC    , NC    , 0}
};
