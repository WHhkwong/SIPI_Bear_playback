Chip SNC7001A


// Size of direct RAM : 5 words


//include ALGRAM_Define.h

if (Compress_IMAADPCMDec == 1)


                ALG_EXT PredictedValue_Dec
                ALG_EXT StepIndex_Dec
				ALG_EXT	CVal_Dec
				ALG_EXT InitIdx_IMADec
				ALG_EXT	IMADec_BitRate
				ALG_EXT	IMADec_FrmSize
				ALG_EXT IMAADPCM_SubFrmIdx
				ALG_EXT IMAADPCM_SubFrmIdxEndP
				ALG_EXT IMADec_FillOutSize
				ALG_EXT IMADec_OutSize
				ALG_EXT IMAADPCM_SubFrmCnt
				ALG_EXT IMA_gFrmCntFlag
				ALG_EXT IMA_SubFrmQBuf


				ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
				ORG ALG_IMAADPCMDec_directDATA
				IMAADPCMDec_DirectRAM_Start   	DS 0
				PredictedValue_Dec				DS 1
                StepIndex_Dec					DS 1
				CVal_Dec						DS 1
				InitIdx_IMADec					DS 1
				IMADec_BitRate					DS 1
				IMADec_FrmSize					DS 1
				IMAADPCM_SubFrmIdx			DS 1
				IMAADPCM_SubFrmIdxEndP  DS 1
				IMADec_FillOutSize			DS 1
				IMADec_OutSize					DS 1
				IMAADPCM_SubFrmCnt		  DS 1
				IMA_gFrmCntFlag					DS 1
				IMAADPCMDec_DirectRAM_End		DS 0
				
				ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
				ORG ALG_IMAADPCMDec_indirectDATA
				IMAADPCMDec_IndirectRAM_Start	DS 0
				IMA_SubFrmQBuf					DS 127
				IMAADPCMDec_IndirectRAM_End 	DS 0


				
endif