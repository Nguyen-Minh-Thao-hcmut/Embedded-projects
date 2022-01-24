#include "motor.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <timer.h>
#include <pid.h>

PROCESS_t tProcess = NONE;
PID_CONTROL_t tPIDControl;
PROFILE_t tProfile;
int32_t gIndex_check = 0;
int32_t g_nDutyCycle;

uint32_t g_nActPulse;
uint32_t g_nCmdPulse;
uint16_t g_nIndex = 0;
uint32_t g_nPrePulse = 32768;
uint16_t rate = 0;
uint32_t nPulse1;
extern float g_dPIDError;
void MotorInit(uint16_t PWM_Freq)
{
	
	//Start PWM with PWM_Freq and 0% duty cycle
	uint16_t ARR_Value;
	ARR_Value = (uint16_t)((_TIM3_CLK_/PWM_Freq) - 1);
	TIM3 -> ARR = ARR_Value;
	TIM3 -> CCR1 = 0;

	TIM_SetCounter(TIM2, 0);
	TIM_SetCounter(TIM3, 0);
	TIM_SetCounter(TIM4, _TIM4_CNT_VAL_INIT_);

	PIDReset(&tPIDControl);
	//PIDInit(&tPIDControl, 1., 0., 0.00);
	MotorSetDir(1);
}

void PWM_Frequency_config(uint16_t dFrequency)
{
	uint32_t ARR_Value1;
	ARR_Value1 = (uint16_t)((_TIM3_CLK_/dFrequency) - 1);
	TIM3 -> ARR = ARR_Value1;
	TIM3 -> CCR1 = 0;
}
void MotorReset(uint16_t dFrequency)
{
	TIM3 -> CCR1 = 0;
	//TIM_Cmd(TIM2, DISABLE);
	//TIM_Cmd(TIM3, DISABLE);
	//TIM_Cmd(TIM4, DISABLE);
	TIM3 -> ARR = (uint16_t)((_TIM3_CLK_/3000)-1);
	
	//TIM_SetCounter(TIM3, 0);
	TIM_SetCounter(TIM4, _TIM4_CNT_VAL_INIT_);
	//TIM_SetCounter(TIM2, 0);
	PIDReset(&tPIDControl);
	g_nCmdPulse = 0;
	g_nActPulse = 0;
	g_nIndex = 0;
	MotorSetDir(1);
	
}
void MotorStart(void)
{
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	//HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
	//HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);
}

void MotorSetDir(int8_t nDir)
{
	switch (nDir)
	{
		case 0:
			//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11, GPIO_PIN_RESET);
			GPIO_ResetBits(GPIOB, GPIO_Pin_11);
			//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10, GPIO_PIN_SET);
			GPIO_SetBits(GPIOB, GPIO_Pin_10);
			break;
		case 1:
			GPIO_SetBits(GPIOB,GPIO_Pin_11);
			//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10, GPIO_PIN_RESET);
			GPIO_ResetBits(GPIOB, GPIO_Pin_10);
			break;
		default:
			break;
	}
}


void MotorSetDuty(uint16_t nDuty)
{
	TIM3->CCR1 = nDuty ;
}

uint16_t ConvertPulseToVel(int32_t nPulse)
{
	float nVel = ((float)nPulse*600 )/(1 * 2 * 3 * 45 ); //RPM VD 10ms -> 10 xung => 10  ms = 0.05 vòng => 1 phút = 0.05 * (60 000/10)
	return (uint16_t)nVel;
}


uint32_t ConvertVelToPulse(float nVel, int* nDir)
{
	float nPulse = 0;
	if (nVel >=0){
		*(nDir) = 1;
	}
	else {
		*(nDir) = 0;
	}
	nPulse = (nVel)*( 1 * 2 * 11* 34)/600;
	return (uint32_t) nPulse;
}


void MotorGetPulse(uint32_t *nPulse)
{
	*nPulse = TIM_GetCounter(TIM4);
	 TIM_SetCounter(TIM4,32768);
}




void MotorMoveVel(float nVel)
{
	int nDir;
	
	uint32_t nVelPulse;
	MotorGetPulse(&nVelPulse);
	g_nActPulse = nVelPulse-32768;
	g_nCmdPulse = ConvertVelToPulse(nVel, &nDir);
	g_nDutyCycle += (int16_t)PIDCompute(&tPIDControl, g_nCmdPulse, g_nActPulse, 0.01f);
	if (g_nDutyCycle >= 0)
	{
		MotorSetDir(1);
		MotorSetDuty(abs(g_nDutyCycle));
	}
	else if (g_nDutyCycle < 0)
	{
		MotorSetDir(0);
		MotorSetDuty(abs(g_nDutyCycle));
	}
	if (g_nIndex < 5)
	{
		tPIDControl.nActVelSample[g_nIndex] = (uint16_t)ConvertPulseToVel(g_nActPulse);
		g_nIndex ++;
	}
	
}

void TIM3_GPIOC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Connect TIM3 pins to AF2 */  
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
	
}


void PWM_Init(uint32_t TIM3_Cnt_Clk, uint32_t TIM3_OutPut_Clk, float TIM3_CH1_Duty)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t PrescalerValue = 0;
	
	uint32_t ARR_Value3 = 0;
	uint16_t CCR1_Val = 0;

	/* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock /2) / TIM3_Cnt_Clk) - 1;
	// Compute the pwm frequency
	ARR_Value3 = (uint32_t)((TIM3_Cnt_Clk/TIM3_OutPut_Clk) - 1);
	
	// Compute pwm duty cycle
	CCR1_Val = (uint16_t) ((TIM3_CH1_Duty/100)*ARR_Value3);
	
	  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = ARR_Value3;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
}

void Encoder_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef			TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	/*Enable clock for timers*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	

	
													
	/*Configure for Encoder interface 1*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	
	/* Configure Timer for Encoder Interface 1*/		
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	TIM_TimeBaseInitStructure.TIM_Period=_ENCODER_ARR_VALUE_;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);


	/*Configure Encoder Interface 1 capture channel*/
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1 | TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICFilter=0;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	/*Configure Encoder Interface 2 capture channel*/

	/*Configure Encoder Interface 1*/
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

	/*Reset Counter 1*/
	TIM_SetCounter(TIM4, _TIM4_CNT_VAL_INIT_); // Need to check this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*Reset Counter 2*/
	//TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
	/*Enable 1nd Timer */
}

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
}


