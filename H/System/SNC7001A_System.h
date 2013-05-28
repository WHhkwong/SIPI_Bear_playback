#ifndef	_SNC7001A_System_inc_H_
#define	_SNC7001A_System_inc_H_

extern void Clr_CIS_HREF_Req(void);
extern void Clr_DMA_CIS_Req(void);
extern void Clr_DMA_NF_Req(void);
extern void Clr_DMA_USB_Req(void);
extern void Clr_I2S_Req(void);
extern void Clr_MSP_Req(void);
extern void Clr_NF_Req(void);
extern void Clr_P00_Req(void);
extern void Clr_P01_Req(void);
extern void Clr_P02_Req(void);
extern void Clr_RTC_Req(void);
extern void Clr_SAR_ADC_Req(void);
extern void Clr_SD_ADC_Req(void);
extern void Clr_SD_DAC_Req(void);
extern void Clr_SPI_Req(void);
extern void Clr_T0_Req(void);
extern void Clr_T1_Req(void);
extern void Clr_T2_Req(void);
extern void Clr_USB_Req(void);
extern void Disable_CIS_INT(void);
extern void Disable_MSP_INT(void);
extern void Disable_NF_INT(void);
extern void Disable_P00_INT(void);
extern void Disable_P01_INT(void);
extern void Disable_P02_INT(void);
extern void Disable_RTC(void);
extern void Disable_SPI_INT(void);
extern void Disable_T0_INT(void);
extern void Disable_T1_INT(void);
extern void Disable_T2_INT(void);
extern void Disgie(void);
extern void Enable_CIS_INT(void);
extern void Enable_MSP_INT(void);
extern void Enable_NF_INT(void);
extern void Enable_P00_INT(void);
extern void Enable_P01_INT(void);
extern void Enable_P02_INT(void);
extern void Enable_RTC(void);
extern void Enable_SPI_INT(void);
extern void Enable_T0_INT(void);
extern void Enable_T1_INT(void);
extern void Enable_T2_INT(void);
extern unsigned int Exchange_High_Low_Byte(unsigned int uiValue);
extern void Gie(void);
extern void P0_WakeUp_Setting(unsigned int uiP0);
extern void P1_WakeUp_Setting(unsigned int uiP1);
extern void RTC_HighClk_0P5_Sec(void);
extern void RTC_HighClk_1_Sec(void);
extern void RTC_LowClk_0P5_Sec(void);
extern void RTC_LowClk_1_Sec(void);
extern void WDT_0P25_Sec(void);
extern void WDT_0P5_Sec(void);
extern void WDT_1_Sec(void);
extern void WDT_2_Sec(void);
extern void Reset_WDT(void);

extern void Switch_Main_Clk_Freq(unsigned int uiCurrentFreq, unsigned int uiTargetFreq);
extern void Power_Down(unsigned int uiWakeupFreq);
extern void Watch_Mode_RTC_32K(void);
extern void Stop_32K_Clock(void);
extern void Start_32K_Clock(void);
extern void USB_Power_Down(void);

extern void Enable_IR(void);
extern void Disable_IR(void);
extern void PAD_12mA_Select(void);
extern void PAD_16mA_Select(void);
extern void BAT_Detect_Level(unsigned int uilevel);

extern void LowClk_Source_RC(void);
extern void LowClk_Source_XTAL(void);


//------------------------------------------------
// Don't Modify below Define
// Main Clock Frequency Define
//------------------------------------------------
#define HIGH_48M	0x01
#define HIGH_24M	0x02
#define HIGH_12M	0x03
#define HIGH_6M		0x04

#define SLOW_12M	0x10

#define SLOW_6M		0x20
#define SLOW_3M		0x21
#define SLOW_1P5M	0x22

#define SLOW_32K	0x30

#define LVD_2P5V	0x00

#define LVD_2P8V	0x01

#define LVD_2P9V	0x10

#endif