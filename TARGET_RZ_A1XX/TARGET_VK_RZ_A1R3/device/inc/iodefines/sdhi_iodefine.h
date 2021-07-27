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
* http://www.renesas.com/disclaimer*
* Copyright (C) 2013-2016 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name : sdhi_iodefine.h
* $Rev: $
* $Date::                           $
* Description : Definition of I/O Register for RZ/A1LU (V3.00l)
******************************************************************************/
#ifndef SDHI_IODEFINE_H
#define SDHI_IODEFINE_H
/* ->QAC 0639 : Over 127 members (C90) */
/* ->QAC 0857 : Over 1024 #define (C90) */
/* ->MISRA 18.4 : Pack unpack union */ /* ->SEC M1.6.2 */
/* ->SEC M1.10.1 : Not magic number */

#define SDHI0 (*(struct st_sdhi  *)0xE804E000uL) /* SDHI0 */
#define SDHI1 (*(struct st_sdhi  *)0xE804E800uL) /* SDHI1 */


/* Start of channel array defines of SPIBSC */

/* Channel array defines of SPIBSC */
/*(Sample) value = SPIBSC[ channel ]->CMNCR; */
#define SDHI_COUNT  (2)
#define SDHI_ADDRESS_LIST \
{   /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */ \
    &SDHI0 \
    &SDHI1 \
}   /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */ /* { } is for MISRA 19.4 */

/* End of channel array defines of SPIBSC */


#define SD_CMD_0			(SDHI0.SD_CMD)
#define SD_ARG0_0         	(SDHI0.SD_ARG0)
#define SD_ARG1_0           (SDHI0.SD_ARG1)
#define SD_STOP_0           (SDHI0.SD_STOP)
#define SDHI0_SD_SECCNT       SDHI0.SD_SECCNT
#define SDHI0_SD_RSP00        SDHI0.SD_RSP00
#define SDHI0_SD_RSP01        SDHI0.SD_RSP01
#define SDHI0_SD_RSP02        SDHI0.SD_RSP02
#define SDHI0_SD_RSP03        SDHI0.SD_RSP03
#define SDHI0_SD_RSP04        SDHI0.SD_RSP04
#define SDHI0_SD_RSP05        SDHI0.SD_RSP05
#define SDHI0_SD_RSP06        SDHI0.SD_RSP06
#define SDHI0_SD_RSP07        SDHI0.SD_RSP07
#define SDHI0_SD_INFO1        SDHI0.SD_INFO1
#define SDHI0_SD_INFO2        SDHI0.SD_INFO2
#define SDHI0_SD_INFO1_MASK   SDHI0.SD_INFO1_MASK
#define SDHI0_SD_INFO2_MASK   SDHI0.SD_INFO2_MASK
#define SDHI0_SD_CLK_CTRL     SDHI0.SD_CLK_CTRL
#define SDHI0_SD_SIZE         SDHI0.SD_SIZE
#define SDHI0_SD_OPTION       SDHI0.SD_OPTION
#define SDHI0_SD_ERR_STS1     SDHI0.SD_ERR_STS1
#define SDHI0_SD_ERR_STS2     SDHI0.SD_ERR_STS2
#define SDHI0_SD_BUF0         SDHI0.SD_BUF0
#define SDHI0_SDIO_MODE       SDHI0.SDIO_MODE
#define SDHI0_SDIO_INFO1      SDHI0.SDIO_INFO1
#define SDHI0_SDIO_INFO1_MASK SDHI0.SDIO_INFO1_MASK
#define SDHI0_CC_EXT_MODE     SDHI0.CC_EXT_MODE
#define SDHI0_SOFT_RST        SDHI0.SOFT_RST
#define SDHI0_VERSION         SDHI0.VERSION
#define SDHI0_EXT_SWAP        SDHI0.EXT_SWAP

typedef struct st_sdhi
{
                                                               /* SDHI             */
    volatile uint16_t  SD_CMD;                                 /*  SD_CMD          */
    volatile uint8_t   dummy1[2];                              /*                  */
    volatile uint16_t  SD_ARG0;                                /*  SSLDR           */
    volatile uint16_t  SD_ARG1;                                /*  SSLDR           */
    volatile uint16_t  SD_STOP;                                /*  SPBCR           */
    volatile uint16_t  SD_SECCNT;                              /*  SPBCR           */
    volatile uint16_t  SD_RSP00;                               /*  SPBCR           */
    volatile uint16_t  SD_RSP01;                               /*  SPBCR           */
    volatile uint16_t  SD_RSP02;                               /*  SPBCR           */
    volatile uint16_t  SD_RSP03;                               /*  SPBCR           */
    volatile uint16_t  SD_RSP04;                               /*  SPBCR           */
    volatile uint16_t  SD_RSP05;                               /*  SPBCR           */
    volatile uint16_t  SD_RSP06;                               /*  SPBCR           */
    volatile uint16_t  SD_RSP07;                               /*  SPBCR           */
    volatile uint16_t  SD_INFO1;                               /*  SPBCR           */
    volatile uint16_t  SD_INFO2;                               /*  SPBCR           */
    volatile uint16_t  SD_INFO1_MASK;                          /*  SPBCR           */
    volatile uint16_t  SD_INFO2_MASK;                          /*  SPBCR           */
    volatile uint16_t  SD_CLK_CTRL;                            /*  SPBCR           */
    volatile uint16_t  SD_SIZE;                                /*  SPBCR           */
    volatile uint16_t  SD_OPTION;                              /*  SPBCR           */
    volatile uint8_t   dummy2[2];                              /*                  */
    volatile uint16_t  SD_ERR_STS1;                            /*  SPBCR           */
    volatile uint16_t  SD_ERR_STS2;                            /*  SPBCR           */
    volatile uint32_t  SD_BUF0;                                /*  DRCR            */
    volatile uint16_t  SDIO_MODE;                              /*  DRCMR           */
    volatile uint16_t  SDIO_INFO1;                             /*  DREAR           */
    volatile uint16_t  SDIO_INFO1_MASK;                        /*  DROPR           */
    volatile uint8_t   dummy3[158];                            /*                  */
    volatile uint16_t  CC_EXT_MODE;                            /*  DRENR           */
    volatile uint8_t   dummy4[6];                              /*                  */
    volatile uint16_t  SOFT_RST;                               /*  SMCR            */
    volatile uint16_t  VERSION;                                /*  SMCMR           */
    volatile uint8_t   dummy5[12];                             /*                  */
    volatile uint16_t  EXT_SWAP;                               /*  SMADR           */
} r_io_sdhi_t;


/* Channel array defines of SDHI (2)*/
#ifdef  DECLARE_SDHI_CHANNELS
volatile struct st_sdhi*  SDHI[ SDHI_COUNT ] =
    /* ->MISRA 11.3 */ /* ->SEC R2.7.1 */
    SDHI_ADDRESS_LIST;
    /* <-MISRA 11.3 */ /* <-SEC R2.7.1 */
#endif  /* DECLARE_SPIBSC_CHANNELS */
/* End of channel array defines of SDHI (2)*/


/* <-SEC M1.10.1 */
/* <-MISRA 18.4 */ /* <-SEC M1.6.2 */
/* <-QAC 0857 */
/* <-QAC 0639 */
#endif
