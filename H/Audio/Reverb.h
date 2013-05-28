#ifndef _H_Reverb
#define _H_Reverb
void SetReverbRAMBank(short RamBk);
void Reverb_Out_Init_chL(short *OutBufLAddr);
void SetReverbParameter(short Sel1D_2D, short XDirectDelay, short YDirectDelay);
short Reverb_GenProcess(short Reverb_Cmd);

#endif