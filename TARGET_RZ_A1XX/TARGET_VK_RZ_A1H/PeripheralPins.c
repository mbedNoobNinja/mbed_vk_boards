
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
    {P9_1,  IRQ0, 4},
    {P7_8,  IRQ1, 8},
    {P1_2,  IRQ2, 4}, {P1_8,  IRQ2, 3}, {P3_0,  IRQ2, 3}, {P5_9,  IRQ2, 4},
    {P1_3,  IRQ3, 4}, {P1_9,  IRQ3, 3},
    {P1_4,  IRQ4, 4}, {P1_10, IRQ4, 3},
    {P1_5,  IRQ5, 4}, {P1_11, IRQ5, 3},
    {P3_1,  IRQ6, 3}, {P3_9,  IRQ6, 8}, {P5_6,  IRQ6, 6},
    {NC,    NC,     0}
};

/************PINMAP***************/
const PinFunc PIPC_0_tbl[] = {
    //   pin      func     pm
    {P4_0   , 2      , -1}, // TIOC0A
    {P5_0   , 6      , -1}, // TIOC0A
    {P4_2   , 2      , -1}, // TIOC0C
    {P5_5   , 6      , -1}, // TIOC0C
    //
    {P8_14  , 4      , -1}, // TIOC2A
    //
    {P8_10  , 4      , -1}, // TIOC3A
    {P5_3   , 6      , -1}, // TIOC3C
    {P8_12  , 4      , -1}, // TIOC3C
    //
    {P3_8   , 6      , -1}, // TIOC4A
    {P4_4   , 3      , -1}, // TIOC4A
    {P3_10  , 6      , -1}, // TIOC4C
    {P4_6   , 3      , -1}, // TIOC4C
    //
    {P5_7   , 1      , 1 }, // TXOUT0M
    {P5_6   , 1      , 1 }, // TXOUT0P
    {P5_5   , 1      , 1 }, // TXOUT1M
    {P5_4   , 1      , 1 }, // TXOUT1P
    {P5_3   , 1      , 1 }, // TXOUT2M
    {P5_2   , 1      , 1 }, // TXOUT2P
    {P5_1   , 1      , 1 }, // TXCLKOUTM
    {P5_0   , 1      , 1 }, // TXCLKOUTP
    {P4_7   , 5      , 0 }, // SSITxD0
    {P8_10  , 8      , 0 }, // SSITxD5
    {P3_7   , 8      , 0 }, // WDTOVF
    {NC     , 0      , -1}
};

/************ADC***************/
const PinMap PinMap_ADC[] = {
    {P1_8,  AN0, 1},
    {P1_9,  AN1, 1},
    {P1_10, AN2, 1},
    {P1_11, AN3, 1},
    {P1_12, AN4, 1},
    {P1_13, AN5, 1},
    {P1_15, AN7, 1},
    {NC,    NC,  0}
};

/************I2C***************/
const PinMap PinMap_I2C_SDA[] = {
    {P1_1 , I2C_0, 1},
    {P1_3 , I2C_1, 1},
    {P1_5 , I2C_2, 1},
    {P1_7 , I2C_3, 1},
    {NC   , NC   , 0}
};

const PinMap PinMap_I2C_SCL[] = {
    {P1_0 , I2C_0, 1},
    {P1_2 , I2C_1, 1},
    {P1_4 , I2C_2, 1},
    {P1_6 , I2C_3, 1},
    {NC   , NC,    0}
};

/************UART***************/
const PinMap PinMap_UART_TX[] = {
    {P3_0  , UART2, 6},
    {P3_1  , UART2, 4},
    {P4_2  , UART2, 5},
    {P5_3  , UART3, 5},
    {P8_8  , UART3, 7},
    {P5_0  , UART4, 5},
    {P8_14 , UART4, 7},
    {P8_13 , UART5, 5},
    {P5_6  , UART6, 5},
    {NC    , NC   , 0}
};

const PinMap PinMap_UART_RX[] = {
    {P3_2  , UART2, 4},
    {P4_3  , UART2, 5},
    {P5_4  , UART3, 5},
    {P8_9  , UART3, 7},
    {P5_1  , UART4, 5},
    {P8_15 , UART4, 7},
    {P8_11 , UART5, 5},
    {P5_7  , UART6, 5},
    {NC    , NC   , 0}
};

const PinMap PinMap_UART_CTS[] = {
    {NC    , NC   , 0}
};

const PinMap PinMap_UART_RTS[] = {
    {NC    , NC   , 0}
};

/************SPI***************/
const PinMap PinMap_SPI_SCLK[] = {
    {P4_4  , SPI_1, 2},
    {P8_14 , SPI_2, 5},
    {P5_0  , SPI_3, 8},
    {P4_0  , SPI_4, 7},
    {NC    , NC   , 0}
};

