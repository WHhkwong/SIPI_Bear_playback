#ifndef _H_IMAADPCMDec
#define _H_IMAADPCMDec
//==============Application function (user)=============//
void IMAADPCMDec_SetBitRate(short BitNumT,short FrmSize);
void IMAADPCMDec_Out_Init_chL(short *OutBufLAddr, short FrmSize);
short IMAADPCMDec_Process(short DRCCmd);
#endif





