
void  Talk2Sing_Init(void);
void  Talk2Sing_SetRambk(short rambk);
void  Talk2Sing_SetWeight(short fwt,short bwt);
void Talk2Sing_SetRealTimeCase(short flag);
void  Talk2Sing_In_Setting(short *ptrmodulator,short *ptrcarrier,short *ptrbackmusic);
void  Talk2Sing_Out_Setting(short *ptrout,short len);
short Talk2Sing_Process(void);


void  Talk2Sing_Process2(void);
void Talk2Sing_Vocode2(void);
short Talk2Sing_DetectPitch(void);
void Talk2Sing_FFTSqrttoMag(void);
//void Talk2Sing_GetSinVal(void);



void  Talk2Sing_EstimageVoiceRangeProcess(void);
short Talk2Sing_GetVoiceRange(void);
short Talk2Sing_GetNotesSamples(short lv,short noteidx,short *outbuf);
