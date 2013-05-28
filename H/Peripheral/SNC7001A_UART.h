#ifndef _SNC7001A_UART
#define _SNC7001A_UART

extern void UART_Enable_Rx(void);
extern void UART_Disable_Rx(void);
extern void UART_Enable_Tx(void);
extern void UART_Disable_Tx(void);
extern void UART_Set_Buad_Rate(u16 uiBR);
extern void UART_Set_Data_Mode(u16 uiRxLen, u16 uiTxLen);
extern void UART_Set_Parity_Check(u16 uiMode);
extern void UART_Parity_Check_Mode(u16 uiMode);
extern u16  UART_Parity_Check_Result(void);
extern void UART_Write_TxD(u16 uiTx);
extern u16  UART_Read_RxD(void);
extern void UART_Clr_RxD_Flag(void);
extern u16  UART_Rx_Status(void);
#endif