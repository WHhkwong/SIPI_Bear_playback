/*#ifndef _H_Phaser
#define _H_Phaser*/

#ifndef _H_Tremolo
#define _H_Tremolo



void PlayTremoloEffect(short SampleRate, short modefreq, short Tremolo_Width);
void Tremolo_Out_Init(short *OutBufLAddr);
short Tremolo_GenProcess(short MCF_Cmd);

#endif