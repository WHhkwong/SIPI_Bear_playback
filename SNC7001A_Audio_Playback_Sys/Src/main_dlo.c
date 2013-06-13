#include <string.h>
#include <SFR.h>
#include "../../H/SNC7001A_Common_H/SNC7001A_Common_def.h"
#include "../../H/System/SNC7001A_System.h"
#include "../../H/Peripheral/SNC7001A_SD_DAC.h"
#include "../../SNC7001A_Audio_Playback_Sys/Include/SNC7001A_Audio_Playback_Usage.h"
#include "../../SNC7001A_Audio_Playback_Sys/Include/SNC7001A_Algorithm_Define.h"
#include "../../H/Peripheral/SNC7001A_SPI.h"

extern u16 g_uiSPI_RX_F;
extern u16 g_uiSPI_RX_0;
extern u16 g_uiSPI_RX_1;
extern u16 g_uiSPI_BUF_INDEX;
extern u16 g_uiFUNC_SELECT;
extern u16 g_uiFUNC_INI_SELECT;
extern u16 g_uiFUNC_PROC;
u16 g_uiFUNC_PLAY;

extern void WaveMarkTrig(void);

extern int* SongRam;
extern int SongRam1[0x400];
extern int SongRam2[0x400];
extern int SongRam3[0x400];
extern int SongRam4[0x400];
extern int SongRam5[0x400];
extern int SongRam6[0x400];

void SNAP01EN(void)
{
	_IObitSET(SFR_P1En,6) ; 
	_IObitSET(SFR_P1M,6) ;
	_IObitSET(SFR_P1,6) ;
}

void SNAP01DIS(void)
{
	_IObitSET(SFR_P1En,6); 
	_IObitSET(SFR_P1M, 6);
	_IObitCLR(SFR_P1,  6);//P1.6=0
}

void F_TestRamPlaySong(int* Song)
{
	SNAP01EN();
	SongRam = Song;
	PlayFore((__GENERIC int*)SongRam);	
}

void SPI_RX_FUNC_1(void)
{
	if( g_uiFUNC_INI_SELECT == 1 )
	{
		SD_DAC_Turn_On(SR_16K);
		SD_DAC_Volume_Control(0x10);

		g_uiFUNC_INI_SELECT = 0;
	}
	else if( g_uiFUNC_INI_SELECT == 2 )
	{
		SD_DAC_Turn_Off();
		PlayFore_Stop();
		_setSR(SFR_P3, _getSR(SFR_P3)&0xFFEF);
		memset(SongRam, 0, 1016);
		g_uiSPI_BUF_INDEX = 0;

		g_uiFUNC_PROC = 0;
		g_uiFUNC_PLAY = 0;

		g_uiFUNC_SELECT = 0;
		g_uiFUNC_INI_SELECT = 0;
	}

	if( ( g_uiFUNC_PLAY == 0 || g_uiFUNC_PLAY == 6) && g_uiFUNC_PROC >= 1 )
	{
		if(PlayForeEnd_Check()==1)
		{
			_setSR(SFR_P3, _getSR(SFR_P3)^0x0001);
			g_uiFUNC_PLAY = 1;
			F_TestRamPlaySong(SongRam1);
		}
	}
	else if( g_uiFUNC_PLAY == 1 && g_uiFUNC_PROC >= 2 )
	{
		if(PlayForeEnd_Check()==1)
		{
			_setSR(SFR_P3, _getSR(SFR_P3)^0x0001);
			g_uiFUNC_PLAY = 2;
			F_TestRamPlaySong(SongRam2);
		}
	}
	else if( g_uiFUNC_PLAY == 2 && g_uiFUNC_PROC >= 3 )
	{
		if(PlayForeEnd_Check()==1)
		{
			_setSR(SFR_P3, _getSR(SFR_P3)^0x0001);
			g_uiFUNC_PLAY = 3;
			F_TestRamPlaySong(SongRam3);
		}
	}
	else if( g_uiFUNC_PLAY == 3 && g_uiFUNC_PROC >= 4 )
	{
		if(PlayForeEnd_Check()==1)
		{
			_setSR(SFR_P3, _getSR(SFR_P3)^0x0001);
			g_uiFUNC_PLAY = 4;
			F_TestRamPlaySong(SongRam4);
		}
	}
	else if( g_uiFUNC_PLAY == 4 && g_uiFUNC_PROC >= 5 )
	{
		if(PlayForeEnd_Check()==1)
		{
			_setSR(SFR_P3, _getSR(SFR_P3)^0x0001);
			g_uiFUNC_PLAY = 5;
			F_TestRamPlaySong(SongRam5);
		}
	}
	else if( g_uiFUNC_PLAY == 5 && g_uiFUNC_PROC >= 6 )
	{
		if(PlayForeEnd_Check()==1)
		{
			_setSR(SFR_P3, _getSR(SFR_P3)^0x0001);
			g_uiFUNC_PLAY = 6;
			F_TestRamPlaySong(SongRam6);
		}
	}
}

