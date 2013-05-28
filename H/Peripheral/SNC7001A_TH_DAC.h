#ifndef _SNC7001A_TH_DAC
#define _SNC7001A_TH_DAC

    extern void TH_DAC_Turn_On(u16);
    extern void TH_DAC_Turn_Off(void);
    extern void TH_DAC_Sample_Rate_Select(unsigned short uiSR);
    extern void TH_DAC_Reset_FIFO(void);
#endif