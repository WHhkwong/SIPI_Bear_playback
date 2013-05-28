

void SNX8KDEC_SetRambk(short rmbk);
void SNX8KDEC_Init(void);
//void SNX8KDEC_SetInBuffer(short *inbuf,short inlen);
void SNX8KDEC_SetOutBuffer(short *outbuf);
short SNX8KDEC_IsDecEnd(void);
short SNX8KDEC_Process(short cmd);
