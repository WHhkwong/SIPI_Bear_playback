#ifndef _H_MUSIC96
#define _H_MUSIC96
void Music96_Init(void);
short Music96_GetChannel(void);
short Music96_GetSampleRate(void);
short Music96_Process(short cmd);
short Music96_Is_End(void);
void Music96_OutCH1_Init(__RAM short *DecOutBuf , short length);
#endif
