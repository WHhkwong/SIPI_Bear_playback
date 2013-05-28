#ifndef _H_IMAADPCMDecR1
#define _H_IMAADPCMDecR1
//==============Application function (user)=============//
void IMAADPCMDecR1_SetBitRate(short BitNumT,short FrmSize);
void IMAADPCMDec_Out_Init_chR1(short *OutBufLAddr, short FrmSizeR);
short IMAADPCMDec_ProcessR1(short DRCCmd);
#endif





