/*#ifndef _H_Phaser
#define _H_Phaser*/


#ifndef _H_WahWah
#define _H_WahWah

void PlayWahWahEffect(short SampleRate, short CentrlFreq, short WahWah_depth, short RATE_wah);
void WahWah_Out_Init(short *OutBufLAddr);
short WahWah_GenProcess(short MCF_Cmd);

#endif