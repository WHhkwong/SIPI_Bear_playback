chip	SNC7001A

MUSIC96_RAM_PUBLIC equ 1

MUSIC_CHANNEL_NUM  equ 1
//include Music96Define.h
//include Music96RamExt.h




	


	public _ReturnTemp;
	public _MP2ReturnTemp;

IFNDEF		__MUSIC96_RAM_h__	
__MUSIC96_RAM_h__	equ	1

IFDEF MUSIC96_RAM_PUBLIC
	MUSIC96_RAM_PUBLIC_FUNC		EQU public
	MUSIC96_RAM_PUBLIC_VAR		EQU public
	MUSIC96_RAM_PUBLIC_Label	EQU public
ELSE
	MUSIC96_RAM_PUBLIC_FUNC 	EQU extern code
	MUSIC96_RAM_PUBLIC_VAR		EQU extern data
	MUSIC96_RAM_PUBLIC_Label	EQU extern code
ENDIF
	//MUSIC96_RAMBK EQU 0x02
//===============extern foreground music ram=====================
	MUSIC96_RAM_PUBLIC_VAR	_Music96RamBk;
	MUSIC96_RAM_PUBLIC_VAR	_MP3_RamBk;
	MUSIC96_RAM_PUBLIC_VAR	_Music96SnxPasswd;

	MUSIC96_RAM_PUBLIC_VAR 	_Flag_Music96;
	MUSIC96_RAM_PUBLIC_VAR	_Flag_MP3;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Flag_Fill;
	MUSIC96_RAM_PUBLIC_VAR	_MP3Flag_Fill;

	MUSIC96_RAM_PUBLIC_VAR	_Flag_Music96_Init;
	MUSIC96_RAM_PUBLIC_VAR	_Music96InputPara;
	MUSIC96_RAM_PUBLIC_VAR	_ptrMusic96TabAlloc;

	MUSIC96_RAM_PUBLIC_VAR	_Music96NotZero      ;

	MUSIC96_RAM_PUBLIC_VAR	_Music96Temp1;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Temp2;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Temp3;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Temp4;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Temp5;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Temp6;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Temp7;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Temp8;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Dfrac;
	MUSIC96_RAM_PUBLIC_VAR	_Music96Cfrac;

	MUSIC96_RAM_PUBLIC_VAR	_MP3HeaderFlag;

	MUSIC96_RAM_PUBLIC_VAR	_Music96SubBandLimit;
    MUSIC96_RAM_PUBLIC_VAR  _Music96hdr_end_flag;
	MUSIC96_RAM_PUBLIC_VAR  _Music96hdr_end_word;


	MUSIC96_RAM_PUBLIC_VAR	_Music96SampleCh1;


	MUSIC96_RAM_PUBLIC_VAR	_Music96BitAlloc;
	MUSIC96_RAM_PUBLIC_VAR	_Music96ScaleIndex;
	MUSIC96_RAM_PUBLIC_VAR	_Music96HannWndRam;

	MUSIC96_RAM_PUBLIC_VAR  _Music96LastFrmFlag;

	MUSIC96_RAM_PUBLIC_VAR	_Music96OutBufCh1;
	MUSIC96_RAM_PUBLIC_VAR	_Music96OutBufCh2;
	MUSIC96_RAM_PUBLIC_VAR	_MP3GrNum;
	MUSIC96_RAM_PUBLIC_VAR	_MP3OutBufaddr11;
	MUSIC96_RAM_PUBLIC_VAR	_MP3OutBufaddr12
	MUSIC96_RAM_PUBLIC_VAR	_MP3hdr_stereo;
	MUSIC96_RAM_PUBLIC_VAR	_MP3AlgType;
	MUSIC96_RAM_PUBLIC_VAR	_MP3FadeInFlag;
	MUSIC96_RAM_PUBLIC_VAR	_MP3FadeInCurSubFrmCnt;
	MUSIC96_RAM_PUBLIC_VAR	_MP3LastFrmFlag;
	MUSIC96_RAM_PUBLIC_VAR	_MP3_V_Fast_dsp1;
	MUSIC96_RAM_PUBLIC_VAR	_MP3_Decoded_Bits;
	MUSIC96_RAM_PUBLIC_VAR	_MP3_BitS_Flag;
	MUSIC96_RAM_PUBLIC_VAR	_MP3SubFrmCnt;
	MUSIC96_RAM_PUBLIC_VAR	_MP3_JSFlag;
	MUSIC96_RAM_PUBLIC_VAR	_MP3pxgv5;
	MUSIC96_RAM_PUBLIC_VAR	_MP3_BitstreamEndFlag;
	//MUSIC96_RAM_PUBLIC_VAR	_MP3POutIdx_asm;
	//MUSIC96_RAM_PUBLIC_VAR	_MP3FOutIdx_asm;
	//MUSIC96_RAM_PUBLIC_VAR	_MP3PcurIdx;
	//MUSIC96_RAM_PUBLIC_VAR	_MP3FcurIdx;
	//MUSIC96_RAM_PUBLIC_VAR	_MixerDASamplesCnt;
	//MUSIC96_RAM_PUBLIC_VAR	_MP3FadeInWeight;
	MUSIC96_RAM_PUBLIC_VAR	_MP3hdr_bitrate_index;
	MUSIC96_RAM_PUBLIC_VAR	_MP3hdr_jsbound;
	MUSIC96_RAM_PUBLIC_VAR	_MP3ActionFlag;
	MUSIC96_RAM_PUBLIC_VAR	_MP3SampIndex;
	MUSIC96_RAM_PUBLIC_VAR	_MP3hdr_mode;
	MUSIC96_RAM_PUBLIC_VAR	_MP3hdr_version;
	MUSIC96_RAM_PUBLIC_VAR	_MP3hdr_sampling_frequency;
	MUSIC96_RAM_PUBLIC_VAR	_MP3hdr_mode_ext;
	MUSIC96_RAM_PUBLIC_VAR	_MP3pxgv6;
	MUSIC96_RAM_PUBLIC_VAR	_MP3FadeOutFlag;
	MUSIC96_RAM_PUBLIC_VAR	_ptrMP3SampBeg;
	MUSIC96_RAM_PUBLIC_VAR	_ptrMP3SampEnd;
	MUSIC96_RAM_PUBLIC_VAR	_MP3SynOffset1;
	MUSIC96_RAM_PUBLIC_VAR	_MP3SynOffset2;
	MUSIC96_RAM_PUBLIC_VAR	_ptrMP3V;
	MUSIC96_RAM_PUBLIC_VAR	_MP3CurOutBufaddr;
	MUSIC96_RAM_PUBLIC_VAR	_MP3BitstreamValid;
	MUSIC96_RAM_PUBLIC_VAR	_MP3MaskVal;
	MUSIC96_RAM_PUBLIC_VAR	_MP3Temppxgv5;
	MUSIC96_RAM_PUBLIC_VAR	_MP3Temppxgv6;
	MUSIC96_RAM_PUBLIC_VAR	_MP3Temp2;
	MUSIC96_RAM_PUBLIC_VAR	_MP3Temp1;
	//MUSIC96_RAM_PUBLIC_VAR	_MP3ReadWordsCnt;
	MUSIC96_RAM_PUBLIC_VAR	_MP3_LowSamp_Flag;
	MUSIC96_RAM_PUBLIC_VAR	_MP3Header;
	MUSIC96_RAM_PUBLIC_VAR	_MP3hdr_IDex;
	MUSIC96_RAM_PUBLIC_VAR	_MP3BuffOffset;
	MUSIC96_RAM_PUBLIC_VAR	_ptrMP3BufOffset;
	MUSIC96_RAM_PUBLIC_VAR	_ptrMP3Buf;
	MUSIC96_RAM_PUBLIC_VAR	_MP3HannWndRam;
	MUSIC96_RAM_PUBLIC_VAR	_MP3SigAdd;
	MUSIC96_RAM_PUBLIC_VAR	_MP3SigSub;
	MUSIC96_RAM_PUBLIC_VAR	_MP3NikTableRam;
	MUSIC96_RAM_PUBLIC_VAR	_ExceptionFlag;
	MUSIC96_RAM_PUBLIC_VAR	_MP3OutBufLen;
