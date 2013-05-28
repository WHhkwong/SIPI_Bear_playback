#ifndef Audio_Playback_Process_H_
#define Audio_Playback_Process_H_


#include "SNC7001A_Algorithm_Define.h"

//=================================================================
//================ Play Process Variable Define ===================
//=================================================================
	#define DecOutLength 		32
	#define InBufLength         64
	#define Music96InBufLength  432 //80Kbps : 360 , 96Kbps :432
	#define Conti_Array_Length  128

//-----------------------------------------------------------------
//================ Play Process Function by Itself ================
//-----------------------------------------------------------------
 	void	CFill_DecInBuffer11_12(void);
	void    CFill_Dec_Music96InBuffer11_12(void) ;
	void	CFill_DecInBuffer21_22(void);
	short	SysCheckOutBuf(void);
	void    AudioPlay_Enable(void);
	void	FillOutBufProcess(short FillLength);
	void	USetBitstreamLabelF(__GENERIC int *Inptr);
	void	USetBitstreamLabelB(__GENERIC int *Inptr);
	void    Audio_Algorithm_Initial(void);
	void    Audio_Decode_Initial(void);
	void	Audio_Decode_Process(void);
	void 	MixFunc(short *OutBufAddr, short *DecTempBufAddr,short DecStatusF, short DecStatusB);
	short 	DecodeProF(short *DecOutBufAddr);
	short 	DecodeProB(short *DecOutBufAddr);
	short   Silence_Detection_Func(short gSilenceDectFlag_Local, short gSilence_Frame_StartAddr , short g_DecodeFrmCntAddr , short gSilence_Frame_EndAddr,short gAlgTypeAddr,short gsubframeindexAddr , short silence_ptr) ;
    void    HeaderUnpack_F(void);
	void    HeaderUnpack_B(void);
	void ReadWrite_Inbuf_Load(short *InBuf11, short *InBuf12, short length, unsigned short Status, unsigned short indx);
	void ReadWrite_Inbuf_Save(short Status, short indx);
	void GetInBufWord_L(void);
	void SetMBEHeaderArrayAddrF(short HeaderStAddrF);
	void SetMBEHeaderArrayAddrB(short HeaderStAddrF);
	void OrientationSetFunc(short OffsetWordAddr, short AlgType, short SampleRate, short BitRate, long OffsetTime, short SilenceDectFlag,short UpDownSel, short CurPosFrmAddr);



#endif



//=================================================================
//================ Play Process Variable Supply ===================
//=================================================================

	__GENERIC short *data_ptr1;
	__GENERIC short *data_ptr2;
	__GENERIC short *data_ptr1_StartAddr;
	__GENERIC short *data_ptr2_StartAddr;
	__GENERIC short *wavemark_ptrF,*wavemark_ptrB;
	__RAM short  CH1_AlgType,CH2_AlgType;
	__RAM short  CH1_Command,CH1_Status;
	__RAM short  CH2_Command,CH2_Status;
	__RAM short  CH1_Volume,CH2_Volume;
	__RAM short  Resample_Sel,Level_Sel;
	__RAM short  OutBufStartAddr,DecOutLengthF,DecOutLengthB,DecOutLengthDAC;
	// ============ for SysCheckOutBuf
	__RAM short  POutIdx_asm;
	__RAM short  FOutIdx_asm;
	__RAM short  PcurIdx;
	__RAM short  FcurIdx;
	__RAM short  OutBufLength;
	// ============ for SysCheckOutBuf

	// ============ for Decode Frame Count
	__RAM long	g_DecodeFrmCntF;
	__RAM long	g_DecodeFrmCntB;
	// ============ for Decode Frame Count

	// ============ for LevelX input buffer parameter
	__RAM unsigned short DecInBuf_Status;
	__RAM unsigned short DecInBuf_R_Status;
	__RAM unsigned short DecInBuf_Indx;
	__RAM unsigned short DecInBuf_R_Indx;
	// ============ for LevelX input buffer parameter

	__RAM short g_InBufLengthF ;
	__RAM short g_InBufLengthB ;

	__RAM short	 gOutBufAddr;

	// ============  Silence Detection Start ============ //
	__GENERIC short *silence_ptrF,*silence_ptrB;
	__RAM long gSilence_Frame_StartF ,  gSilence_Frame_EndF ;
	__RAM long gSilence_Frame_StartB ,  gSilence_Frame_EndB ;
	__RAM short  SilenceDectFlagF , SilenceDectFlagB;
	__RAM short	 subframeindexF;
	__RAM short	 subframeindexB;

