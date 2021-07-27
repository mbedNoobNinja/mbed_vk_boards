/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2012 - 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/**************************************************************************//**
* @file         RZ_A1_Init.c
* $Rev: 624 $
* $Date:: 2013-04-24 13:37:48 +0900#$
* @brief        RZ_A1 Initialize
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "VKRZA1LU.h"
#include "RZ_A1_Init.h"
#include "rza_io_regrw.h"
#include "gpio_iobitmask.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
#define CS2_SDRAM_MODE_16BIT_CAS2_BR_BW (*(volatile uint16_t*)0x3FFFD040)
#define CS3_SDRAM_MODE_16BIT_CAS2_BR_BW (*(volatile uint16_t*)0x3FFFE040)

#define GPIO_PORT0_BOOTMODE_BITMASK (0x000fu)

#define CS3_SDRAM

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

static void PORT_Init(void)
{
    /* ==== BSC settings ==== */

    /* ---- P2_1 : RAS# ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC21_SHIFT,   GPIO_PIBC2_PIBC21);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC21_SHIFT,   GPIO_PBDC2_PBDC21);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM21_SHIFT,       GPIO_PM2_PM21);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC21_SHIFT,     GPIO_PMC2_PMC21);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC21_SHIFT,   GPIO_PIPC2_PIPC21);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC21_SHIFT,   GPIO_PBDC2_PBDC21);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC21_SHIFT,     GPIO_PFC2_PFC21);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE21_SHIFT,   GPIO_PFCE2_PFCE21);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE21_SHIFT, GPIO_PFCAE2_PFCAE21);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC21_SHIFT,   GPIO_PIPC2_PIPC21);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC21_SHIFT,     GPIO_PMC2_PMC21);

    /* ---- P2_2 : CAS# ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC22_SHIFT,   GPIO_PIBC2_PIBC22);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC22_SHIFT,   GPIO_PBDC2_PBDC22);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM22_SHIFT,       GPIO_PM2_PM22);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC22_SHIFT,     GPIO_PMC2_PMC22);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC22_SHIFT,   GPIO_PIPC2_PIPC22);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC22_SHIFT,   GPIO_PBDC2_PBDC22);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC22_SHIFT,     GPIO_PFC2_PFC22);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE22_SHIFT,   GPIO_PFCE2_PFCE22);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE22_SHIFT, GPIO_PFCAE2_PFCAE22);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC22_SHIFT,   GPIO_PIPC2_PIPC22);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC22_SHIFT,     GPIO_PMC2_PMC22);

    /* ---- P2_3 : CKE ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC23_SHIFT,   GPIO_PIBC2_PIBC23);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC23_SHIFT,   GPIO_PBDC2_PBDC23);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM23_SHIFT,       GPIO_PM2_PM23);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC23_SHIFT,     GPIO_PMC2_PMC23);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC23_SHIFT,   GPIO_PIPC2_PIPC23);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC23_SHIFT,   GPIO_PIBC2_PIBC23);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC23_SHIFT,     GPIO_PBDC2_PBDC23);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE23_SHIFT,   GPIO_PM2_PM23);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE23_SHIFT, GPIO_PMC2_PMC23);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC23_SHIFT,   GPIO_PIPC2_PIPC23);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC23_SHIFT,     GPIO_PMC2_PMC23);

    /* ---- P2_4 : DQMLL ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC24_SHIFT,   GPIO_PIBC2_PIBC24);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC24_SHIFT,   GPIO_PBDC2_PBDC24);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM24_SHIFT,       GPIO_PM2_PM24);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC24_SHIFT,     GPIO_PMC2_PMC24);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC24_SHIFT,   GPIO_PIPC2_PIPC24);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC24_SHIFT,   GPIO_PBDC2_PBDC24);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC24_SHIFT,     GPIO_PFC2_PFC24);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE24_SHIFT,   GPIO_PFCE2_PFCE24);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE24_SHIFT, GPIO_PFCAE2_PFCAE24);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC24_SHIFT,   GPIO_PIPC2_PIPC24);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC24_SHIFT,     GPIO_PMC2_PMC24);

    /* ---- P2_5 : DQMLU ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC25_SHIFT,   GPIO_PIBC2_PIBC25);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC25_SHIFT,   GPIO_PBDC2_PBDC25);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM25_SHIFT,       GPIO_PM2_PM25);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC25_SHIFT,     GPIO_PMC2_PMC25);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC25_SHIFT,   GPIO_PIPC2_PIPC25);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC25_SHIFT,   GPIO_PBDC2_PBDC25);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC25_SHIFT,     GPIO_PFC2_PFC25);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE25_SHIFT,   GPIO_PFCE2_PFCE25);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE25_SHIFT, GPIO_PFCAE2_PFCAE25);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC25_SHIFT,   GPIO_PIPC2_PIPC25);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC25_SHIFT,     GPIO_PMC2_PMC25);

    /* ---- P2_6 : RD/WR# ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC26_SHIFT,   GPIO_PIBC2_PIBC26);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC26_SHIFT,   GPIO_PBDC2_PBDC26);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM26_SHIFT,       GPIO_PM2_PM26);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC26_SHIFT,     GPIO_PMC2_PMC26);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC26_SHIFT,   GPIO_PIPC2_PIPC26);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC26_SHIFT,   GPIO_PBDC2_PBDC26);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC26_SHIFT,     GPIO_PFC2_PFC26);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE26_SHIFT,   GPIO_PFCE2_PFCE26);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE26_SHIFT, GPIO_PFCAE2_PFCAE26);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC26_SHIFT,   GPIO_PIPC2_PIPC26);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC26_SHIFT,     GPIO_PMC2_PMC26);

    /* ---- P2_0 : CS3# ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC20_SHIFT,   GPIO_PIBC2_PIBC20);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC20_SHIFT,   GPIO_PBDC2_PBDC20);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM20_SHIFT,       GPIO_PM2_PM20);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC20_SHIFT,     GPIO_PMC2_PMC20);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC20_SHIFT,   GPIO_PIPC2_PIPC20);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC20_SHIFT,   GPIO_PBDC2_PBDC20);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC20_SHIFT,     GPIO_PFC2_PFC20);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE20_SHIFT,   GPIO_PFCE2_PFCE20);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE20_SHIFT, GPIO_PFCAE2_PFCAE20);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC20_SHIFT,   GPIO_PIPC2_PIPC20);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC20_SHIFT,     GPIO_PMC2_PMC20);
}

/******************************************************************************
* Function Name: CS3_PORTInit
* Description  : Sets the PORT multiplexed pin to use the CS3 space.
* Arguments    : none
* Return Value : none
******************************************************************************/
static void CS3_PORTInit(void)
{
    /* ---- P5_0 : D0 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE50_SHIFT, GPIO_PFCAE5_PFCAE50);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE50_SHIFT,   GPIO_PFCE5_PFCE50);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC50_SHIFT,     GPIO_PFC5_PFC50);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC50_SHIFT,     GPIO_PMC5_PMC50);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC50_SHIFT,   GPIO_PIPC5_PIPC50);

    /* ---- P5_1 : D1 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE51_SHIFT, GPIO_PFCAE5_PFCAE51);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE51_SHIFT,   GPIO_PFCE5_PFCE51);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC51_SHIFT,     GPIO_PFC5_PFC51);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC51_SHIFT,     GPIO_PMC5_PMC51);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC51_SHIFT,   GPIO_PIPC5_PIPC51);

    /* ---- P5_2 : D2 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE52_SHIFT, GPIO_PFCAE5_PFCAE52);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE52_SHIFT,   GPIO_PFCE5_PFCE52);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC52_SHIFT,     GPIO_PFC5_PFC52);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC52_SHIFT,     GPIO_PMC5_PMC52);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC52_SHIFT,   GPIO_PIPC5_PIPC52);

    /* ---- P5_3 : D3 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE53_SHIFT, GPIO_PFCAE5_PFCAE53);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE53_SHIFT,   GPIO_PFCE5_PFCE53);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC53_SHIFT,     GPIO_PFC5_PFC53);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC53_SHIFT,     GPIO_PMC5_PMC53);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC53_SHIFT,   GPIO_PIPC5_PIPC53);

    /* ---- P5_4 : D4 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE54_SHIFT, GPIO_PFCAE5_PFCAE54);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE54_SHIFT,   GPIO_PFCE5_PFCE54);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC54_SHIFT,     GPIO_PFC5_PFC54);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC54_SHIFT,     GPIO_PMC5_PMC54);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC54_SHIFT,   GPIO_PIPC5_PIPC54);

    /* ---- P5_5 : D5 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE55_SHIFT, GPIO_PFCAE5_PFCAE55);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE55_SHIFT,   GPIO_PFCE5_PFCE55);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC55_SHIFT,     GPIO_PFC5_PFC55);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC55_SHIFT,     GPIO_PMC5_PMC55);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC55_SHIFT,   GPIO_PIPC5_PIPC55);

    /* ---- P5_6 : D6 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE56_SHIFT, GPIO_PFCAE5_PFCAE56);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE56_SHIFT,   GPIO_PFCE5_PFCE56);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC56_SHIFT,     GPIO_PFC5_PFC56);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC56_SHIFT,     GPIO_PMC5_PMC56);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC56_SHIFT,   GPIO_PIPC5_PIPC56);

    /* ---- P5_7 : D7 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE57_SHIFT, GPIO_PFCAE5_PFCAE57);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE57_SHIFT,   GPIO_PFCE5_PFCE57);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC57_SHIFT,     GPIO_PFC5_PFC57);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC57_SHIFT,     GPIO_PMC5_PMC57);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC57_SHIFT,   GPIO_PIPC5_PIPC57);

    /* ---- P5_8 : D8 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE58_SHIFT, GPIO_PFCAE5_PFCAE58);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE58_SHIFT,   GPIO_PFCE5_PFCE58);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC58_SHIFT,     GPIO_PFC5_PFC58);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC58_SHIFT,     GPIO_PMC5_PMC58);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC58_SHIFT,   GPIO_PIPC5_PIPC58);

    /* ---- P5_9 : D9 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE59_SHIFT, GPIO_PFCAE5_PFCAE59);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE59_SHIFT,   GPIO_PFCE5_PFCE59);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC59_SHIFT,     GPIO_PFC5_PFC59);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC59_SHIFT,     GPIO_PMC5_PMC59);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC59_SHIFT,   GPIO_PIPC5_PIPC59);

    /* ---- P5_10 : D10 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE510_SHIFT, GPIO_PFCAE5_PFCAE510);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE510_SHIFT,   GPIO_PFCE5_PFCE510);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC510_SHIFT,     GPIO_PFC5_PFC510);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC510_SHIFT,     GPIO_PMC5_PMC510);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC510_SHIFT,   GPIO_PIPC5_PIPC510);

    /* ---- P5_11 : D11 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE511_SHIFT, GPIO_PFCAE5_PFCAE511);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE511_SHIFT,   GPIO_PFCE5_PFCE511);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC511_SHIFT,     GPIO_PFC5_PFC511);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC511_SHIFT,     GPIO_PMC5_PMC511);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC511_SHIFT,   GPIO_PIPC5_PIPC511);

    /* ---- P5_12 : D12 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE512_SHIFT, GPIO_PFCAE5_PFCAE512);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE512_SHIFT,   GPIO_PFCE5_PFCE512);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC512_SHIFT,     GPIO_PFC5_PFC512);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC512_SHIFT,     GPIO_PMC5_PMC512);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC512_SHIFT,   GPIO_PIPC5_PIPC512);

    /* ---- P5_13 : D13 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE513_SHIFT, GPIO_PFCAE5_PFCAE513);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE513_SHIFT,   GPIO_PFCE5_PFCE513);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC513_SHIFT,     GPIO_PFC5_PFC513);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC513_SHIFT,     GPIO_PMC5_PMC513);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC513_SHIFT,   GPIO_PIPC5_PIPC513);

    /* ---- P5_14 : D14 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE514_SHIFT, GPIO_PFCAE5_PFCAE514);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE514_SHIFT,   GPIO_PFCE5_PFCE514);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC514_SHIFT,     GPIO_PFC5_PFC514);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC514_SHIFT,     GPIO_PMC5_PMC514);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC514_SHIFT,   GPIO_PIPC5_PIPC514);

    /* ---- P5_15 : D15 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE5, 0, GPIO_PFCAE5_PFCAE515_SHIFT, GPIO_PFCAE5_PFCAE515);
    RZA_IO_RegWrite_16(&GPIO.PFCE5,  0, GPIO_PFCE5_PFCE515_SHIFT,   GPIO_PFCE5_PFCE515);
    RZA_IO_RegWrite_16(&GPIO.PFC5,   0, GPIO_PFC5_PFC515_SHIFT,     GPIO_PFC5_PFC515);
    RZA_IO_RegWrite_16(&GPIO.PMC5,   1, GPIO_PMC5_PMC515_SHIFT,     GPIO_PMC5_PMC515);
    RZA_IO_RegWrite_16(&GPIO.PIPC5,  1, GPIO_PIPC5_PIPC515_SHIFT,   GPIO_PIPC5_PIPC515);

    /* ---- P3_0 : A1 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE30_SHIFT, GPIO_PFCAE3_PFCAE30);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE30_SHIFT,   GPIO_PFCE3_PFCE30);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC30_SHIFT,     GPIO_PFC3_PFC30);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM30_SHIFT,       GPIO_PM3_PM30);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC30_SHIFT,     GPIO_PMC3_PMC30);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC30_SHIFT,   GPIO_PIPC3_PIPC30);

    /* ---- P3_1 : A2 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE31_SHIFT, GPIO_PFCAE3_PFCAE31);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE31_SHIFT,   GPIO_PFCE3_PFCE31);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC31_SHIFT,     GPIO_PFC3_PFC31);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM31_SHIFT,       GPIO_PM3_PM31);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC31_SHIFT,     GPIO_PMC3_PMC31);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC31_SHIFT,   GPIO_PIPC3_PIPC31);

    /* ---- P3_2 : A3 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE32_SHIFT, GPIO_PFCAE3_PFCAE32);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE32_SHIFT,   GPIO_PFCE3_PFCE32);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC32_SHIFT,     GPIO_PFC3_PFC32);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM32_SHIFT,       GPIO_PM3_PM32);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC32_SHIFT,     GPIO_PMC3_PMC32);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC32_SHIFT,   GPIO_PIPC3_PIPC32);

    /* ---- P3_3 : A4 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE33_SHIFT, GPIO_PFCAE3_PFCAE33);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE33_SHIFT,   GPIO_PFCE3_PFCE33);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC33_SHIFT,     GPIO_PFC3_PFC33);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM33_SHIFT,       GPIO_PM3_PM33);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC33_SHIFT,     GPIO_PMC3_PMC33);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC33_SHIFT,   GPIO_PIPC3_PIPC33);

    /* ---- P3_4 : A5 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE34_SHIFT, GPIO_PFCAE3_PFCAE34);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE34_SHIFT,   GPIO_PFCE3_PFCE34);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC34_SHIFT,     GPIO_PFC3_PFC34);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM34_SHIFT,       GPIO_PM3_PM34);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC34_SHIFT,     GPIO_PMC3_PMC34);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC34_SHIFT,   GPIO_PIPC3_PIPC34);

    /* ---- P3_5 : A6 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE35_SHIFT, GPIO_PFCAE3_PFCAE35);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE35_SHIFT,   GPIO_PFCE3_PFCE35);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC35_SHIFT,     GPIO_PFC3_PFC35);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM35_SHIFT,       GPIO_PM3_PM35);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC35_SHIFT,     GPIO_PMC3_PMC35);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC35_SHIFT,   GPIO_PIPC3_PIPC35);

    /* ---- P3_6 : A7 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE36_SHIFT, GPIO_PFCAE3_PFCAE36);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE36_SHIFT,   GPIO_PFCE3_PFCE36);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC36_SHIFT,     GPIO_PFC3_PFC36);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM36_SHIFT,       GPIO_PM3_PM36);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC36_SHIFT,     GPIO_PMC3_PMC36);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC36_SHIFT,   GPIO_PIPC3_PIPC36);

    /* ---- P3_7 : A8 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE37_SHIFT, GPIO_PFCAE3_PFCAE37);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE37_SHIFT,   GPIO_PFCE3_PFCE37);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC37_SHIFT,     GPIO_PFC3_PFC37);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM37_SHIFT,       GPIO_PM3_PM37);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC37_SHIFT,     GPIO_PMC3_PMC37);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC37_SHIFT,   GPIO_PIPC3_PIPC37);

    /* ---- P3_8 : A9 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE38_SHIFT, GPIO_PFCAE3_PFCAE38);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE38_SHIFT,   GPIO_PFCE3_PFCE38);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC38_SHIFT,     GPIO_PFC3_PFC38);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM38_SHIFT,       GPIO_PM3_PM38);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC38_SHIFT,     GPIO_PMC3_PMC38);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC38_SHIFT,   GPIO_PIPC3_PIPC38);

    /* ---- P3_9 : A10 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE39_SHIFT, GPIO_PFCAE3_PFCAE39);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE39_SHIFT,   GPIO_PFCE3_PFCE39);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC39_SHIFT,     GPIO_PFC3_PFC39);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM39_SHIFT,       GPIO_PM3_PM39);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC39_SHIFT,     GPIO_PMC3_PMC39);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC39_SHIFT,   GPIO_PIPC3_PIPC39);

    /* ---- P3_10 : A11 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE310_SHIFT, GPIO_PFCAE3_PFCAE310);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE310_SHIFT,   GPIO_PFCE3_PFCE310);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC310_SHIFT,     GPIO_PFC3_PFC310);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM310_SHIFT,       GPIO_PM3_PM310);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC310_SHIFT,     GPIO_PMC3_PMC310);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC310_SHIFT,   GPIO_PIPC3_PIPC310);

    /* ---- P3_11 : A12 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE311_SHIFT, GPIO_PFCAE3_PFCAE311);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE311_SHIFT,   GPIO_PFCE3_PFCE311);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC311_SHIFT,     GPIO_PFC3_PFC311);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM311_SHIFT,       GPIO_PM3_PM311);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC311_SHIFT,     GPIO_PMC3_PMC311);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC311_SHIFT,   GPIO_PIPC3_PIPC311);

    /* ---- P3_12 : A13 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE312_SHIFT, GPIO_PFCAE3_PFCAE312);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE312_SHIFT,   GPIO_PFCE3_PFCE312);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC312_SHIFT,     GPIO_PFC3_PFC312);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM312_SHIFT,       GPIO_PM3_PM312);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC312_SHIFT,     GPIO_PMC3_PMC312);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC312_SHIFT,   GPIO_PIPC3_PIPC312);

    /* ---- P3_13 : A14 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE313_SHIFT, GPIO_PFCAE3_PFCAE313);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE313_SHIFT,   GPIO_PFCE3_PFCE313);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC313_SHIFT,     GPIO_PFC3_PFC313);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM313_SHIFT,       GPIO_PM3_PM313);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC313_SHIFT,     GPIO_PMC3_PMC313);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC313_SHIFT,   GPIO_PIPC3_PIPC313);

    /* ---- P3_14 : A15 ---- */
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE314_SHIFT, GPIO_PFCAE3_PFCAE314);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE314_SHIFT,   GPIO_PFCE3_PFCE314);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC314_SHIFT,     GPIO_PFC3_PFC314);
    RZA_IO_RegWrite_16(&GPIO.PM3,    0, GPIO_PM3_PM314_SHIFT,       GPIO_PM3_PM314);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC314_SHIFT,     GPIO_PMC3_PMC314);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC314_SHIFT,   GPIO_PIPC3_PIPC314);
}


