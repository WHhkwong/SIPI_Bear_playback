#ifndef _SNC7001A_SD_ADC
#define _SNC7001A_SD_ADC

extern u16 SD_ADC_Turn_On(u16 ui_sample_rate, u16 ui_int_mode);
extern u16 SD_ADC_Turn_Off(void);
extern u16 SD_ADC_Gain_Ctrl(u16 ui_gain_value);
extern u16 SD_ADC_Volume_Ctrl(u16 ui_vol_value);
extern u16 SD_ADC_AGC_Parameter(u16 ui_HB_H_value, u16 ui_HB_L_value, u16 ui_LB_H_value, u16 ui_LB_L_value, u16 ui_AGC_gain_value, u16 ui_attack_time, u16 ui_decay_time);
extern u16 SD_ADC_AGC_On(void);
extern u16 SD_ADC_AGC_Off(void);
extern u16 SD_ADC_AD_DATA(void);
extern u16 SD_ADC_Read_REG(u16 ui_Reg_Addr);
extern u16 SD_ADC_Write_REG(u16 ui_Reg_Addr, u16 ui_value);

#endif