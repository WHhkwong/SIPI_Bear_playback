Chip SNC7001A//Chip SNC7210


// Size of direct RAM : 5 words


//include ALGRAM_Define.h

if (Compress_IMAADPCMDecR == 1)


                ALG_EXT PredictedValue_DecR
                ALG_EXT StepIndex_DecR
				ALG_EXT	CVal_DecR
				ALG_EXT InitIdx_IMADecR
				ALG_EXT	IMADec_BitRateR
				ALG_EXT	IMADec_FrmSizeR
				ALG_EXT IMAADPCM_SubFrmIdxR
				ALG_EXT IMAADPCM_SubFrmIdxEndPR
				ALG_EXT IMADec_FillOutSizeR
				ALG_EXT IMADec_OutSizeR
				ALG_EXT IMAADPCM_SubFrmCntR
				ALG_EXT IMA_gFrmCntFlagR
				ALG_EXT IMA_SubFrmQBufR


				ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
				ORG ALG_IMAADPCMDec_R_directDATA
				IMAADPCMDecR_DirectRAM_Start   	DS 0
				PredictedValue_DecR				DS 1
                StepIndex_DecR					DS 1
				CVal_DecR						DS 1
				InitIdx_IMADecR					DS 1
				IMADec_BitRateR					DS 1
				IMADec_FrmSizeR					DS 1
				IMAADPCM_SubFrmIdxR			DS 1
				IMAADPCM_SubFrmIdxEndPR DS 1
				IMADec_FillOutSizeR			DS 1
				IMADec_OutSizeR					DS 1
				IMAADPCM_SubFrmCntR		  DS 1
				IMA_gFrmCntFlagR				DS 1
				IMAADPCMDecR_DirectRAM_End		DS 0
				
				ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
				ORG ALG_IMAADPCMDec_R_indirectDATA
				IMAADPCMDecR_IndirectRAM_Start   	DS 0
				IMA_SubFrmQBufR										DS 127
				IMAADPCMDecR_IndirectRAM_End   		DS 0


				
endif