#ifndef _SNC7001A_CIS
#define _SNC7001A_CIS

extern void CIS_Effect_Setting( u16 ui_mode,u16 ui_LineAdjust,u16 ui_PixelAdjust);
extern void CIS_Transfer_Setting(u16 ui_ColumNum, u16 ui_RowNum);
extern void CIS_Enable_Transfer(void);
extern void CIS_Controller_Setting( u16 ui_CtrlPar);
extern void CIS_Clr_LineBuf0_Flag(void);
extern void CIS_Clr_LineBuf1_Flag(void);
extern void CIS_Clr_LineBuf2_Flag(void);
extern u16 CIS_LineBuf0_Flag_R(void);
extern u16 CIS_LineBuf1_Flag_R(void);
extern u16 CIS_LineBuf2_Flag_R(void);
extern void CIS_LineBuf0_Setting(u16 );
extern void CIS_LineBuf1_Setting(u16 );
extern void CIS_LineBuf2_Setting(u16 );
extern u16 CIS_DLL_Setting(void);
extern void CIS_MSP_Init(unsigned uiDeviceAddr, unsigned int uiBR);
extern void CIS_Reg_Write(u16 reg_addr, u16 value);
extern u16 CIS_Reg_Read(u16 reg_addr);
#endif