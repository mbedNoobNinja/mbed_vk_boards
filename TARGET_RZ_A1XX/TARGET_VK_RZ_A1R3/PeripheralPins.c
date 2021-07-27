
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
    {P1_6 , IRQ2, 2},
    {P1_7 , IRQ3, 2},
    {P1_10, IRQ2, 2},
    {P1_11, IRQ3, 2},
    {P1_12, IRQ4, 2},
    {P1_13, IRQ5, 2},
    {P1_14, IRQ6, 2},
    {P1_15, IRQ7, 2},
    {P2_0 , IRQ7, 4},
    {P2_1 , IRQ6, 4},
    {P2_7 , IRQ2, 4},
    {P5_8 , IRQ3, 4},
    {P5_9 , IRQ4, 4},
    {P5_10, IRQ5, 4},
    {P5_11, IRQ6, 4},
    {P6_7 , IRQ0, 4},
    {P6_8 , IRQ1, 4},
    {P6_9 , IRQ2, 4},
    {P6_10, IRQ3, 4},
    {   NC,   NC, 0}
};

/************PINMAP***************/
const PinFunc PIPC_0_tbl[] = {
//   pin func pipc
    {P2_4 , 3, -1}, /* TIOC4A */
    {P2_5 , 3, -1}, /* TIOC3A */
    {P3_10, 3, -1}, /* TIOC3B */
    {P3_11, 3, -1}, /* TIOC3A */
    {P3_12, 3, -1}, /* TIOC3C */
    {P3_13, 3, -1}, /* TIOC3D */
    {P5_8 , 3, -1}, /* TIOC4A */
    {P5_9 , 3, -1}, /* TIOC4B */
    {P5_10, 3, -1}, /* TIOC4C */
    {P5_11, 3, -1}, /* TIOC4D */
    {P5_14, 4, -1}, /* TIOC2A */
    {P6_7 , 5, -1}, /* TIOC3A */
    {P6_8 , 5, -1}, /* TIOC3B */
    {P6_9 , 5, -1}, /* TIOC3C */
    {P6_10, 5, -1}, /* TIOC3D */
    {   NC, 0, -1}
    //{P5_6 , 3, 0 }, /* SSITxD1 */
    //{P6_0 , 5, 0 }, /* WDTOVF */
    //{P6_6 , 3, 0 }, /* SSITxD3 */
    //{P6_10, 3, 0 }, /* SSITxD0 */
};

/************ADC***************/
const PinMap PinMap_ADC[] = {
    {P1_10, AN2 , 1},
    {P1_11, AN3 , 1},
    {P1_12, AN4 , 1},
    {P1_13, AN5 , 1},
    {P1_14, AN6 , 1},
    {P1_15, AN7 , 1},
    {P3_9 , AN10, 1},
    {P3_10, AN11, 1},
    {P3_11, AN12, 1},
    {P3_12, AN13, 1},
    {P3_13, AN14, 1},
    {   NC,   NC, 0}
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
    {P3_9 , UART3, 5},
    {P3_15, UART1, 5},
    {P5_7 , UART2, 5},
    {P5_15, UART4, 3},
    {P7_1 , UART2, 4},
    {NC   , NC   , 0}
};

const PinMap PinMap_UART_RX[] = {
    {P0_1 , UART2, 2},
    {P0_2 , UART1, 2},
    {P1_7 , UART2, 3},
    {P1_10, UART2, 3},
    {P1_11, UART3, 3},
    {P3_10, UART3, 5},
    {P5_14, UART4, 3},
    {NC   , NC   , 0}
};

const PinMap PinMap_UART_CTS[] = {
    {   NC,    NC, 0}
};

const PinMap PinMap_UART_RTS[] = {
    {   NC,    NC, 0}
};

/************SPI***************/
const PinMap PinMap_SPI_SCLK[] = {
    {P5_4 , SPI_2, 2},
    {P6_0 , SPI_0, 3},
    {   NC,    NC, 0}
};

const PinMap PinMap_SPI_MOSI[] = {
    {P5_6 , SPI_2, 2},
    {P6_2 , SPI_0, 3},
    {NC   , NC   , 0}
};

const PinMap PinMap_SPI_MISO[] = {
    {P5_7 , SPI_2, 2},
    {P6_3 , SPI_0, 3},
    {NC   , NC   , 0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {P5_5 , SPI_2, 2},
    {P6_1 , SPI_0, 3},
    {NC   , NC   , 0}
};

/************PWM***************/
const PinMap PinMap_PWM[] = {
    {P2_4 , PWM_TIOC4A, 3},
    {P2_5 , PWM_TIOC3A, 3},
    {P3_11, PWM_TIOC3A, 3},
    {P3_12, PWM_TIOC3C, 3},
    {P5_8 , PWM_TIOC4A, 3},
    {P5_10, PWM_TIOC4C, 3},
    {P5_14, PWM_TIOC2A, 4},
    {P6_7 , PWM_TIOC3A, 5},
    {P6_9 , PWM_TIOC3C, 5},
    {NC   , NC        , 0}
};

/************CAN***************/
const PinMap PinMap_CAN_RD[] = {
    {P2_9 , CAN_0, 5},
    {P5_8 , CAN_0, 2},
    {NC   , NC   , 0}
};

const PinMap PinMap_CAN_TD[] = {
    {P2_8 , CAN_0, 5},
    {P5_9 , CAN_0, 2},
    {P6_10, CAN_1, 6},
    {NC   , NC   , 0}
};

const PinMap PinMap_SDHI_D0[] = {
/*  {P3_4  , SDHI_0, 2}, Unaccessable (used for ETHERNET) */
    {P7_3  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_D1[] = {
/*  {P3_5  , SDHI_0, 2}, Unaccessable (used for ETHERNET) */
    {P7_2  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_D2[] = {
/*  {P3_0  , SDHI_0, 2}, Unaccessable (used for ETHERNET) */
    {P7_7  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_D3[] = {
/*  {P3_1  , SDHI_0, 2}, Unaccessable (used for ETHERNET) */
    {P7_6  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_CLK[] = {
/*  {P3_3  , SDHI_0, 2}, Unaccessable (used for ETHERNET) */
    {P7_4  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_CMD[] = {
/*  {P3_2  , SDHI_0, 2}, Unaccessable (used for ETHERNET) */
    {P7_5  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_CD[] = {
/*  {P3_7  , SDHI_0, 2}, Unaccessable (used for ETHERNET) */
    {P7_0  , SDHI_1, 3},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_WP[] = {
/*  {P3_6  , SDHI_0, 2}, Unaccessable (used for ETHERNET) */
/*  {P7_1  , SDHI_1, 3}, Unaccessable (used for USBTX)    */
    {NC    , NC    , 0}
};
