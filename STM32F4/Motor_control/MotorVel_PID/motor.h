#ifndef __MOTOR_H
#define __MOTOR_H
// Encoder define
#define _RATIO_ 45
#define _PULSE_PER_CHANNEL_ 3
#define _CHANNEL_NUM_ 2
#define _PULSE_MODE_ 1
#define _ARR_VALUE_ 6999
#define _ENCODER_ARR_VALUE_ 0xFFFF
#define _TIM4_CNT_VAL_INIT_ 32768
#define _TIM3_CLK_ 84000000
#define _SAMPLE_TIME_ 10
#include "stm32f4xx.h"
#include <stdlib.h>
#include <stdbool.h>


extern void MotorSetDir(int8_t nDir);
extern void MotorSetDuty(uint16_t nDuty);
extern void MotorInit(uint16_t PWM_Freq);
extern uint32_t ConvertVelToPulse(float nVel, int* Dir);
extern uint16_t ConvertPulseToVel(int32_t nPulse);
extern void MotorGetPulse(uint32_t *nPulse);
extern void MotorMoveVel(float nVel);
extern void TIM3_GPIOC_Config(void);
extern void PWM_Init(uint32_t TIM3_Cnt_Clk, uint32_t TIM3_OutPut_Clk, float TIM3_CH1_Duty);
extern void PWM_Frequency_config(uint16_t dFrequency);
extern void Encoder_Config(void);
extern void MotorStart(void);
extern void MotorReset(uint16_t dFrequency);
extern void GPIO_Config(void);
#endif
