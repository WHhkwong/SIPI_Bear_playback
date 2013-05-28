#ifndef _SNC7001A_Series_I2S
#define _SNC7001A_Series_I2S

extern void I2S_TR_Select(unsigned int);
extern void I2S_Enable(void);
extern void I2S_Disable(void);
extern void I2S_Format_Select(unsigned int);
extern void I2S_Word_Length_Select(unsigned int);
extern void I2S_FIFO_Control(unsigned int);
extern void I2S_Sample_Rate_Select(unsigned int);
extern void I2S_Reset_FIFO(unsigned int);
extern void I2S_Trigger_Start(void);
extern void I2S_Trigger_Stop(void);
#endif