/******************************************************************************
* Function Name: CS3_BSC_Init
* Description  : This is the user-defined function called by the R_BSC_Init
*              : function. The setting for initialization of the BSC in the CS3
*              : space is required. In this sample code, the setting to use
*              : the SDRAM in the CS3 space is executed. Sets the BSC to 
*              : connect the ISSI IS42S16320B-75 to the CS3 space with 16-bit
*              : bus width.
* Arguments    : none
* Return Value : none
******************************************************************************/
static void CS3_BSC_Init(void)
{
       /* ==== CS2BCR settings ==== */
    /* Idle Cycles between Write-read Cycles  */
    /* and Write-write Cycles : 0 idle cycles */
    /* Memory type :SDRAM                     */
    /* Data Bus Size : 16-bit                 */
    BSC.CS2BCR = 0x00004C00ul;

    /* SDRAM WORKAROUND - see Note */
    BSC.CS2WCR = 0x00000480ul;

    /* ==== CS3BCR settings ==== */
    /* SDRAM WORKAROUND - see Note */
    /* Idle Cycles between Write-read Cycles  */
    /* and Write-write Cycles : 0 idle cycles */
    /* Memory type :SDRAM                     */
    /* Data Bus Size : 16-bit                 */
    BSC.CS3BCR = 0x00004C00ul;

    /* ==== CS2/3WCR settings ==== */
    /* Precharge completion wait cycles: 1 cycle     */
    /* Wait cycles between ACTV command              */
    /* and READ(A)/WRITE(A) command : 1 cycles       */
    /* CAS latency for Area 3 : 2 cycles             */
    /* Auto-precharge startup wait cycles : 2 cycles */
    /* Idle cycles from REF command/self-refresh     */
    /* Release to ACTV/REF/MRS command : 5 cycles    */
    BSC.CS3WCR = 0x00002492ul;

    /* ==== SDCR settings ==== */
    /* SDRAM WORKAROUND - see Note*/
    /* Row address for Area 2 : 13-bit    */
    /* Column Address for Area 2 : 9-bit  */
    /* Refresh Control :Refresh           */
    /* RMODE :Auto-refresh is performed   */
    /* BACTV :Auto-precharge mode         */
    /* Row address for Area 3 : 13-bit    */
    /* Column Address for Area 3 : 9-bit  */
    BSC.SDCR = 0x00110811ul;

    /* ==== RTCOR settings ==== */
    /* 7.8usec / 60nsec              */
    /*   = 32(0x40)cycles per refresh */
    BSC.RTCOR = 0xA55A0080ul;

    /* ==== RTCSR settings ==== */
    /* initialisation sequence start */
    /* Clock select B-phy/16          */
    /* Refresh count :Once           */
    BSC.RTCSR = 0xA55A0008ul;


    /* ==== SDRAM Mode Register ==== */
    /* Burst read (burst length 1)./Burst write */
    CS2_SDRAM_MODE_16BIT_CAS2_BR_BW = 0;

    /* SDRAM WORKAROUND - see Note */
    CS3_SDRAM_MODE_16BIT_CAS2_BR_BW = 0;
}

