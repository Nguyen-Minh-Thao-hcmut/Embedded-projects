#ifndef __PID_H
#define __PID_H
#define _SAMPLE_NUM_ 5
#include "stm32f4xx.h"
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
	float dKp, dKi, dKd;
	int16_t dFrequency;
	float dErrorTerm;
	float dIntergral;
	//uint16_t nSampleTuningPID[200];
	int16_t nActVelSample[5];
} PID_CONTROL_t;

typedef struct 
{	
  float dVelCmd;
} PROFILE_t;

typedef enum
{
  NONE = 1,
  SPID,
	SVEL,
  CRUN,
  CRUN_RES,
	STOP,
} PROCESS_t;

extern void PIDReset(PID_CONTROL_t *PID_Ctrl);
extern void PIDInit(PID_CONTROL_t *PID_Ctrl);
extern void PID_Check_and_Set(PID_CONTROL_t* PID_Ctrl, float dKp, float dKi, float dKd, int nFrequency);
extern float PIDCompute(PID_CONTROL_t *PID_Ctrl, float dCmdValue, float dActValue, float dTs);
#endif
