#include "stm32f4xx.h"
#include "system_timetick.h"
#include "serial.h"
#include "motor.h"
#include "pid.h"
#include "timer.h"


#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


extern uint8_t recieve_flag;
extern PID_CONTROL_t tPIDControl;
extern PROFILE_t tProfile;
extern PROCESS_t tProcess;
extern uint32_t nPulse1;
extern uint32_t g_nPrePulse;
//extern uint8_t g_nExpectedFrame;
extern uint8_t bDataAvailable;
extern uint8_t txbuff[_TX_BUFF_SIZE_];
extern uint8_t rxbuff[_RX_BUFF_SIZE_];
extern uint8_t g_strCommand[_CMD_SIZE_];
extern uint8_t g_strOpt[_OPT_SIZE_];
extern uint8_t g_strData[_DATA_SIZE_];
extern uint8_t g_Flow_control[];
extern uint8_t ACK[];

extern uint32_t g_nActPulse;
extern uint32_t g_nCmdPulse;
extern uint16_t g_nIndex;
extern int16_t g_nDutyCycle;


uint8_t g_strTxCommand[_CMD_SIZE_];
uint8_t g_nTxOption[_OPT_SIZE_];
uint8_t g_nTxData[_DATA_SIZE_];
int gIndexTx = 0;
/*

*/
void delay_01ms(uint16_t period);

void init_main(void);

int main()
{
	init_main();
	while(1)
	{
		 if (bDataAvailable == 1)
    {
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
      if (StrCompare(g_strCommand, (uint8_t *)"SPID", _CMD_SIZE_)) 
      {
        tProcess = (tProcess == NONE)? SPID : tProcess;
      }
      else if (StrCompare(g_strCommand, (uint8_t *)"SVEL", _CMD_SIZE_))
      {
        if(tProcess == NONE)
				{
					tProcess = SVEL;
				}
				else if(tProcess == CRUN)
				{
					tProfile.dVelCmd =  (float)(g_strData[0] * 100 + g_strData[1] + g_strData[2]/10); // Change Vel on the fly Vd: Vel = 3456.5 data[0] = 34, data[1] = 56, data[2] = 5
			     memcpy(g_strCommand, (uint8_t*)"CRUN",_CMD_SIZE_);
				}
      }
 
      else if (StrCompare(g_strCommand, (uint8_t *)"CRUN", _CMD_SIZE_))
      {
        tProcess = CRUN_RES;
      }
      else if (StrCompare(g_strCommand, (uint8_t *)"STOP", _CMD_SIZE_))
      {
        tProcess =  STOP_RES;
      }
      else
      {
        tProcess = NONE;
      }
			bDataAvailable = 0;
    }
		
		
    switch (tProcess)
    {
    case NONE:
      break;
    case SPID:
			bDataAvailable = 1;
			SerialWriteComm(g_strCommand, g_strOpt, g_strData, txbuff, g_Flow_control);
			

      /* Get PID params and PWM Frequency */
			tPIDControl.dKp = (float)g_strData[0] + (float)g_strData[1] / 10; // Vd: Kp = 30.4 thi g_strData[0] = 30, g_strData[1] = 4
      tPIDControl.dKi = (float)g_strData[2] + (float)g_strData[3] / 10; //Vd: Ki = 30.4 thi g_strData[2] = 30, g_strData[3] = 4
      tPIDControl.dKd = (float)g_strData[4] + (float)g_strData[5] / (pow((float)10, (float)g_strData[6])); // Kd = 30.0005 thi g_strData[4] = 30, g_strData[5] = 5, g_strData[5] = 4
			tPIDControl.dFrequency = (uint16_t) (g_strData[7]*100 + g_strData[8]); // fPwm = 21325 Hz thi g_strData[7] = 2, g_strData[8] = 13, g_strData[9] = 25
			
			MotorInit(tPIDControl.dFrequency);
		  TIM_SetCounter(TIM4,32768);
			tProcess = NONE;
      break;
		case SVEL:
			bDataAvailable = 1;
		  
			SerialWriteComm(g_strCommand, g_strOpt, g_strData, txbuff, g_Flow_control);
			tProfile.dVelCmd =  (float)(g_strData[0] * 100 + g_strData[1] + g_strData[2]/10);
			tProcess = NONE;
			break;
    case CRUN_RES:
			bDataAvailable = 1;
			SerialWriteComm(g_strCommand, g_strOpt, g_strData, txbuff, g_Flow_control);
			g_nCmdPulse = 0;
			PIDReset(&tPIDControl);
			TIM_SetCounter(TIM4, _TIM4_CNT_VAL_INIT_);
			g_nIndex = 0;
			
			MotorStart();
			
      tProcess = CRUN;
      break;
    case CRUN:
      break;
		case STOP_RES:
			bDataAvailable = 1;
			SerialWriteComm(g_strCommand, g_strOpt, g_strData, txbuff, g_Flow_control);					
			tProcess = STOP;
			break;
		case STOP:
			break;
		}

	}

}

void init_main(void)
{
	timer2_Config();
	UART4_User_Init();
	DMA_User_Init();
	GPIO_Config();
	TIM3_GPIOC_Config();
	PWM_Init(_TIM3_CLK_, tPIDControl.dFrequency,0);
	Encoder_Config();
	PIDInit(&tPIDControl);
	
}

void delay_01ms(uint16_t period){

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  	TIM6->PSC = 8399;		// clk = SystemCoreClock /2 /(PSC+1) = 10KHz
  	TIM6->ARR = period-1;
  	TIM6->CNT = 0;
  	TIM6->EGR = 1;		// update registers;

  	TIM6->SR  = 0;		// clear overflow flag
  	TIM6->CR1 = 1;		// enable Timer6

  	while (!TIM6->SR);
    
  	TIM6->CR1 = 0;		// stop Timer6
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, DISABLE);
}
