/*#ifndef _H_Phaser
#define _H_Phaser*/

#ifndef _H_Vibrato
#define _H_Vibrato

void PlayVibratoEffect(short SampleRate, short modefreq, short Vibrato_Width);
void Vibrato_Out_Init(short *OutBufLAddr);
short Vibrato_GenProcess(short MCF_Cmd);

#endif