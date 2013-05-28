#ifndef _H_Phaser
#define _H_Phaser

void PlayPhaserEffect(short SampleRate, short PhaseRate, short PhaseFeedBack, short PhaseDryWet, short PhaseStage);
void Phaser_Out_Init(short *OutBufLAddr);
short Phaser_GenProcess(short MCF_Cmd);

#endif