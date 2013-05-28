Chip SNC7001A

				//include ALGRAM_Define.h

				ALG_EXT	Dec_pdaout
				ALG_EXT	Dec_pdaout_R
				ALG_EXT	Effect_pdaout
				ALG_EXT DynamicRamBk
				ALG_EXT ReverbDynamicRamBk

				ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
				ORG ALG_AlgCommon_directDATA//ALG_AlgCommon_directDATA	 	segment	data  	at 	RAMSetStPos_AlgCommon_indirect common   //[2005.01.26]
				Dec_pdaout			DS 1
				Dec_pdaout_R		DS 1
				Effect_pdaout		DS 1
				DynamicRamBk		DS 1
				ReverbDynamicRamBk	DS 1