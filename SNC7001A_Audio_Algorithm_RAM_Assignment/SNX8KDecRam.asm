Chip SNC7001A
    
	public _SNX8KDEC_ReturnTemp;
	public _SNX8KDEC_EndFlag;
	//extern data _SNX8KENC_ReturnTemp;

	//include Src\SNX8KIP\SNX8KMemDefine.h
	SNX8KDEC_RAM_PUBLIC equ 1
	//include ..\SNX8KIP\SNX8KDecRamExt.h
	//include ..\SNX8KIP\SNX8KDecDefine.h
	
	//include Src\SNX8KIP\SNX8KDecRamExt.h
	//include Src\SNX8KIP\SNX8KDecDefine.h
	
	//SNX8KDEC_RAM1_START segment data at 0x0326//SNX8KDEC_DIRECTRAM_BEG COMMON
	IFNDEF		__SNX8KDEC_RAM_h__	
__SNX8KDEC_RAM_h__	equ	1	

IFDEF SNX8KDEC_RAM_PUBLIC
	SNX8KDEC_RAM_PUBLIC_FUNC	EQU public
	SNX8KDEC_RAM_PUBLIC_VAR		EQU public
	SNX8KDEC_RAM_PUBLIC_Label	EQU public
ELSE
	SNX8KDEC_RAM_PUBLIC_FUNC 	EQU extern code
	SNX8KDEC_RAM_PUBLIC_VAR		EQU extern data
	SNX8KDEC_RAM_PUBLIC_Label	EQU extern code
ENDIF

	    				
		
//SNX8KDEC_RAM_PUBLIC_VAR	SNX8KDEC_TEMP;
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pxgv5          
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pxgv6          
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_parm_11        //snx8k decode 11 parameters to parm_11[1~11];
		                     //parm_11[0]=1 => vad off
SNX8KDEC_RAM_PUBLIC_VAR     _SNX8KDEC_CurOutBufaddr  
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_UserOutBufAddr;
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_UserOutBufLen;
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_Fill_Out_Idx;
//SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_EndFlag;
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_CommandRegister;
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_modeindex       
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pcode0          
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pcode1          
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pcode2          
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_oldt0           
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pt0             
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tfrac           
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_t0max           
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_t0min           
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tt0             
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tcormax         
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tcmax           
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_ten             
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_ten0            
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tener           
SNX8KDEC_RAM_PUBLIC_VAR     _SNX8KDEC_tener0          
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tgainout        
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tgainin      	  
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pnumfram        
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pnumsbfm        
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_poverflow       
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pisubfm         
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pexc            
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pres2           
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_psynth          
SNX8KDEC_RAM_PUBLIC_VAR     _SNX8KDEC_tidx           
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tidx1          
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tidx2          
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_texp           
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_mempre         
SNX8KDEC_RAM_PUBLIC_VAR     _SNX8KDEC_psharp          
		
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_lsp_10          
SNX8KDEC_RAM_PUBLIC_VAR     _SNX8KDEC_tp_10           
		
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_ap_11         
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tf_12        	
		
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tfw1_12         
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tfw2_12         
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_ta_11           
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_subfdoflag8K    
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tpos_4          
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_gainpitch       
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_gaincode        
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pastgain        
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_pastquaen_4     

SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_oldexc_234     
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_memsyn_10 
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_memsynpst_10
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_freqprev_40
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_res2buf_183
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_synthbuf_50
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tmp_10
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_tmp_50		
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_th_22		
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_lspnew_10	
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_lspold_10	
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_code_40

SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_res2ps_40
//SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_OUT_BUF;
SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_Rambk;
//SNX8KDEC_RAM_PUBLIC_VAR		_SNX8KDEC_OUT_BUF2;
ENDIF
	ALG_DATA_AddrStart  segment data at ALG_RAM_Addr common//SNX8KENC_DIRECTRAM_BEG
	org ALG_SNX8KDEC_directDATA;
	
    
		_SNX8KDEC_pxgv5           DS 1;
		_SNX8KDEC_pxgv6           DS 1;
		_SNX8KDEC_parm_11         DS 12//snx8k decode 11 parameters to parm_11[1~11];
		                     //parm_11[0]=1 => vad off
		_SNX8KDEC_ReturnTemp     ds 1;
		_SNX8KDEC_UserOutBufAddr ds 1;
		_SNX8KDEC_UserOutBufLen  ds 1;
		_SNX8KDEC_Fill_Out_Idx   ds 1;
        _SNX8KDEC_CurOutBufaddr  DS 1//永遠指到snx8k內部的buffer
		_SNX8KDEC_Rambk  ds 1;
		_SNX8KDEC_EndFlag ds 1;
		_SNX8KDEC_CommandRegister ds 1;
		_SNX8KDEC_modeindex       DS 1
		_SNX8KDEC_pcode0          DS 1
		_SNX8KDEC_pcode1          DS 1
		_SNX8KDEC_pcode2          DS 1
		_SNX8KDEC_oldt0           DS 1
		_SNX8KDEC_pt0             DS 1
		_SNX8KDEC_tfrac           DS 1
		_SNX8KDEC_t0max           DS 1
		_SNX8KDEC_t0min           DS 1
		_SNX8KDEC_tt0             DS 1
		_SNX8KDEC_tcormax         DS 2
		_SNX8KDEC_tcmax           DS 1
		_SNX8KDEC_ten             DS 1
		_SNX8KDEC_ten0            DS 1
		_SNX8KDEC_tener           DS 2
        _SNX8KDEC_tener0          DS 2
		_SNX8KDEC_tgainout        DS 1
		_SNX8KDEC_tgainin      	  DS 1
		_SNX8KDEC_pnumfram        DS 1
		_SNX8KDEC_pnumsbfm        DS 1
		_SNX8KDEC_poverflow       DS 1
		_SNX8KDEC_pisubfm         DS 1
		_SNX8KDEC_pexc            DS 1
		_SNX8KDEC_pres2           DS 1
		_SNX8KDEC_psynth          DS 1
        _SNX8KDEC_tidx            DS 1
		_SNX8KDEC_tidx1           DS 1
		_SNX8KDEC_tidx2           DS 1
		_SNX8KDEC_texp            DS 1
		_SNX8KDEC_mempre          DS 1
        _SNX8KDEC_psharp          DS 1
		
		_SNX8KDEC_lsp_10          DS 0
      	_SNX8KDEC_tp_10           DS 10
		
		_SNX8KDEC_ap_11           DS 0
		_SNX8KDEC_tf_12        	  DS 12
		
		_SNX8KDEC_tfw1_12         DS 12
		_SNX8KDEC_tfw2_12         DS 12
		_SNX8KDEC_ta_11           DS 11//要放在0~2k-1 for double fetch
		_SNX8KDEC_subfdoflag8K    DS 1
		_SNX8KDEC_tpos_4          DS 4
		_SNX8KDEC_gainpitch       DS 1
		_SNX8KDEC_gaincode        DS 1
		_SNX8KDEC_pastgain        DS 1
		_SNX8KDEC_pastquaen_4     DS 4
		
		SNX8KDEC_RAM1_END			DS	0
		//SNX8KDEC_RAM2_START segment data at 0x0C78//SNX8KDEC_INDIRECTRAM_BEG COMMON
		ALG_DATA_AddrStart  segment data at ALG_RAM_Addr common
		org ALG_SNX8KDEC_indirectDATA

		_SNX8KDEC_oldexc_234     ds 234
		_SNX8KDEC_memsyn_10      ds 10
		_SNX8KDEC_memsynpst_10   ds 10
		_SNX8KDEC_freqprev_40 	ds 40
		_SNX8KDEC_res2buf_183	ds 183
		_SNX8KDEC_synthbuf_50	ds 50
		_SNX8KDEC_tmp_10			ds 10
		_SNX8KDEC_tmp_50			ds 50//要放在0~2k-1 for double fetch
		_SNX8KDEC_th_22			ds 22
		_SNX8KDEC_lspnew_10		ds 10
		_SNX8KDEC_lspold_10		ds 10
		_SNX8KDEC_code_40        ds 0//要放在0~2k-1 for double fetch
		_SNX8KDEC_res2ps_40		ds 40
		//_code_40		ds 40
		SNX8KDEC_RAM2_END			DS	0

	