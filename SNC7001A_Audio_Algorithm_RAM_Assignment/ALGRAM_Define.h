//#ifndef  ALGRAM_Define_H_
//#define  ALGRAM_Define_H_

	ALG_EXT equ	public

	//========== Melody Channel Number Define =======

    Compress_Aud32		  EQU    1
	Compress_Aud32F		  EQU	1
	Compress_Aud32B		  EQU	1

	Compress_NMLD		  EQU    1
	NMLD_NCHANNEL		  EQU	12

	Compress_IMAADPCMDec  EQU	1
	Compress_IMAADPCMDecR EQU	1



	Resample_ChNum		 EQU	1
	ChangeSpeed			 EQU	1
	Resample		 	 EQU	1
	Reverb				 EQU	1
	Robot_TimeDomain	 EQU	1
	


	//==================Algorithm RAM Start Address ==================
	ALG_RAM_Addr        equ 0x140//0x140 //0x200 
	//================================================================

	//===== RAM SIZE of foreground Start ======//
	ALG_Audio32_directDATA_SIZE		equ	42
	ALG_Audio32F_indirectDATA_SIZE	equ	855
	ALG_Audio32B_indirectDATA_SIZE	equ	856


	ALG_SNX8KDEC_directDATA_SIZE    equ 125
	ALG_SNX8KDEC_indirectDATA_SIZE  equ 669


	ALG_IMAADPCMDec_directDATA_SIZE	    equ	12
	ALG_IMAADPCMDec_R_directDATA_SIZE	equ	12

	ALG_IMAADPCMDec_indirectDATA_SIZE	    equ	127
	ALG_IMAADPCMDec_R_indirectDATA_SIZE	    equ	127


	ALG_Melody_directDATA_SIZE		equ	56
	ALG_Melody_indirectDATA_SIZE	equ	16*NMLD_NCHANNEL

 
	ALG_Music96_directDATA_SIZE           equ	107
	//ALG_Music96_DoubleFetchDATA_SIZE      equ	1024//504+512
	ALG_Music96_DoubleFetchDATA_SIZE      equ	1024+128//504+512,128 Doblefetch Issue  
	ALG_Music96_indirectDATA_SIZE         equ	960
	  




	//===== RAM SIZE of foreground End   =========================================//
	

	ALG_AlgCommon_directDATA_SIZE	equ	5
	SysCommon_indirectDATA_SIZE	    equ	5+6


    ALG_AlgCommon_directDATA      equ	0
	SysCommon_indirectDATA        equ   ALG_AlgCommon_directDATA + ALG_AlgCommon_directDATA_SIZE
    ALG_Audio32_directDATA        equ   SysCommon_indirectDATA  + SysCommon_indirectDATA_SIZE

	ALG_Audio32F_indirectDATA     equ   ALG_Audio32_directDATA + ALG_Audio32_directDATA_SIZE
    
	ALG_SNX8KDEC_directDATA       equ   ALG_Audio32_directDATA + ALG_Audio32_directDATA_SIZE 
	ALG_SNX8KDEC_indirectDATA     equ   ALG_SNX8KDEC_directDATA + ALG_SNX8KDEC_directDATA_SIZE
 
    ALG_IMAADPCMDec_directDATA    equ   ALG_Audio32_directDATA + ALG_Audio32_directDATA_SIZE 
    ALG_IMAADPCMDec_indirectDATA  equ	ALG_IMAADPCMDec_directDATA + ALG_IMAADPCMDec_directDATA_SIZE

	ALG_Music96_directDATA        equ   ALG_Audio32_directDATA + ALG_Audio32_directDATA_SIZE
    ALG_Music96_DoubleFetchDATA   equ   ALG_Music96_directDATA + ALG_Music96_directDATA_SIZE
	ALG_Music96_indirectDATA      equ   ALG_Music96_DoubleFetchDATA + ALG_Music96_DoubleFetchDATA_SIZE
   

	ALG_Audio32B_indirectDATA     equ   ALG_Audio32F_indirectDATA +ALG_Audio32F_indirectDATA_SIZE 
    ALG_Melody_directDATA         equ   ALG_Audio32F_indirectDATA +ALG_Audio32F_indirectDATA_SIZE 
    ALG_Melody_indirectDATA       equ   ALG_Melody_directDATA + ALG_Melody_directDATA_SIZE

	ALG_IMAADPCMDec_R_directDATA    equ   ALG_Audio32F_indirectDATA +ALG_Audio32F_indirectDATA_SIZE  
    ALG_IMAADPCMDec_R_indirectDATA  equ	  ALG_IMAADPCMDec_R_directDATA + ALG_IMAADPCMDec_R_directDATA_SIZE

    





