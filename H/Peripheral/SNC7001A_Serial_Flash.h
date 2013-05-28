#ifndef _SNC7001A_Serial_Flash
#define _SNC7001A_Serial_Flash

extern void SF_Enable(void);
extern void SF_Disable(void);
extern u16  SF_Read_Factory_ID(void);
extern u16  SF_Read_Status(void);
extern void SF_Write_Status(u16 uiStatus);
extern void SF_Set_Baud_Rate(u16 uiBR);
extern void SF_Run_Program_Mode(u16 uiReadMode);
extern void SF_Chip_Erase(void);
extern void SF_Sector_Erase(u16 uiAddrH, u16 uiAddrL);
extern void SF_Block_Erase(u16 uiAddrH, u16 uiAddrL);
extern void SF_Read_DMA_Mode(u16 uiMode, u16 uiSPIAddrH, u16 uiSPIAddrL, u16 uiLength, u16* p_uiWRAMAddr);
extern void SF_Write_DMA_Mode(u16 uiMode, u16 uiSPIAddrH, u16 uiSPIAddrL, u16 uiLength, u16* p_uiWRAMAddr);
extern void SF_Power_Down(void);
extern void SF_Wake_Up(void);
extern void SF_Enable_Quad_Mode(void);
extern void SF_Disable_Quad_Mode(void);
extern void SF_Set_Deselect_Cycle(u16 uiDSCycle);
extern u16  SF_Erase_Data_Polling(void);
extern u16  SF_Write_DMA_Data_Polling(void);

#endif
