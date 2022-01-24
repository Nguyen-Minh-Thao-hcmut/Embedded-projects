#include "timer.h"
#include "pid.h"
#include "motor.h"
#include "serial.h"
extern PROCESS_t tProcess;
extern PROFILE_t tProfile;
extern PID_CONTROL_t tPIDControl;
extern uint16_t g_nIndex;
extern uint8_t g_strCommand[_CMD_SIZE_];
extern uint8_t g_strOpt[_OPT_SIZE_];
extern uint8_t g_strData[_DATA_SIZE_];
extern uint8_t g_strTxCommand[_CMD_SIZE_];
extern uint8_t g_nTxOption[_OPT_SIZE_];
extern uint8_t g_nTxData[_DATA_SIZE_];
extern uint8_t bDataAvailable;
extern uint8_t txbuff[_TX_BUFF_SIZE_];
extern uint8_t g_Flow_control[];
void timer2_Config(void)
{
	//Timer2 interrupt per 10ms
	uint16_t PreScalerValue = 99;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	// Time base configuration
	TIM_TimeBaseStructure.TIM_Period = 41999;
	TIM_TimeBaseStructure.TIM_Prescaler = PreScalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM2 -> CR1 |= ((0x0001)<<7);
	TIM_PrescalerConfig(TIM2, PreScalerValue, TIM_PSCReloadMode_Immediate);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void TIM2_IRQHandler(void)
{
	
	//Write process control code here
	switch (tProcess)
    {
    case NONE:
      break;
    case SPID:
      break;
		case CRUN_RES:
			break;
		case SVEL:
			break;
    case CRUN:
      MotorMoveVel(tProfile.dVelCmd);
			if (g_nIndex == 5)
			{
				int index1;
				memcpy(g_strTxCommand, g_strCommand, 4);
				memcpy(g_nTxOption, g_strOpt, 3);
				for (index1 = 0; index1 <= g_nIndex - 1; index1++)
				{
				
				g_nTxData[2*index1] = (tPIDControl.nActVelSample[index1]&0xFF00) >> 8;
				g_nTxData[2*index1 + 1] = (tPIDControl.nActVelSample[index1]&0xFF);
				
				/*
        memset(g_strTxCommand, 0x00, 4);
        memset(g_nTxOption, 0x00, 3);
        memset(g_nTxData, 0x00, 10);
					*/       
				}
				bDataAvailable = 1;
				SerialWriteComm(g_strTxCommand, g_nTxOption, g_nTxData,txbuff, g_Flow_control);
				bDataAvailable = 0;
				g_nIndex = 0;
			}
      break;
		case STOP_RES:
			break;
		case STOP:
			MotorSetDuty(0);
			DMA_Cmd(DMA1_Stream4, DISABLE);
			tProcess = NONE;
			break;
    }
		TIM_ClearFlag(TIM2, TIM_SR_UIF);
		
	//
	
}



