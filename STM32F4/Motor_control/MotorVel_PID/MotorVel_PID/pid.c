#include "pid.h"
#include "timer.h"
#include "motor.h"
float g_dPIDError = 0;

void PIDReset(PID_CONTROL_t* PID_Ctrl)
{
	PID_Ctrl->dIntergral = 0.0f;
	PID_Ctrl->dErrorTerm = 0.0f;
	g_dPIDError = 0;
}

void PIDInit(PID_CONTROL_t* PID_Ctrl)
{
	//Set default value to PID_Control variable
	PID_Ctrl->dKp = 1;
	PID_Ctrl->dKi = 0;
	PID_Ctrl->dKd = 0;
	PID_Ctrl -> dFrequency = 3000;
	PID_Ctrl -> dErrorTerm = 0;
	PID_Ctrl -> dIntergral = 0;
}

void PID_Check_and_Set(PID_CONTROL_t* PID_Ctrl, float dKp, float dKi, float dKd, int nFrequency)
{
	PID_Ctrl -> dKp = (dKp <= 0.0f)? 1: dKp;
	PID_Ctrl ->	dKi = (dKi < 0.0f)? 0: dKi;
	PID_Ctrl -> dKd = (dKd < 0.0f)? 0: dKd;
	PID_Ctrl -> dFrequency = (0 < nFrequency < 65535)? nFrequency : 3000;
}


float PIDCompute(PID_CONTROL_t* PID_Ctrl, float dCmdValue, float dActValue, float dTs)
{
	float dPIDResult;
	float dP = 0, dI = 0, dD = 0;
	g_dPIDError = dCmdValue - dActValue;
	
	dP = (PID_Ctrl->dKp)*g_dPIDError;
	PID_Ctrl->dIntergral += g_dPIDError;
	dI = (PID_Ctrl->dKi)*(dTs/2)*(PID_Ctrl->dIntergral);
	dD = (PID_Ctrl->dKd)*(g_dPIDError - PID_Ctrl->dErrorTerm)/dTs;
	dPIDResult = dP + dI + dD;
	PID_Ctrl->dErrorTerm = g_dPIDError;
	return dPIDResult;
}