if(RUN_IN_DEBUG_MODE==1)
MUSIC96_RAM_PUBLIC_VAR	_DebugVal
MUSIC96_RAM_PUBLIC_VAR	_DebugInfo
MUSIC96_RAM_PUBLIC_VAR	_DebugBufIdx
MUSIC96_RAM_PUBLIC_VAR	_StepInfo;
MUSIC96_RAM_PUBLIC_VAR  _StepInfoIdx;

endif

ENDIF


	//ALG_DATA_AddrStart	segment	data  	at 	0x0200  common
	ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
	ORG ALG_Music96_directDATA
	//org ALG_Music96_directDATA1
	MP3_RAM_START ds 0;
	_MP3_RamBk ds 1;//一定要放在第一個位置,與mp2的rambk olverlay
	_MP3_ExceptionFlag		ds 1;
	
	//========初始化要設0的區段,要與mp2也要設0的參數overlay===============
	//main data queue related parameters
	_MP3OnlyOneByteFlag ds 1;//表示該frm的maindata最後一筆只有一個byte
	_MP3MainDataOnlyOneByteFlag ds 1;//表示目前的maindata只有一個byte
	_MP3HeadPos         ds 1;
	_MP3TailPos         ds 1;
	_MP3HeadPosByte	 ds 1;
    _MP3TailPosByte     ds 1;
	_MP3DiscardBytes    ds 1;
	_MP3MainDataVal     ds 1;
	_MP3LeftBits        ds 1;
	//pack main data related parameters
	_MP3BitPackPos      ds 1;
	_MP3PreBitPackPos   ds 1;//當拿到queue中最後一個位置的資料時,如果該位罝只有1byte,那麼要備份_MP3BitPackPos至_MP3PreBitPackPos
	_MP3BitPackBuff     ds 1;
	
	_MP3GrIndex        ds 1;
	_MP3ChIndex        ds 1;
	_MP3CurIndex       DS 1;
	_MP3CurOutIndex    ds 1;
	_MP3OutIdx         ds 1;
	_MP3Slots  ds 1;
	_MP3PreSlots ds 1;
	//=====================================================================
	//======這裡往下有些參數會在music96使用,所以不能overlay================
	_Music96hdr_end_word ds 3;
	_Music96hdr_end_flag ds 1;

	_MP3ActionFlag  ds 1;
	_ptrMP3V   ds 1;
	_ptrMP3Buf ds 1;
	_ptrMP3SampBeg ds 1;
	_ptrMP3SampEnd ds 1;
	_MP3TempBuffOffset ds 0;
	_ptrMP3BufOffset  ds 1;
	_ptrMP3TabOffset  ds 1;
	_MP3SampIndex   ds 1;
	_MP3GrNum          ds 1;

	
	_MP3CurOutBufaddr ds 1;
	
	_MP3OutBufaddr11  ds 1;
	_MP3OutBufaddr12  ds 1;
	
	_MP3OutBufLen     ds 1;
	
	_MP3SubFrmCnt      ds 1;
	_Music96Flag_Fill	ds  0;
	_MP3Flag_Fill           ds 1;
	_Flag_Music96	 ds 0;
	_Flag_MP3        ds 1;  
	_MP3MaskVal ds 1;
	
	_MP3IMDCTout_Idx ds 0;
	_MP3Temp1   ds 1;
	_MP3IMDCTBLK_addr ds 0;
	_MP3Temp2   ds 1;
	_MP3BlkType ds 0;
	_MP3Temp3   ds 1;
	_MP3Temp4   ds 1;
	_MP3ScaleLen0 ds 0;
	_MP3Temp5   ds 1;
	_MP3HuffmanDecBits ds 0;
	_MP3ScaleLen1 ds 0;
	_MP3Temp6   ds 1;
	_MP3Temp7   ds 1;
	_MP3SynOffset1 ds 0;
	_MP3Temp8   ds 1;
	_MP3SynOffset2 ds 0;
	_MP3Temp9   ds 1;
    _MP3Temp10  ds 1;
	_MP3Temp11  ds 1;
	_MP3Temp12  ds 1;

	
	_ReturnTemp ds 1;
	_MP2ReturnTemp ds 1;

	_MP3pxgv5  ds 1;
	_MP3pxgv6  ds 1;
	_MP3Temppxgv5  ds 1;
	_MP3Temppxgv6  ds 1;
	_MP3_BitS_Flag ds 1;
	_MP3_BitstreamEndFlag ds 1;
	_MP3_Decoded_Bits ds 1;
	_MP3_MainData_Decoded_Bits ds 1;
	_MP3_LowSamp_Flag ds 1;
	_Music96SnxPasswd	 ds 0;
    _MP3SnxPassWd        ds 1;
    _MP3VolL          ds 1;
	_MP3VolR          ds 1;
	//========header=========
	//header中間不要插入其它word
	_MP3HeaderFlag ds 1;
	_MP3Header ds 0;
    _MP3hdr_version ds 1;
	_MP3hdr_lay ds 1;
    _MP3hdr_error_protection ds 1;
	_MP3hdr_bitrate_index ds 1;
	_MP3hdr_sampling_frequency ds 1;
	_MP3hdr_padding	ds 1;
	_MP3hdr_extension	ds 1;
	_MP3hdr_mode	    ds 1;
	_MP3hdr_mode_ext	ds 1;
	_MP3hdr_copyright	ds 1;
	_MP3hdr_original	ds 1;
	_MP3hdr_emphasis	ds 1;
	//==============================
	_MP3hdr_IDex    ds 1;
	_MP3hdr_jsbound	ds 1;
	_MP3hdr_stereo     ds 1;
	_MP3hdr_sblimit    ds 1;
	_MP3_JSFlag     ds 1;
	_MP3AlgType			ds 1;
	_MP3BuffOffset ds 2;
	//=======OID ram=========
	_MP3DiffFrmCnt ds 2;
	_MP3FadeInSubFrmCnt ds 1;
	_MP3FadeInEndPos ds 1;
		
	_MP3FadeOutBegPos ds 1;
	_MP3FadeInTime ds 1;
	_MP3FadeOutTime ds 1;
	_MP3FadeOutFlag ds 1;
	_MixerCh1FadeInFlag ds 0;
	_MP3FadeInFlag  ds 1;
	_MP3FadeInStep ds 1;
	_MP3FadeOutStep ds 1;
	_MP3FadeOutSubFrmCnt ds 1;
	_MP3FadeInCurSubFrmCnt ds 1;
	_MP3FadeOutFinalCountdown ds 1;
	_Music96LastFrmFlag	ds 1;
	_MP3LastFrmFlag ds 1;
	_MP3BitstreamValid ds 1;
	_MP3NotSynCnt ds 1;
	//=======================
	//ALG_DATA_AddrStart	 	segment	data  	at 	0x0200 common
	//ORG ALG_Music96_DoubleFetchRAM//ALG_Audio32F_indirectDATA	 	segment	data  	at 	RAMSetStPos_Audio32F_indirect common
	
	ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
	ORG ALG_Music96_DoubleFetchDATA
		
	_Music96HannWndRam	   ds 0;
	_MP3HannWndRam         ds 504;//要放在0~2k-1
	_MP3NikTableRam        ds 512;//要放在0~2k-1
	//========================
	//MP2 ram
	org _MP3_RamBk
	_Music96RamBk ds 1;//要放在第一個,才能與mp3_rambk overlay
	_ExceptionFlag		ds 1;
	_Music96NotZero		ds 1;
	_Music96SubBandLimit ds 1;
	_ptrMusic96TabAlloc  ds 1;
	_Music96Dfrac  ds 1;
	_Music96Cfrac  ds 1;
	_Music96Temp1  ds 1;
	_Music96Temp2  ds 1;
	_Music96Temp3  ds 1;
	_Music96Temp4  ds 1;
	_Music96Temp5  ds 1;
	_Music96Temp6  ds 1;
	_Music96Temp7  ds 1;
	_Music96Temp8  ds 1;
	_Music96InputPara ds 1;
	_Flag_Music96_Init ds 1;
	//========================
