// Size of direct RAM : 56 words
// Size of indirect RAM : 16*NMLD_NCHANNEL words

Chip SNC7001A

//include ALGRAM_Define.h

if (Compress_NMLD == 1)

	  ALG_EXT Melody_Com_RAM_Satrt

	  ALG_EXT _CheckSum_High
	  ALG_EXT _CheckSum_Low
	  ALG_EXT TestFrameCnt

	  ALG_EXT @w4_wtempo
	  ALG_EXT _ins
	  ALG_EXT chanattr
	  ALG_EXT ptch
	  ALG_EXT nmldflag
	  ALG_EXT FrameSize
	  ALG_EXT MaxChNum
	  ALG_EXT CurChNum
	  ALG_EXT endcnt
	  ALG_EXT tmpcnt
	  ALG_EXT _code
	  ALG_EXT set_N_ch_make
	  ALG_EXT pch1
	  ALG_EXT NMLD_RAM_END
	  //====[NMLD PART 2] 16 CH MLD====
	  ALG_EXT PNMLD_INS  	//NMLD 初始設定用[2004.03.18]
	  ALG_EXT PNMLD_VOL
	  ALG_EXT out4 			  	//[20061213 allen]
	  ALG_EXT R_Ins_tab     	  //[2005.03.28]
	  ALG_EXT R_Ins_tabH    	   //[2005.03.28]
	  ALG_EXT R_Rhythm_tab    	   //[2005.03.28]
	  ALG_EXT R_Rhythm_tabH   	   //[2005.03.28]
	  ALG_EXT Melody_Com_RAM_End
	  //=============NMLD===============//

	  //==========[NMLD TEMP START]===============//
	  ALG_EXT Melody_Work_RAM_Start
	  ALG_EXT ChannelAttribute
	  ALG_EXT Melody_Work_RAM_End
      //==========[NMLD TEMP END]================//

	  //ALG_DATA_AddrStart	 	segment	data  	at 	0x0600 common
	  //EFFECT_RAM_START	 	segment	data  	at 	EFFECT_RAM common
	  //ORG ALG_Melody_directDATA//ALG_Melody_directDATA	 	segment	data  	at 	RAMSetStPos_Melody_direct common
	  
	  ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common 
	  ORG ALG_Melody_directDATA
		//ORG 0xCC+0x400//204+512 
	  
	  
	  
	  // =============[ direct RAM Start] ==========//
	  //==========[NMLD START]============//
	  //Melody direct RAM Start 0x600 ======================================
	  Melody_Com_RAM_Satrt  ds 	0;
	  _CheckSum_High		ds	1
	  _CheckSum_Low			ds	1
	  TestFrameCnt			ds	1

	  @w4_wtempo      		ds 	1;
	  _ins            		ds 	1;
	  chanattr        		ds 	1;
	  ptch            		ds 	1;
	  nmldflag        		ds 	1;
	  FrameSize       		ds 	1;
	  MaxChNum        		ds 	1;
	  CurChNum        		ds	1;
	  endcnt          		ds 	1;
	  tmpcnt          		ds 	1;
	  _code          		ds 	1;
	  set_N_ch_make   		ds	1;
	  pch1            		ds 	1;
	  NMLD_RAM_END    		ds	0;
	  //====[NMLD PART 2] 16 CH MLD====
	  PNMLD_INS  			ds 	16;	//NMLD 初始設定用[2004.03.18]
	  PNMLD_VOL  			ds 	16;
	  out4 			 		ds 	4; 	//[20061213 allen]
	  R_Ins_tab     	   	ds  1;//[2005.03.28]
	  R_Ins_tabH    	   	ds  1;//[2005.03.28]
	  R_Rhythm_tab    	   	ds 	1;//[2005.03.28]
	  R_Rhythm_tabH   	   	ds 	1;//[2005.03.28]
	  Melody_Com_RAM_End   	ds	0;
	  //Melody direct RAM End 0x638 ======================================
	  //Melody direct RAM Length 0x38(56) ======================================

	  //=============NMLD===============//
	  // =============[ direct RAM End] =============//

	  //ALG_DATA_AddrStart	 	segment	data  	at 	0x0211 common
	//  EFFECT_RAM_START	 	segment	data  	at 	EFFECT_RAM common
	//  ORG ALG_Melody_indirectDATA//ALG_Melody_indirectDATA	 	segment	data  	at 	RAMSetStPos_Melody_indirect common
	  ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common 
	  ORG ALG_Melody_indirectDATA
		//ORG 0xCC+0x400+0x38//204+512 
	
	  // =============[ indirect RAM Start] ==========//
	  //==========[NMLD TEMP START]===============//
	  //Melody indirect RAM Start 0x638 ======================================
	  Melody_Work_RAM_Start		DS 0
	  ChannelAttribute 			DS 16*NMLD_NCHANNEL;
	  Melody_Work_RAM_End    	DS 0;
	  //Melody indirect RAM End 0x6F8 ======================================
	  //Melody indirect RAM Length 0xC0 ======================================
      //==========[NMLD TEMP END]================//

endif


