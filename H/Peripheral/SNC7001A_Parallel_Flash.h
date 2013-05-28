#ifndef _SNC7001A_Parallel_Flash
#define _SNC7001A_Parallel_Flash

extern u16  PF_Read_Device_ID(u16 uiCSSelect);
extern u16  PF_Read_Factory_ID(u16 uiCSSelect);
extern void PF_Chip_Erase(u16 uiCSSelect);
extern void PF_Block_Erase(u16 uiCSSelect, u16 uiAddrH, u16 uiAddrL);
extern void PF_Sector_Erase(u16 uiCSSelect, u16 uiAddrH, u16 uiAddrL);
extern void PF_Enable(u16 uiCSSelect, u16 uiDeviceType);
extern void PF_Disable(u16 uiCSSelect);
extern void PF_Reset_CMD(u16 uiCSSelect);
extern void PF_Read_DMA_Mode(u16 uiCSSelect, u16 uiAddrH, u16 uiAddrL, u16 uiLength, u16* p_uiWRAMAddr);
extern void PF_Write_DMA_Mode(u16 uiCSSelect, u16 uiAddrH, u16 uiAddrL, u16 uiLength, u16* p_uiWRAMAddr);
extern void PF_Set_Max_Size(u16 uiSizeSelect);
extern void PF_Set_Access_Cycle_Time(u16 uiCSSelect, u16 uiReadCycle, u16 uiWriteCycle);
extern u16  PF_Erase_Data_Polling(u16 uiCSSelect);
extern u16  PF_Write_DMA_Data_Polling(void);

#endif