// ============  Silence Detection End ============ //

	// ============  Wave Mark Start ============ //
	__RAM short g_uiMarkCodeF ;
	__RAM short g_uiMarkCodeB ;

	__RAM  long g_uiWaveMark_1ms_CounterF;
	__RAM  long g_uiWaveMark_1ms_CounterB;
	__RAM  short g_uiWaveMark_Time_Counter;
	__RAM  long g_uiWaveMark_TimeF;
	__RAM  long g_uiWaveMark_TimeB;
	__RAM  short  WaveMarkF_F , WaveMarkF_B;

	__RAM  unsigned short  PlayWaveMarkFlagF;

	__RAM  unsigned short  PlayWaveMarkFlagB;

	__RAM  unsigned short g_uiWaveMarkN_F;
	__RAM  unsigned short g_uiWaveMarkN_B;

	// ============  Wave Mark End ============ //
	//__RAM short  DecodeOutBuf[DecOutLength];
	__RAM short  DecodeOutBufR[DecOutLength];
	//__RAM short  gOutBuf[320];
	__RAM short  gOutBuf[320+32];


	__RAM short  gInputBuf11[InBufLength];
	__RAM short  gInputBuf12[InBufLength];


//=============== Orientation or AB Play ==================

	__RAM short  OrientationTrigFlag_F;
	__RAM short  gUpDown_Sel_F;
	__RAM long	 gOffsetTime_F;
	__RAM long	 gOffsetWord_F;

	__RAM short  OrientationTrigFlag_B;
	__RAM short  gUpDown_Sel_B;
	__RAM long	 gOffsetTime_B;
    __RAM long	 gOffsetWord_B;

	__RAM short  AB_PlayF_Flag;
	__RAM short  AB_PlayB_Flag;


	__RAM long AB_PlayF_EndFrmcnt ;
	__RAM long AB_PlayB_EndFrmcnt ;

	__RAM long AB_PlayF_EndTime;
	__RAM long AB_PlayB_EndTime;






//===========================================================


    #ifdef MUSIC96_PLAY
	__RAM short  gMusic96InputBuf11[Music96InBufLength];
	__RAM short  gMusic96InputBuf12[Music96InBufLength];
    #endif



	__RAM short  gInputBuf21[InBufLength];
	__RAM short  gInputBuf22[InBufLength];
	// ============  Header Start ============ //
	short  *MBEHeaderInfoF;	///////
	short  *MBEHeaderInfoB;	///////
	__RAM short  samplerate,bitrate;
	__RAM long   FrmLengthF,FrmLengthB;
	short MBEHeaderStAddrF[16];
	short MBEHeaderStAddrB[16];
	// ============  Header End   ============ //


	//------------- Check Channel End (Stop) --------
	__RAM short g_Play_End_F;    // 2012.3.23 __RAM short g_No_Start_Play_F;
	__RAM short g_Play_End_B;    // 2012.3.23 __RAM short g_No_Start_Play_B;
	//------------- Check Channel End (Stop) --------




	unsigned short PlayConti_Number ;
    unsigned short PlayConti_Length ;
    __RAM short PlayConti_Array[Conti_Array_Length] ;
	short PlayConti_Array_Ptr ;


	//===================================Wen add 20110928=============
    short PlayContiHead_Subframe ;
	short DecodeProcess_Subframe ;

	short DecodeProcess_Res_Sample_Number ;

	short Fill_ResData_Flag ;
	short Fill_ResData_Length ;
	//================================================================

	unsigned short g_uiKeyScan_8ms;
	unsigned short g_uiPreKeyValue;
	unsigned short g_uiKeyValue;



	union DWORD_TYPE  g_PlayDataAddr;
	union DWORD_TYPE  g_PlayDataAddr_R;


	unsigned short g_SPI_DMA_Read_Type ;




    unsigned short PlayForeEnd_Check_Flag ;
	unsigned short PlayBackEnd_Check_Flag ;

//==========================================
	unsigned short	OddEven;
	unsigned short Audio32_16KHz;
	unsigned short Snx8K_8KHz;
//===========================================
	//YQ 2013-5-10 Start
	int* SongRam;
	int SongRam1[0x600];
	int SongRam2[0x600];

	int g_SongDataAddr;
	//YQ 2013-5-10 End