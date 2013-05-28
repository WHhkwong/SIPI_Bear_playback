#ifndef _SNC7001A_SD_DAC
#define _SNC7001A_SD_DAC

extern void SD_DAC_Volume_Control(u16 volume);
extern void SD_DAC_Turn_On(u16 DAC_SR);
extern void SD_DAC_Turn_Off(void);
extern void SD_DAC_Mute_OnOff(u16 Status);
extern void SD_DAC_De_Emphasis_OnOff(u16 Status);
extern void SD_DAC_Pause(void);
extern void SD_DAC_PauseResume(void);

extern unsigned int g_FadeOutFlag;
extern signed int g_DACTailValue;
#endif