void MainRoutine(void)
{
		g_uiFUNC_PROC = 0;

		g_uiFUNC_PLAY = 0;

		g_uiSPI_BUF_INDEX = 0;

#ifdef ENABLE_PIN_WAKEUP
		g_uiFUNC_INI_SELECT = 0;

		g_uiFUNC_SELECT = 0;
#else
		g_uiFUNC_INI_SELECT = 1;

		g_uiFUNC_SELECT = 1;
#endif
//	F_TestRamPlaySong();	//YQ 2013-5-10
   while(1)
   {
      Reset_WDT();

	  if(g_uiFUNC_SELECT == 0x0001)
	  {
         SPI_RX_FUNC_1();
      }
#ifdef ENABLE_PIN_WAKEUP
	  else if(g_uiFUNC_SELECT == 0x0000)
	  {
	  	SNAP01DIS();
//		Switch_Main_Clk_Freq(HIGH_48M, SLOW_12M);
//		Power_Down(HIGH_48M);
	  }
#endif

	  Audio_Decode_Process();

	 /* if(PlayForeEnd_Check()==1)
	  {
	    Reset_WDT();
	  }*/

      #ifdef WaveMark
	  WaveMarkTrig();
	  #endif

   }
}



#ifdef WaveMark
//================================WaveMark================================
void WaveMarkTrig(void)
{

  if (PlayWaveMarkFlagF ==1)  
  { 
      WaveMark_Routine_F();
	  
	  if( g_uiMarkCodeF != (short)0xFFFF )
	  { 
	    g_uiWaveMarkN_F++ ;
	   
	    switch(g_uiWaveMarkN_F)
        {
          
		   case 1/*WaveMark1*/ :    
           //_setSR(SFR_P0,g_uiMarkCodeF);  
		   g_uiMarkCodeF =(short)0xFFFF ;
	   
	       break;
      
	       case 2 /*WaveMark2*/ :        
           //_setSR(SFR_P0,g_uiMarkCodeF);  
		   g_uiMarkCodeF =(short)0xFFFF ;
	   
	       break;

           case 3 /*WaveMark3*/ :
      
           //_setSR(SFR_P0,g_uiMarkCodeF);  
		   g_uiMarkCodeF =(short)0xFFFF ;
	   
	       break;

           case 4 /*WaveMark4*/ :

          // _setSR(SFR_P0,g_uiMarkCodeF);  
		   g_uiMarkCodeF =(short)0xFFFF ;
	   
	       break;

		  
	       default:
		   g_uiMarkCodeF =(short)0xFFFF ;
	  
	                break;
	      
        } // Switch

   } //if

  }//if


  if (PlayWaveMarkFlagB ==1)  
  { 
      WaveMark_Routine_B();
	  
	  if( g_uiMarkCodeB != (short)0xFFFF )
	  { 
	    g_uiWaveMarkN_B++ ;
	   
	    switch(g_uiWaveMarkN_B)
        {
          
		   case 1/*WaveMark1*/ :    
           _setSR(SFR_P1,g_uiMarkCodeB);  
		   g_uiMarkCodeB =(short)0xFFFF ;
	   
	       break;
      
	       case 2 /*WaveMark2*/ :        
           _setSR(SFR_P1,g_uiMarkCodeB);  
		   g_uiMarkCodeB =(short)0xFFFF ;
	   
	       break;

           case 3 /*WaveMark3*/ :
      
           _setSR(SFR_P1,g_uiMarkCodeB);  
		   g_uiMarkCodeB =(short)0xFFFF ;
	   
	       break;

           case 4 /*WaveMark4*/ :

           _setSR(SFR_P1,g_uiMarkCodeB);  
		   g_uiMarkCodeB =(short)0xFFFF ;
	   
	       break;

		  
	       default:
		   g_uiMarkCodeF =(short)0xFFFF ;
	    
	                break;
	      
        } // Switch

   } //if

  }//if
}

//================================WaveMark================================
#endif 