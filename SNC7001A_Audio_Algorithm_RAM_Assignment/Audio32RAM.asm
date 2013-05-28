Chip SNC7001A

// Size of direct RAM : 42 words (for foreground and background)
// Size of indirect RAM : 855 words (for foreground)
// Size of indirect RAM : 855 words (for background)


//#define RAMSetStPos_Audio32 0xA0E7
//include ALGRAM_Define.h   //wensheng


if (Compress_Aud32 == 1)


ALG_EXT Aud_Com_RAM_Start
		//ALG_EXT bitrate_chL
  		//ALG_EXT bitrate_chR
		ALG_EXT Aud32Dec_subframecnt
		ALG_EXT Aud32Dec_subframecnt_R

//---- [ Dynamic RAM pointer ]----
        ALG_EXT Aud32Dec_pRAM1
		ALG_EXT Aud32Dec_pRam2_1//Aud32Dec_pRAM2_1//
//ORG     pRAM2
		ALG_EXT Aud32Dec_pRAM2//Aud32Dec_pRam2//
        ALG_EXT Aud32Dec_pram3
//ORG     pram3
		ALG_EXT Aud32Dec_pRAM3_1
//ORG     pram3
		ALG_EXT Aud32Dec_pRam3_2
   //=====================[AU32]=============================
        ALG_EXT Aud32Dec_dct_length_1
        ALG_EXT Aud32Dec_dct_length_log_1
		ALG_EXT Aud32Dec_dither_ptr_1
		ALG_EXT Aud32Dec_number_of_regions
 	    ALG_EXT Aud32Dec_num_categorization_control_bits
 	    ALG_EXT Aud32Dec_num_categorization_control_possibilities
    	ALG_EXT Aud32Dec_number_of_coefs
 	    ALG_EXT Aud32Dec_number_of_valid_coefs
        ALG_EXT Aud32Dec_frame_size
		ALG_EXT Aud32Dec_PadrCH0
	 	ALG_EXT Aud32Dec_pxgv5a
	 	ALG_EXT Aud32Dec_pxgv6a
	 	ALG_EXT Aud32Dec_Audio16_ini
    	ALG_EXT Aud32Dec_old_samples_320_Adr
 		ALG_EXT Aud32Dec_randseed_4_Adr
 	   	ALG_EXT Aud32Dec_PCH1_7
 		ALG_EXT Aud32Dec_PCH2_7
        ALG_EXT Aud32Dec_Audio16FLen
        ALG_EXT Aud32Dec_number_of_bits
 	 	ALG_EXT Aud32Dec_number_of_bits_left_1
 		ALG_EXT Aud32Dec_data_index_1
		ALG_EXT Aud32Dec_AUDIO32RAM_END1    //shift RAM CH1
        ALG_EXT Aud32Dec_AUDIO32RAM_END2     //shift RAM CH2
        ALG_EXT Aud32Dec_PlayS2
		ALG_EXT Aud32Dec_PlayS
	    ALG_EXT Aud32Dec_number_of_available_bits
 	 	ALG_EXT Aud32Dec_tmp
 	 	ALG_EXT Aud32Dec_randword_1
 	 	ALG_EXT Aud32Dec_mag_shift_1
//ORG tmp

 		ALG_EXT Aud32Dec_expected_number_of_code_bits
	    ALG_EXT Aud32Dec_raw_max
 		ALG_EXT Aud32Dec_raw_min
 		ALG_EXT Aud32Dec__max
 		ALG_EXT Aud32Dec__min
 		ALG_EXT Aud32Dec_raw_max_index
     	ALG_EXT Aud32Dec_raw_min_index
 		ALG_EXT Aud32Dec_max_rate_pointer
 		ALG_EXT Aud32Dec_min_rate_pointer
      	ALG_EXT Aud32Dec_ii
 		ALG_EXT Aud32Dec_temp2
//ORG _raw_max
 		ALG_EXT Aud32Dec_temp1
 		ALG_EXT Aud32Dec_answer
 		ALG_EXT Aud32Dec_delta
 		ALG_EXT Aud32Dec_bits
     	ALG_EXT Aud32Dec_test_offset
 		ALG_EXT Aud32Dec_categorization_control
 		ALG_EXT Aud32Dec_index
 		ALG_EXT Aud32Dec_max_index
		ALG_EXT Aud32Dec_offset

		ALG_EXT Aud32Dec_AU32DYRAM      //=_temp2

		ALG_EXT Aud_Com_RAM_End

endif

if(Compress_Aud32F == 1)

		ALG_EXT AudF_Work_RAM_Start
		ALG_EXT Aud32Dec_AudpRAMT1
		ALG_EXT Aud32Dec_AUDIO16RAM1
        ALG_EXT AudF_Work_RAM_End

endif

if(Compress_Aud32B == 1)

		ALG_EXT AudB_Work_RAM_Start
		ALG_EXT Aud32Dec_AudpRAMT2
		ALG_EXT Aud32Dec_AUDIO16RAM2
        ALG_EXT AudB_Work_RAM_End

endif


