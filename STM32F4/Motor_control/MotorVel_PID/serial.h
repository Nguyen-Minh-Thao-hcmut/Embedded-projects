#ifndef __SERIAL_H
#define __SERIAL_H

//Frame size definition
#define _RX_BUFF_SIZE_ 20
#define _TX_BUFF_SIZE_ 20
#define _CMD_SIZE_ 4
#define _OPT_SIZE_ 3
#define _DATA_SIZE_ 10
#define _FRAME_SIZE_ 20
// Frame Offset definition
#define _STX_ 0
#define _CMD_ 1
#define _OPT_ 5
#define _DATA_ 8
#define _FLOW_CONTROL_ 18 
#define _ETX_ 19
//
#include "stm32f4xx.h"
#include "system_timetick.h"
#include <string.h>
#include <stdlib.h>

extern void DMA_User_Init(void);
extern void UART4_User_Init(void);
extern void DMA1_Stream2_IRQHandler(void);
extern int StrCompare(uint8_t *pBuff, uint8_t *pSample, uint8_t nSize);
extern void SerialAcceptReceive(void);
extern void Serial_UnAcceptRecieve(void);
extern int SerialWriteComm(uint8_t* pStrCmd, uint8_t* pOpt, uint8_t* pData, uint8_t* pBuff, uint8_t* pFlow_control);
#endif
