#ifndef _SNC7001A_MCU_8080
#define _SNC7001A_MCU_8080

extern void MCU_8080_Enable(void);
extern void MCU_8080_Disable(void);
extern void MCU_8080_Set_DataMode(u16 uiMode);
extern void MCU_8080_Set_Access_Pulse_Duration(u16 uiHighPulse, u16 uiLowPulse);
extern void MCU_8080_Write_Command(u16 uiCMD);
extern void MCU_8080_Write_DataWord(u16 uiData);
extern void MCU_8080_Write_DataWord_LBFirst(u16 uiData);
extern void MCU_8080_Write_DataWord_HBFirst(u16 uiData);
extern u16  MCU_8080_Read_DataWord(void);
extern u16  MCU_8080_Read_DataWord_LBFirst(void);
extern u16  MCU_8080_Read_DataWord_HBFirst(void);
extern void MCU_8080_DMA_Write_Mode(u16 uiMode, u16* p_uiWRAMAddr, u16 uiLength);
extern void MCU_8080_DMA_Read_Mode(u16 uiMode, u16* p_uiWRAMAddr, u16 uiLength);

#endif