#ifndef _H_IMAADPCMEnc
#define _H_IMAADPCMEnc
//==============Application function (user)=============//
//void IMAADPCMEnc_In_Init(short *InBufLAddr, short FillLength);
void IMAADPCMEnc_Out_Init(short *OutBufLAddr, short OutSize);
short IMAADPCMEnc_Process(short DRCCmd);
void IMAADPCMEnc_SetBitRate(short BitNumT, short FrmSize, short StandardFlag);
#endif





