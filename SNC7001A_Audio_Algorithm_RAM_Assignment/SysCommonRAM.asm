Chip SNC7001A


				//include ALGRAM_Define.h
				//extern data Background_ALGSel
				
				public inbufstatus
				public inbufindx
  				public curinbuf1
  				public curinbuf2
				public Dec_NFa
				public BitUnpackIdx
				public BitUnpackIdxT
				public BitUnpackVal
				public BitUnpackValT
  				

				
				//SYS_DATA	 	segment	data  	at 	0x0E00 common   //[2005.01.26]
				ALG_DATA_AddrStart	 	segment	data  	at 	ALG_RAM_Addr common
				ORG SysCommon_indirectDATA
				inbufstatus				ds	1;
				inbufindx				ds	1;
  				curinbuf1				ds  1;
  				curinbuf2				ds  1;
				Dec_NFa					ds  1;
				BitUnpackIdx            DS 2
	            BitUnpackIdxT           DS 1
           	    BitUnpackVal            DS 2
	            BitUnpackValT           DS 1

