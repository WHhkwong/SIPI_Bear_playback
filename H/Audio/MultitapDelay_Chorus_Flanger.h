#ifndef _H_MCF
#define _H_MCF

void PlayMCFEffect(short MCFEffectMode, short SampleRate);
void MCF_Out_Init(short *OutBufLAddr);
short MCF_GenProcess(short MCF_Cmd);

#endif