//MP3_RAM_DATA2	segment	data  	at 	0x0800  common
	//ALG_DATA_AddrStart	 	segment	data  	at 	0x0200 common
	//org ALG_Music96_indirectDATA2


//=====================  Wen Modify  =================================   
    
	ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
	ORG ALG_Music96_indirectDATA

	_Music96BitAlloc ds	32*MUSIC_CHANNEL_NUM
	_Music96ScaleIndex	ds	96*MUSIC_CHANNEL_NUM;
	_Music96SampleCh1  ds 96*MUSIC_CHANNEL_NUM;
	_Music96OutBufCh1 ds 96;
	_Music96OutBufCh2 ds 96;

	_MP3_V_Fast_dsp1 	    ds MUSIC_CHANNEL_NUM*512;//要放在2k~4k-1
	_MP3SigAdd				ds 16;//要放在2k~4k-1
	_MP3SigSub				ds 16;//要放在2k~4k-1



	MP3_RAM_END ds 0;
//=============================================================================
   
//=====================  Jason Original =================================   
    
/*	ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
	ORG ALG_Music96_indirectDATA

	_MP3_V_Fast_dsp1 	    ds MUSIC_CHANNEL_NUM*512;//要放在2k~4k-1
	_MP3SigAdd				ds 16;//要放在2k~4k-1
	_MP3SigSub				ds 16;//要放在2k~4k-1

	_Music96BitAlloc ds	32*MUSIC_CHANNEL_NUM
	_Music96ScaleIndex	ds	96*MUSIC_CHANNEL_NUM;
	_Music96SampleCh1  ds 96*MUSIC_CHANNEL_NUM;
	_Music96OutBufCh1 ds 96;
	_Music96OutBufCh2 ds 96;

	MP3_RAM_END ds 0;*/
//=============================================================================	