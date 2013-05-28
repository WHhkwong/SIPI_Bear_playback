#ifndef _H_ChgSpeed
#define _H_ChgSpeed
//==============Application function (user)=============//
//unsigned short ChgSpeedL_In_Init(short *inbuf11,short *inbuf12,short length);
void ChgSpeed_Out_Init_chL(short *OutBufLAddr);
unsigned short GetStatusforDoChgSpeed(void);
void PlayChgSpeed(short chaSpeedLevel);
short ChgSpeedL_Process(short cmd);
//==============Application function (user)=============//
#endif