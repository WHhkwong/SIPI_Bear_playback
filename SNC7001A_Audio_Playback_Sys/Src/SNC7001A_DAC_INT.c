
#define _INT_C

#include <SFR.h>
#include "../../H/SNC7001A_Common_H/SNC7001A_Common_def.h"
#include "../../H/System/SNC7001A_System.h"
#include "SNC7001A_Algorithm_Define.h"
#include "../../SNC7001A_Audio_Playback_Sys/Include/SNC7001A_Audio_Playback_Usage.h"
#include "hw_setup.h"

extern u16 g_uiMOUTH_STATE;

extern short	 gOutBuf[];
extern short     POutIdx_asm;

void __interrupt [0x34] DA_ISR(void)
{
	long gOutAmp;

	Clr_SD_DAC_Req();

//	MOUTH_PIECE_PIN_TOGGLE;
   
    #ifdef WaveMark
	//=======================WaveMark Usage====================
    if ( WaveMarkF_F==1 || WaveMarkF_B==1)
    {
	 	g_uiWaveMark_Time_Counter++ ;  
		if(samplerate==16000)
	    {
	       if (g_uiWaveMark_Time_Counter ==2) 
           {
   	          g_uiWaveMark_1ms_CounterF++ ;
              g_uiWaveMark_1ms_CounterB++ ;
		      g_uiWaveMark_Time_Counter=0;
           }
	    } 
	    else if (samplerate==8000)
    	{
	          g_uiWaveMark_1ms_CounterF = g_uiWaveMark_Time_Counter ;
		      g_uiWaveMark_1ms_CounterB = g_uiWaveMark_Time_Counter ;
     	}
	}  
	//=============================================================
	#endif
   
	gOutAmp = gOutBuf[POutIdx_asm] + gOutBuf[POutIdx_asm + 1] + gOutBuf[POutIdx_asm + 2] + gOutBuf[POutIdx_asm + 3] +
				gOutBuf[POutIdx_asm + 4] + gOutBuf[POutIdx_asm + 5] + gOutBuf[POutIdx_asm + 6] + gOutBuf[POutIdx_asm + 7];

	gOutAmp = gOutAmp / 8;

	if(gOutAmp >= 256 || gOutAmp <= -256)
	{
		if(g_uiMOUTH_STATE)
		{
			MOUTH_PIECE_PIN_HI;
		}
		else
		{
			MOUTH_PIECE_PIN_LO;
		}
	}
	else
	{
		g_uiMOUTH_STATE = 1;
		MOUTH_PIECE_PIN_LO;
	}

   __asm
   {

    extern data _gOutBufAddr
//	extern data _POutIdx_asm
	extern data _PcurIdx
	extern data _OutBufLength
   

	@FILLDA_PROC:
          	   //====<0> PUSH ====
               Push SSF
               PUSH Iy0;
  	           Push R0
               PUSH X1;
			   push r1;
			   push x0;
			   push Ix0;

			   Ix0 = (_gOutBufAddr)
			   X0 = RAM(Ix0)
			   Ix0 = (_POutIdx_asm)
			   R1 = RAM(Ix0)
			   X0=X0+R1;
			   Iy0=X0;
			   X1=0;
			   R0 = RAM(Iy0);
	           DAOL = R0
			   RAM(Iy0,1)=X1;

	           R0 = RAM(Iy0)
	           DAOL = R0
			   RAM(Iy0,1)=X1;

	           R0 = RAM(Iy0)
	           DAOL = R0
			   RAM(Iy0,1)=X1;

	           R0 = RAM(Iy0)
	           DAOL = R0
			   RAM(Iy0,1)=X1;

	           R0 = RAM(Iy0)
	           DAOL = R0
			   RAM(Iy0,1)=X1;

	           R0 = RAM(Iy0)
	           DAOL = R0
			   RAM(Iy0,1)=X1;

	           R0 = RAM(Iy0)
	           DAOL = R0
			   RAM(Iy0,1)=X1;

	           R0 = RAM(Iy0)
	           DAOL = R0
			   RAM(Iy0,1)=X1;

			   Ix0 = (_POutIdx_asm)
			   X1 = RAM(Ix0)
               R0 = 8;
               X1 = X1+R0;          	//cntint++;
			   RAM(Ix0) = X1		 	//POutIdx_asm = X1;


               //-- reset input buffer --
			   Ix0 = (_OutBufLength)
			   R0 = RAM(Ix0)
               X1 = X1-R0;
               JFLT FILLDA0_CD;

			   Ix0 = (_PcurIdx)
			   R0 = RAM(Ix0)
			   R0 = BTOG.0 R0;
			   RAM(Ix0) = R0

			   X1 = 0;
			   Ix0 = (_POutIdx_asm)
			   RAM(Ix0) = X1

	FILLDA0_CD: 
               POP Ix0;
               POP x0;
			   POP r1;
               POP X1;
	           Pop R0
               POP Iy0;
	           Pop SSF
 }
}