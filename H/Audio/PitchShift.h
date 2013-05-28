#ifndef _H_PitchShift
#define _H_PitchShift
//==============Application function (user)=============//
void SetRobotVoice(short Sel);
void PitchShift_Out_Init_chL(short *OutBufLAddr);
void PlayPitchShiftSet(short pitch_level,short InSampleRate);
short PitchShift_GenProcess(short PitchShift_Cmd);
unsigned short GetStatusforDoPitchShift(void);
//==============Application function (user)=============//
#endif