if (Compress_Aud32 == 1)

		ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
		ORG ALG_Audio32_directDATA//ALG_Audio32_directDATA	 	segment	data  	at 	RAMSetStPos_Audio32_direct common
		// =============[ direct RAM Start] ==========//
		Aud_Com_RAM_Start		DS 0;
		//bitrate_chL             ds 1;
  		//bitrate_chR             ds 1;
		Aud32Dec_subframecnt			DS 1;
		Aud32Dec_subframecnt_R			DS 1;


//---- [ Dynamic RAM pointer ]----
        Aud32Dec_pRAM1             DS   1
		Aud32Dec_pRAM2             DS   1
ORG     Aud32Dec_pRAM2
		Aud32Dec_pRam2_1             DS   1
        Aud32Dec_pram3             DS   1
ORG     Aud32Dec_pram3
		Aud32Dec_pRAM3_1             DS   1
ORG     Aud32Dec_pram3
		Aud32Dec_pRam3_2              DS   1
   //=====================[AU32]=============================
        Aud32Dec_dct_length_1       DS 1
        Aud32Dec_dct_length_log_1   DS 1
		Aud32Dec_dither_ptr_1       DS 1
		Aud32Dec_number_of_regions   DS 1
 	    Aud32Dec_num_categorization_control_bits  DS 1
 	    Aud32Dec_num_categorization_control_possibilities  DS 1
    	Aud32Dec_number_of_coefs  DS 1
 	    Aud32Dec_number_of_valid_coefs  DS 1
        Aud32Dec_frame_size  DS 1
		Aud32Dec_PadrCH0      DS 0
	 	Aud32Dec_pxgv5a       DS  1
	 	Aud32Dec_pxgv6a       DS  1
	 	Aud32Dec_Audio16_ini  DS  1
    	Aud32Dec_old_samples_320_Adr  DS 1
 		Aud32Dec_randseed_4_Adr         DS 1
 	   	Aud32Dec_PCH1_7       DS 1
 		Aud32Dec_PCH2_7       DS 1
        Aud32Dec_Audio16FLen DS 1
        Aud32Dec_number_of_bits DS 1
 	 	Aud32Dec_number_of_bits_left_1  DS 1
 		Aud32Dec_data_index_1     DS 1
		Aud32Dec_AUDIO32RAM_END1    DS 1 //shift RAM CH1
        Aud32Dec_AUDIO32RAM_END2    DS 1  //shift RAM CH2
        Aud32Dec_PlayS2        DS 1
		Aud32Dec_PlayS        DS 1
	    Aud32Dec_number_of_available_bits  DS 1
 	 	Aud32Dec_tmp           DS 9
 	 	Aud32Dec_randword_1         DS 1
 	 	Aud32Dec_mag_shift_1  DS 1
ORG Aud32Dec_tmp

 		Aud32Dec_expected_number_of_code_bits  DS 1
	    Aud32Dec_raw_max  DS 1
 		Aud32Dec_raw_min  DS 1
 		Aud32Dec__max  DS 1
 		Aud32Dec__min  DS 1
 		Aud32Dec_raw_max_index  DS 1
     	Aud32Dec_raw_min_index  DS 1
 		Aud32Dec_max_rate_pointer  DS 1
 		Aud32Dec_min_rate_pointer  DS 1
      	Aud32Dec_ii  DS 1
 		Aud32Dec_temp2  DS 1
ORG Aud32Dec_raw_max
 		Aud32Dec_temp1  DS 1
 		Aud32Dec_answer  DS 1
 		Aud32Dec_delta  DS 1
 		Aud32Dec_bits  DS 1
     	Aud32Dec_test_offset  DS 1
 		Aud32Dec_categorization_control  DS 1
 		Aud32Dec_index  DS 1
 		Aud32Dec_max_index  DS 1
		Aud32Dec_offset  DS 1

		Aud32Dec_AU32DYRAM  DS 0    //=_temp2
		Aud_Com_RAM_End		DS 0;
		// =============[ direct RAM End] =============//

endif

if(Compress_Aud32F == 1)

		// =============[ indirect RAM Start] ==========//
		//=========[AU32 Temp RAM END Left Channel]===========//
		ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
		ORG ALG_Audio32F_indirectDATA//ALG_Audio32F_indirectDATA	 	segment	data  	at 	RAMSetStPos_Audio32F_indirect common
		AudF_Work_RAM_Start 	   ds 0
		Aud32Dec_AudpRAMT1         DS  360
		Aud32Dec_AUDIO16RAM1       dS 171+4+320
        AudF_Work_RAM_End   	   ds 0
		//=========[AU32 Temp RAM END Left Channel]===========//

endif

if(Compress_Aud32B == 1)

		//=========[AU32 Temp RAM END Right Channel]===========//
		ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
		ORG ALG_Audio32B_indirectDATA//ALG_Audio32B_indirectDATA	 	segment	data  	at 	RAMSetStPos_Audio32B_indirect common
        AudB_Work_RAM_Start    	   DS 0
		Aud32Dec_AudpRAMT2         DS   360
		Aud32Dec_AUDIO16RAM2       DS 171+4+320
        AudB_Work_RAM_End     	   DS 1
		//=========[AU32 Temp RAM END Right Channel]===========//

endif
