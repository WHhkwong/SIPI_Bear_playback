#ifndef  Audio_Playback_External_Para_H
#define  Audio_Playback_External_Para_H

//==================Extern function Start===========================
extern void Audio_Decode_Process(void);
extern void AudioPlay_Enable(void);
//======================General Play Function ======================

extern void PlayFore(__GENERIC int *Inptr);
extern void PlayBack(__GENERIC int *Inptr);


extern short PlayForeEnd_Check(void);
extern short PlayBackEnd_Check(void);

extern void PlayFore_Stop(void);
extern void PlayBack_Stop(void);

extern void PlayFore_Pause(void);
extern void PlayBack_Pause(void);

extern void PlayFore_PauseResume(void);
extern void PlayBack_PauseResume(void);

extern void PlayFore_VOL_SET (short foreground_volume);
extern void PlayBack_VOL_SET (short background_volume);

//==================================================================


//================= WaveMark function  ==============================
void WaveMarkF_Enable(void);
void WaveMarkB_Enable(void);
void WaveMark_Routine_F(void);
void WaveMark_Routine_B(void);
//===================================================================


//================= Orientation or AB Play function  =================

extern void PlayOrientationF(short UpDown_SelT, long OffsetTimeT);
extern void PlayOrientationB(short UpDown_SelT, short OffsetTimeT);
extern void AB_PlayF(long StartTime, long EndTime);
extern void AB_PlayB(long StartTime, long EndTime);

//=====================================================================


extern void AudioPlay_Enable(void);


//==================Extern function End===============================



//==================Extern Variables Start  ===========================

//======================KeyScan Routine================================

extern unsigned short g_uiKeyScan_8ms;
extern unsigned short g_uiPreKeyValue;
extern unsigned short g_uiKeyValue;
//=====================================================================

//==================== WaveMark Usage=================================
extern __RAM  unsigned short  PlayWaveMarkFlagF;
extern	__RAM  unsigned short  PlayWaveMarkFlagB;
extern	__RAM  unsigned short g_uiWaveMarkN_F;
extern	__RAM  unsigned short g_uiWaveMarkN_B; 
extern	__RAM short g_uiMarkCodeF ;
extern	__RAM short g_uiMarkCodeB ;


extern	__RAM  long g_uiWaveMark_1ms_CounterF;
extern	__RAM  long g_uiWaveMark_1ms_CounterB;
extern	__RAM  short g_uiWaveMark_Time_Counter;
extern  __RAM short  samplerate ;
extern __RAM  short  WaveMarkF_F ;
extern __RAM  short  WaveMarkF_B ;

//=====================================================================



//================== extern Variables Start  ===========================
extern unsigned short OddEven;
extern unsigned short Audio32_16KHz;
extern unsigned short Snx8K_8KHz;
//==================Variables End================================


#endif