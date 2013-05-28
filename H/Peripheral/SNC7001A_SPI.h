#ifndef _SNC7001A_Series_SPI
#define _SNC7001A_Series_SPI

extern void SPI_Enable(u16);
extern void SPI_Disable(void);
extern void SPI_Set_Baud_Rate(u16);
extern void SPI_Set_Interface_Mode(u16);
extern void SPI_SW_CS1_Signal(u16);
extern void SPI_SW_CS2_Signal(u16);
extern void SPI_HW_CS1_Setting(u16);
extern void SPI_HW_CS2_Setting(u16);
extern void SPI_Set_Access_Mode(u16, u16);
extern u16  SPI_Access_Data(unsigned int *p_uiWRAM, unsigned int uiBitLength);

extern void SPI_RDID(unsigned int *p_uiWRAM);
extern u16  SPI_RDSR(void);
extern void SPI_WREN(void);
extern void SPI_WRSR(unsigned int uiStatus);
extern void SPI_Chip_Erase(void);
extern void SPI_Block_Erase(unsigned int uiAddrH, unsigned int uiAddrL);
extern void SPI_Sector_Erase(unsigned int uiAddrH, unsigned int uiAddrL);
extern u16  SPI_Byte_Read(unsigned int uiAddrH, unsigned int uiAddrL);
extern void SPI_Byte_Write(unsigned int uiAddrH, unsigned int uiAddrL, unsigned int uiData);
extern u16  SPI_Word_Read(unsigned int uiAddrH, unsigned int uiAddrL);
extern void SPI_Word_Write(unsigned int uiAddrH, unsigned int uiAddrL, unsigned int uiData);
extern void SPI_Sequential_Read(u16 uiAddrH, u16 uiAddrL, u16 uiLen, u16*p_uiWRAM);
extern void SPI_Sequential_Read_Dual(u16 uiAddrH, u16 uiAddrL,u16 uiLen, u16* p_uiWRAM);
extern void SPI_Sequential_Read_Quad(u16 uiAddrH, u16 uiAddrL, u16 uiLen, u16*p_uiWRAM);
extern void SPI_Page_Write(u16 uiAddrH, u16 uiAddrL, u16 uiLen, u16*p_uiWRAM);
extern void SPI_Page_Write_Quad(u16 uiAddrH, u16 uiAddrL, u16 uiLen, u16*p_uiWRAM);
extern u16  SPI_Data_Polling(void);
#endif