const PinMap PinMap_SPI_MOSI[] = {
    {P4_6  , SPI_1, 2},
    {P9_0  , SPI_2, 5},
    {P5_2  , SPI_3, 8},
    {P4_2  , SPI_4, 7},
    {NC    , NC   , 0}
};

const PinMap PinMap_SPI_MISO[] = {
    {P4_7  , SPI_1, 2},
    {P9_1  , SPI_2, 5},
    {P5_3  , SPI_3, 8},
    {P4_3  , SPI_4, 7},
    {NC    , NC   , 0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {P4_5  , SPI_1, 2},
    {P8_15 , SPI_2, 5},
    {P5_1  , SPI_3, 8},
    {P4_1  , SPI_4, 7},
    {NC    , NC   , 0}
};

/************PWM***************/
const PinMap PinMap_PWM[] = {
    //TIOC0 A,C
    {P4_0     , PWM_TIOC0A, 2},	//TIOC0A
    {P5_0     , PWM_TIOC0A, 6},	//TIOC0A
    {P4_2     , PWM_TIOC0C, 2},	//TIOC0C
    {P5_5     , PWM_TIOC0C, 6},	//TIOC0C
    //TIOC2 A
    {P8_14    , PWM_TIOC2A, 4},	//TIOC2A
    //TIOC3 A,C
    {P8_10    , PWM_TIOC3A, 4},	//TIOC3A
    {P5_3     , PWM_TIOC3C, 6}, //TIOC3C
    {P8_12    , PWM_TIOC3C, 4},	//TIOC3C
    //TIOC4 A,C
    {P3_8     , PWM_TIOC4A, 6},	//TIOC4A
    {P4_4     , PWM_TIOC4A, 3},	//TIOC4A
    {P3_10    , PWM_TIOC4C, 6},	//TIOC4C
    {P4_6     , PWM_TIOC4C, 3},	//TIOC4C
    //PWM1
    {P8_10    , PWM_PWM1C , 6},	//PWM1C
    {P8_11    , PWM_PWM1D , 6},	//PWM1D
    {P8_12    , PWM_PWM1E , 6},	//PWM1E
    {P8_13    , PWM_PWM1F , 6},	//PWM1F
    {P8_14    , PWM_PWM1G , 6},	//PWM1G
    {P8_15    , PWM_PWM1H , 6},	//PWM1H
    //PWM2
    {P3_0     , PWM_PWM2A , 7},	//PWM2A
    {P3_1     , PWM_PWM2B , 7},	//PWM2B
    {P3_2     , PWM_PWM2C , 7},	//PWM2C
    {P4_4     , PWM_PWM2E , 4},	//PWM2E
    {P4_5     , PWM_PWM2F , 4},	//PWM2F
    {P4_6     , PWM_PWM2G , 4},	//PWM2G
    {P4_7     , PWM_PWM2H , 4},	//PWM2H
    {NC       , NC        , 0}
};

/************CAN***************/
const PinMap PinMap_CAN_RD[] = {
    {P9_1  , CAN_0, 3},
    {P1_4  , CAN_1, 3},
    {P5_9  , CAN_1, 5},
    {P4_2  , CAN_3, 4},
    {P1_5  , CAN_4, 3},
    {NC    , NC   , 0}
};

const PinMap PinMap_CAN_TD[] = {
    {P9_0  , CAN_0, 3},
    {P5_10 , CAN_1, 5},
    {P4_3  , CAN_3, 4},
    {P8_10 , CAN_4, 5},
    {NC    , NC   , 0}
};

const PinMap PinMap_SDHI_D0[] = {
    {P4_11 , SDHI_0, 3},
    {P3_11 , SDHI_1, 7},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_D1[] = {
    {P4_10 , SDHI_0, 3},
    {P3_10 , SDHI_1, 7},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_D2[] = {
    {P4_15 , SDHI_0, 3},
    {P3_15 , SDHI_1, 7},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_D3[] = {
    {P4_14 , SDHI_0, 3},
    {P3_14 , SDHI_1, 7},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_CLK[] = {
    {P4_12 , SDHI_0, 3},
    {P3_12 , SDHI_1, 7},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_CMD[] = {
    {P4_13 , SDHI_0, 3},
    {P3_13 , SDHI_1, 7},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_CD[] = {
    {P4_8  , SDHI_0, 3},
    {P3_8  , SDHI_1, 7},
    {NC    , NC    , 0}
};

const PinMap PinMap_SDHI_WP[] = {
    {P4_9  , SDHI_0, 3},
    {P3_9  , SDHI_1, 7},
    {NC    , NC    , 0}
};

