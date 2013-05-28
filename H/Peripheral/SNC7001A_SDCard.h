#ifndef	_SNC7001A_SDCard_H
#define	_SNC7001A_SDCard_H

extern void SDC_Disable_Function(void);
extern u16  SDC_4BIT_Init(u16  ui_CMDTimeOutValue, u16  ui_RWTimeOutValueH,u16  ui_RWTimeOutValueL, u16  ui_SDCSpeed);
extern u16  SDC_SPI_Init(u16  ui_CMDTimeOutValue, u16  ui_RWTimeOutValueH,u16  ui_RWTimeOutValueL, u16  ui_SDCSpeed);
extern u16  SDC_Read_Single_Block(u32 sec_cnt, u16 databuf_addr,u16 SDMODE);
extern u16  SDC_Read_Multi_Block(u32 sec_cnt, u16 databuf_addr, u16 type,u16 SDMODE);
extern u16  SDC_Write_Single_Block(u32 sec_cnt, u16 databuf_addr,u16 SDMODE);
extern u16  SDC_Write_Multi_Block(u32 sec_cnt, u16 databuf_addr, u16 type,u16 SDMODE);
extern u16  SDC_Erase_Function(u32 start_sec_cnt, u32 end_sec_cnt);
extern u16  SDC_LBA_Write(u32 BULKOUT_LBA,u32  TotalLen, u32 DataResidue, u16  Bulk_BUF);
extern u16  SDC_LBA_Read(u32 BULKIN_LBA,u32  TotalLen, u32 DataResidue, u16  Bulk_BUF);

extern u16  g_uiCard_Ver,g_uiCard_Type;
extern u16  g_uiCMDTimeOutValue;
extern u32  g_uiTotal_Block_Num;
#endif //_SDC_H