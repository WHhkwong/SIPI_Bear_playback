#ifndef _H_audio32
#define _H_audio32
//==============Application function (user)=============//
//LC
void Aud32_Parameter_Set_chL(short bitrate);
//void Aud32_In_Init_chL(ushort *, ushort *, ushort);
//unsigned short Aud32_In_Init_chL(short *InBuf11,short *InBuf12, short InBuflength);
void Aud32_Out_Init_chL(short *OutBufLAddr);
short Aud32_Process_chL(short);

//RC
void Aud32_Parameter_Set_chR(short bitrate);
//unsigned short Aud32_In_Init_chR(short *InBuf21, short *InBuf22, short InBuflength);
void Aud32_Out_Init_chR(short *OutBufLAddr);
short Aud32_Process_chR(short Cmd);
//==============Application function (user)=============//
#endif

