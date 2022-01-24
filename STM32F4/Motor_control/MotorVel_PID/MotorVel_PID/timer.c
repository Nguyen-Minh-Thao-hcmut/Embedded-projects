#include "timer.h"
#include "pid.h"
#include "motor.h"
extern PROCESS_t tProcess;
extern PROFILE_t tProfile;
extern PID_CONTROL_t tPIDControl;
extern uint16_t g_nIndex;
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
	TIM_TimeBaseStructure.TIM_Period = PreScalerValue;
	TIM_TimeBaseStructure.TIM_Prescaler = 8399;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM2 -> CR1 |= ((0x0001)<<7);
	TIM_PrescalerConfig(TIM2, PreScalerValue, TIM_PSCReloadMode_Immediate);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void TIM2_IRQHandler(void)
{
	TIM_ClearFlag(TIM2, TIM_SR_UIF);
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
      break;
		case STOP:
			MotorReset(tPIDControl.dFrequency);
			tProcess = NONE;
			break;
    }
	//
	
}



