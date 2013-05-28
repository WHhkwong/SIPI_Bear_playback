#ifndef _H_IMAADPCMDecR
#define _H_IMAADPCMDecR
//==============Application function (user)=============//
void IMAADPCMDecR_SetBitRate(short BitNumT,short FrmSize);
void IMAADPCMDec_Out_Init_chR(short *OutBufLAddr, short FrmSizeR);
short IMAADPCMDec_ProcessR(short DRCCmd);
#endif





