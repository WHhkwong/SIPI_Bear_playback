
void ChVocoder_Init(void);
void ChVocoder_SetRambk(short rambk);
//void ChVocoder_SetResampleFactor(short factor);
void ChVocoder_In_Setting(short *ptrmodulator,short *ptrcarrier);
void ChVocoder_Out_Setting(short *ptrout,short len);
void ChVocoder_Process(void);
short ChVocoderNotResampleProcess(void);

//void ChVocoder_Vocode(void);
void ChVocoder_Vocode2(void);
void ChVocoder_SetCarrierNormalize(short wt);//100~2000