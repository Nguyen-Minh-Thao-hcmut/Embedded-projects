#include "serial.h"
#include "pid.h"

uint8_t recieve_flag = 0;
uint8_t rxbuff[_RX_BUFF_SIZE_];
uint8_t txbuff[_TX_BUFF_SIZE_];
uint8_t g_strCommand[_CMD_SIZE_];
uint8_t g_strOpt[_OPT_SIZE_];
uint8_t g_strData[_DATA_SIZE_];

//uint8_t g_strResent_Request[2];
uint8_t g_Flow_control[1];
uint8_t bDataAvailable = 0;
uint8_t STX[] = {0x02U};
uint8_t ETX[] = {0x03U};
uint8_t SYN[] = {0x16U};
uint8_t ACK[] = {0x06U};
uint8_t NAK[] = {0x15U};

extern PROCESS_t tProcess;

int StrCompare(uint8_t *pBuff, uint8_t *pSample, uint8_t nSize)
{
	int i;
    for (i = 0; i < nSize; i++)
    {
        if (pBuff[i] != pSample[i])
        {
            return 0;
        }
    }

    return 1;
}

void SerialAcceptReceive(void)
{
    /* Enable USART */
  USART_Cmd(UART4, ENABLE);
	
	/* Enable UART4 DMA */
	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
}

void Serial_UnAcceptRecieve(void)
{
	USART_Cmd(UART4, DISABLE);
	USART_DMACmd(UART4, USART_DMAReq_Rx, DISABLE);
}


void SerialReadComm(uint8_t* pBuff, uint8_t* pStrCmd, uint8_t* pStrOpt, uint8_t* pStrData)
{
	if ((pBuff[0] == STX[0])&&(pBuff[_FRAME_SIZE_ - 1] == ETX[0])&&(pBuff[_FLOW_CONTROL_] == SYN[0]))
	{
			memcpy(pStrCmd, pBuff + _CMD_,_CMD_SIZE_);
			memcpy(pStrOpt, pBuff + _OPT_,_OPT_SIZE_);
			memcpy(pStrData, pBuff + _DATA_,_DATA_SIZE_);
	}
}

int SerialWriteComm(uint8_t* pStrCmd, uint8_t* pOpt, uint8_t* pData, uint8_t* pBuff, uint8_t* pFlow_control)
{
	if (bDataAvailable == 1)
	{
	uint8_t index = 0;
	//uint8_t* pBuff; 
	//pBuff = (uint8_t*)malloc(18);
			
	memcpy(pBuff + index, STX, 1);
	index += 1;
	memcpy(pBuff + index, pStrCmd, _CMD_SIZE_);
	index += _CMD_SIZE_;
	memcpy(pBuff + index, pOpt, _OPT_SIZE_);
	index += _OPT_SIZE_;
	memcpy(pBuff + index, pData, _DATA_SIZE_);
	index += _DATA_SIZE_;
	memcpy(pBuff + index, pFlow_control, 1);
	index += 1;
	memcpy(pBuff + index, ETX, 1);
	// UART with DMA
	DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);		
	DMA1_Stream4->NDTR = _TX_BUFF_SIZE_;
	DMA_Cmd(DMA1_Stream4, ENABLE);
	bDataAvailable = 0;
	return 1;
	//
	//free(pBuff);
	}
	else 
	{
		return 0;	
	}
}


void DMA1_Stream2_IRQHandler(void)
{
	
	uint8_t* pStrCmd_Tmp;
	uint8_t* pStrOpt_Tmp;
	uint8_t* pStrData_Tmp;
	
	pStrCmd_Tmp = (uint8_t*)malloc(_CMD_SIZE_);
	pStrOpt_Tmp = (uint8_t*)malloc(_OPT_SIZE_);
	pStrData_Tmp = (uint8_t*)malloc(_DATA_SIZE_);
	
	SerialReadComm(rxbuff, pStrCmd_Tmp, pStrOpt_Tmp, pStrData_Tmp);
	
	if (tProcess == NONE)
	{
		recieve_flag = 1;		
	}
	else if (tProcess == CRUN)
	{
		if ((StrCompare(pStrCmd_Tmp, (uint8_t*)"SVEL",4) == 1)||(StrCompare(pStrCmd_Tmp,(uint8_t*) "STOP",4)==1))
		{
			recieve_flag = 1;
		}
	}
	if (recieve_flag == 1)
	{
		g_Flow_control[0] = ACK[0];
		memcpy(g_strCommand, pStrCmd_Tmp, _CMD_SIZE_);
		memcpy(g_strOpt, pStrOpt_Tmp, _OPT_SIZE_);
		memcpy(g_strData, pStrData_Tmp, _DATA_SIZE_);
		bDataAvailable = 1;
	}
	else	
	{
		g_Flow_control[0] = NAK[0];
		bDataAvailable = 1;
		SerialWriteComm(pStrCmd_Tmp, pStrOpt_Tmp, pStrData_Tmp, txbuff, g_Flow_control);
		g_Flow_control[0] = ACK[0];
	}
	free(pStrCmd_Tmp);
	free(pStrOpt_Tmp);
	free(pStrData_Tmp);
	recieve_flag = 0;
	DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);
	
	DMA_Cmd(DMA1_Stream2, ENABLE);
	
}


void DMA_User_Init(void)
{	
	// DMA-UART4_RX configuration
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rxbuff;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = _RX_BUFF_SIZE_;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream2, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream2, ENABLE);
	
	/* Enable DMA Interrupt to the highest priority */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Transfer complete interrupt mask */
  DMA_ITConfig(DMA1_Stream2, DMA_IT_TC, ENABLE);
	
	// DMA1-UART4 TX configuration
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &UART4->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)txbuff;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = _TX_BUFF_SIZE_;
	DMA_Init(DMA1_Stream4, &DMA_InitStructure);
	DMA_Cmd(DMA1_Stream4, ENABLE);
	
}
void UART4_User_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	
	/* Connect UART4 pins to AF2 */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
	
	 /* GPIO Configuration for UART4 Tx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* GPIO Configuration for USART Rx */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USARTx configured as follow:
		- BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(UART4, &USART_InitStructure);
	
	/* Enable USART */
  USART_Cmd(UART4, ENABLE);
	
	/* Enable UART4 DMA */
  USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE); 
	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
}


