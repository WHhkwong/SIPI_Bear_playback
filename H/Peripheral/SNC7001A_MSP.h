#ifndef  _SNC7001A_Serial_MSP
#define	 _SNC7001A_Serial_MSP

	extern void MSP_Enable(void);
	extern void MSP_Disable(void);
	extern void MSP_Set_BaudRate(u16 uiBR);
	extern u16  MSP_Set_Start_Address(u16 uiDeviceAddr);
	extern u16  MSP_Set_Restart_Address(u16 uiDeviceAddr);
	extern void MSP_Set_Stop(void);
	extern u16  MSP_Check_ACK(void);
	extern u16  MSP_Receive_Data(u16 uiStatus);
	extern void MSP_Receive_Data_Continue(u16* p_uiWRAMAddr, u16 uiLength);
	extern void MSP_Send_Data(u16 uiData);
	extern u16  MSP_Send_Data_Continue(u16* p_uiWRAMAddr, u16 uiLength);
#endif