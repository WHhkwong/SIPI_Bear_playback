#ifndef _H_Melody
#define _H_Melody

//==============Application function (user)=============//
short Melody_Process(short);
void  Melody_Out_Init(short *OutBufRAddr);

//----- Setting Sel,ChannelAttribute,Tempo,MLD_Vol,MLD_Inst.
void   SetCh(short num_cur_ch);
void   SetTempo(short);
void   SetVolume(ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,
				ushort,ushort,ushort,ushort,ushort);
void   SetInstrument(ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,ushort,
				ushort,ushort,ushort,ushort,ushort);
//==============Application function (user)=============//

#endif