/**************************************************************************//**
* Function Name: RZ_A1_SetSramWriteEnable
* @brief         Initialize Board settings
*
*                Description:<br>
*                Set SRAM write enable
* @param         none
* @retval        none
******************************************************************************/
void RZ_A1_SetSramWriteEnable(void)
{
    /* Enable SRAM write access */
    CPG.SYSCR3 = 0x0F;

    return;
}

/**************************************************************************//**
* Function Name: RZ_A1_InitClock
* @brief         Initialize Board settings
*
*                Description:<br>
*                Initialize Clock
* @param         none
* @retval        none
******************************************************************************/
void RZ_A1_InitClock(void)
{
    /* Cancel L2C standby status before clock change */
    L2CREG15_POWER_CTRL = 0x00000001;

    /* Clock settings */
    /* ClockMode1 */
    CPG.FRQCR  = 0x1035;    /* CPU Clock =384.00MHz */

    return;
}

/**************************************************************************//**
* Function Name: RZ_A1_IsClockMode0
* @brief         Query Clock Mode
*
*                Description:<br>
*                Answer ClockMode0 or not
* @param         none
* @retval        true  : clock mode 0
* @retval        false : clock mode 1
******************************************************************************/
int RZ_A1_IsClockMode0(void)
{
    /* ClockMode1 */
    return false;
}

/**************************************************************************//**
* Function Name: RZ_A1_InitBus
* @brief         Initialize Bus
*
*                Description:<br>
*                Initialize Pin Setting
* @param         none
* @retval        none
******************************************************************************/
void RZ_A1_InitBus(void)
{
#if defined(CS3_SDRAM)
   PORT_Init();
   CS3_PORTInit();
   CS3_BSC_Init();
#endif
    /*************************************************************************/
    /* If need Pin Setting before run program, the setting will be wrote here*/
    /*************************************************************************/
    /* P2_7(ESP_EN) */
    GPIOP2      &= ~0x0080;         /* Outputs low level */
    GPIOPMC2    &= ~0x0080;         /* Port mode */
    GPIOPM2     &= ~0x0080;         /* Output mode */

    return;
}

/******************************************************************************
End of file
******************************************************************************/
