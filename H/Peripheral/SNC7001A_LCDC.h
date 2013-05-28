#ifndef _SNC7001A_LCDC
#define _SNC7001A_LCDC

extern void LCDC_Enable(void);
extern void LCDC_Disable(void);
extern void LCDC_Set_Segment_Common(u16 uiSegNum, u16 uiComNum);
extern void LCDC_Set_LCD_Clock(u16 uiClock);
extern void LCDC_Set_Suspend_LCD_Clock(u16 uiClock);
extern void LCDC_Set_Gray_Palette(u16 uiColor0, u16 uiColor1, u16 uiColor2, u16 uiColor3);
extern void LCDC_Set_Line_Pulse(u16 uiLPD, u16 uiLPW, u16 uiLBW);
extern void LCDC_Set_LACD_Rate(u16 uiLACD);
extern void LCDC_Set_Data_Bus_Width(u16 uiDBW);
extern void LCDC_Set_2Bit_Per_Pixel(void);
extern void LCDC_Set_4Bit_Per_Pixel(void);
extern void LCDC_Fill_Normal_Display_Data(__GENERIC int* pSrcDataAddr, u16* pWRAMAddr, u16 uiDataLen);
extern void LCDC_Normal_Display_On(u16 *pWRAMAddr);

extern u16  LCDC_Set_Suspend_Segment_Common(u16 uiSegNum, u16 uiComNum);
extern u16  LCDC_Fill_Suspend_Display_Data(__GENERIC int* pSrcDataAddr, u16 uiDataLen);
extern void LCDC_Suspend_12M(void);
extern void LCDC_Suspend_6M(void);
extern void LCDC_Suspend_3M(void);
extern void LCDC_Suspend_1P5M(void);
#endif