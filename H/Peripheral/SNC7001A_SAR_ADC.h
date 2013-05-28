#ifndef _SNC7001A_SAR_ADC
#define _SNC7001A_SAR_ADC

extern u16 SAR_ADC_CHS(u16 ui_sel_ch);
extern u16 SAR_ADC_CKS(u16 uiDataLen, u16 ui_sel_cks);
extern u16 SAR_ADC_AUTO(u16 ui_mode);
extern u16 SAR_ADC_BAT_SW(u16 ui_mode);
extern u16 SAR_ADC_EN(u16 ui_mode);
extern u16 SAR_ADC_START(u16 ui_mode);
extern u16 SAR_ADC_DATA_Valid(void);
extern u16 SAR_ADC_DATA(void);

#endif
