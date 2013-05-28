
//========================================================================================
//SNC7001A Audio Playback Sample Code
//Created by Wensheng  
//v1 : 2011.10.25
//v2 : 2012.05.15
//v3 : 2012.12.20
//v4 : 2013.01.08   //add the silence deteciton for SNX8K/MUSIC96/IMAADPCM

//Algorithm Support Type is Bellow
//<1> Audio32 Sample Rate = 16KHz ; BitRate : 16Kbps,20Kbps,24Kbps,28Kbps,32Kbps
//<2> MIDI(Melody) Sample Rate = 16KHz
//<3> Music96 Sample Rate = 16KHz ; BitRate : 40Kbps,48Kbps,56Kbps,64Kbps,80Kbps,96Kbps
//<4> SNX8K Sample Rate =8KHz ; BitRate : 8Kbps
//<5> IMAADPCM Sample Rate = 8KHz(BitRate:32Kbps),12KHz(BitRate:48Kbps),16KHz(BitRate:64Kbps)

//Advance play function
//<1> WaveMark
//<2> SilenceDetection
//<3> Orientation

//===========================================================================================

#define _KeyScan_
#include <SFR.H>
#include "../../H/SNC7001A_Common_H/SNC7001A_Common_def.h"
#include "../../H/System/SNC7001A_System.h"
#include "../../H/Peripheral/SNC7001A_Serial_Flash.h"
#include "../../H/Peripheral/SNC7001A_SD_DAC.h"

#include "../../H/Audio/Audio32_Dec_Lib.h"
#include "../../H/Audio/MLD_Dec_Lib.h"
#include "../../H/Audio/SNX8KDec_Lib.h"
#include "../../H/Audio/IMAADPCMDec.h"
#include "../../H/Audio/IMAADPCMDecR.h"
#include "../../H/Audio/Music96_Dec_Lib.h"


#include "SNC7001A_Audio_Playback_Process.h"
#include "SNC7001A_Algorithm_Define.h"

extern int g_SongDataAddr;
extern int SongRam1[0x600];

void Audio_Decode_Process(void)
{
short DecStatusF,DecStatusB;
short i;

	Audio_Decode_Initial();


	if(SysCheckOutBuf() == 1)  //Control Algorithm Decoder Timing Point
	{

		if(Level_Sel == 1)
		{

		  DecStatusF=0;
		  DecStatusB=0;
		  
		   DecStatusF = DecodeProF(gOutBuf+OutBufStartAddr);  //Foreground Decode Process

		   DecStatusB = DecodeProB(DecodeOutBufR); //Background Decode Process

		}

	   MixFunc(gOutBuf+OutBufStartAddr,DecodeOutBufR,DecStatusF,DecStatusB);

    }

	if(CH1_Command != ResetCmd && CH1_Command != StopCmd)  //Fill Foreground Decoder Inbuffer Data
	{
	    if(CH1_AlgType == MUSIC96)     //MUSIC96  Algorithm InbufferLength = 432
		{
		  	CFill_Dec_Music96InBuffer11_12();
		}
		else
		{
		  CFill_DecInBuffer11_12();	// Other Algorithm InbufferLength = 64

		}


    }

	if(CH2_Command != ResetCmd && CH2_Command != StopCmd) //Fill Foreground Decoder Inbuffer Data
		CFill_DecInBuffer21_22();

	// 2012.3.26 start, modify check order
	if (CH1_Command == StopCmd)
	{
		if (PlayForeEnd_Check_Flag)
		{
			if ((POutIdx_asm >= FOutIdx_asm) && (PcurIdx == FcurIdx))
			{
				PlayForeEnd_Check_Flag = 0;
   				g_Play_End_F =1;
			}
		}
	}

	if (CH2_Command == StopCmd)
	{
		if (PlayBackEnd_Check_Flag)
		{
			if ((POutIdx_asm >= FOutIdx_asm) && (PcurIdx == FcurIdx))
			{
	   			PlayBackEnd_Check_Flag =0;
				g_Play_End_B = 1;
			}
		}
	}
	// 2012.3.26 end
}


void Audio_Decode_Initial(void)
{

	if(CH1_Command == ResetCmd)
	{

		HeaderUnpack_F();  //Foreground Header Data Unpack

		#ifdef AUDIO32_PLAY
		//====================Audio32 Foreground Decode Initial===============================
	    if(CH1_AlgType == AUDIO32)
		{
			Aud32_Parameter_Set_chL(bitrate);
			CH1_Status = Aud32_Process_chL(CH1_Command);
			if(CH1_Status == 1)
				CH1_Command = NormalCmd;
			DecOutLengthF = 32;
			g_InBufLengthF =64 ;  // The Inbuffer Length is different for different Algorithm
			Level_Sel = 1;

			CFill_DecInBuffer11_12();
		}
		//=====================================================================================
		#endif

        #ifdef MUSIC96_PLAY
		//====================Music96 Foreground Decode Initial===============================
	    if(CH1_AlgType == MUSIC96)
		{
			Music96_Init();

			CH1_Command = NormalCmd;
			CH2_Command = StopCmd;  //The Music96 Ram is overlap with background voice play
			DecOutLengthF = 32;
			g_InBufLengthF =432; //The Music96 Inbuffer Length is 432
			Level_Sel = 1;
			CFill_Dec_Music96InBuffer11_12();

		}
		//====================================================================================

		#endif

		#ifdef IMAADPCM_PLAY
		if(CH1_AlgType == IMAADPCM)
		{
	    //====================IMAADPCM Foreground Decode Initial===============================


			  DecOutLengthF = 32;
			  g_InBufLengthF =64;
			  CFill_DecInBuffer11_12();
              ReadWrite_Inbuf_Load(gInputBuf11,gInputBuf12,g_InBufLengthF,DecInBuf_Status,DecInBuf_Indx);
			  CH1_Status = IMAADPCMDec_Process(CH1_Command);
			  Level_Sel=1 ;
	          ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_Status,(__RAM short)&DecInBuf_Indx);
			  if(CH1_Status == 1)
		      {
			     CH1_Command = NormalCmd;
              }

			  //=========================IMAADPCM Dec_Orientation=============================
			  /*if (OrientationTrigFlag_F==1)
			  {
			     data_ptr1_StartAddr +=2 ;
			  }*/
			  //
        }


		//====================================================================================
		#endif


		#ifdef SNX8K_PLAY
	    //====================SNX8K Foreground Decode Initial=======================================
		if(CH1_AlgType == SNX8K)
		{
	
		    CH2_Command=StopCmd;
		   	POutIdx_asm = 0;
        	FOutIdx_asm = 0;
	    	PcurIdx = 0;
	    	FcurIdx = 0;
			DecOutLengthF=DecOutLengthB;
	
			
			
			//SNX8KDEC_SetRambk(0x0002);
			SNX8KDEC_SetRambk(0x0001);
			if(SNX8KDEC_Process(ResetCmd)==1)
			CH1_Command = NormalCmd;

			CH2_Command = StopCmd;  //SNX8K is 8KHz sample rate , is not mix with background 16KHz

			Level_Sel = 1;

            DecOutLengthF = 40;

			g_InBufLengthF =64 ;

			CFill_DecInBuffer11_12();

         }

		//====================================================================================
		#endif


		DecOutLengthDAC = DecOutLengthF;  //Foreground DAC Length is different
	}

	if(CH2_Command == ResetCmd)
	{


		HeaderUnpack_B();  //Background Header Data Unpack

		if(CH1_AlgType==MUSIC96)
		{
		   CH1_Command=StopCmd;

		   POutIdx_asm = 0;
        	   FOutIdx_asm = 0;
	    	   PcurIdx = 0;
	    	   FcurIdx = 0;

			DecOutLengthF=DecOutLengthB;

		}
		
		if(CH1_AlgType==SNX8K)
		{
		    CH1_Command=StopCmd;
		   	POutIdx_asm = 0;
        	FOutIdx_asm = 0;
	    	PcurIdx = 0;
	    	FcurIdx = 0;

			DecOutLengthF=DecOutLengthB;
		}
		#ifdef AUDIO32_PLAY
        //====================Audio32 Background Decode Initial===============================
		if(CH2_AlgType == AUDIO32)
		{
			Aud32_Parameter_Set_chR(bitrate);
			CH2_Status = Aud32_Process_chR(CH2_Command);
			if(CH2_Status == 1)
			{
			   CH2_Command = NormalCmd;
			   if(Level_Sel == 0)
					Level_Sel = 1;
			}
			DecOutLengthB = 32;

			g_InBufLengthB =64 ;

			CFill_DecInBuffer21_22();
		}
		//=====================================================================================
		#endif


		#ifdef MELODY_PLAY
		//====================Melody Background Decode Initial========================================

		if(CH2_AlgType == MLD)
		{
		     DecOutLengthB = 32;
			 g_InBufLengthB =64 ;


			 CFill_DecInBuffer21_22();

		     ReadWrite_Inbuf_Load(gInputBuf21,gInputBuf22,g_InBufLengthB,DecInBuf_R_Status,DecInBuf_R_Indx);
			 CH2_Status = Melody_Process(CH2_Command);
			 ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_R_Status,(__RAM short)&DecInBuf_R_Indx);
	    	 if(CH2_Status == 1)
			 {
			    CH2_Command = NormalCmd;
			    if(Level_Sel == 0)
			    	   Level_Sel = 1;
			 }


		}
        //=====================================================================================
        #endif

		#ifdef IMAADPCM_PLAY
		//==================MAADPCM Background Decode Initial================================
		if(CH2_AlgType == IMAADPCM)
		{

              DecOutLengthB = 32;
			  g_InBufLengthB =64;
			  CFill_DecInBuffer21_22();
              ReadWrite_Inbuf_Load(gInputBuf21,gInputBuf22,g_InBufLengthB,DecInBuf_R_Status,DecInBuf_R_Indx);
			  CH2_Status = IMAADPCMDec_ProcessR(CH2_Command);
			  Level_Sel=1 ;
	          ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_R_Status,(__RAM short)&DecInBuf_R_Indx);
			  if(CH2_Status == 1)
		      {
			     CH2_Command = NormalCmd;
              }



        }
		#endif

		DecOutLengthDAC = DecOutLengthB;
	}
}



short SysCheckOutBuf(void)  //SysCheckOutBuf is the Ring Buffer Control, and resolution is one sample
{
 short Temp,Temp1;

   if(PcurIdx != FcurIdx)
   {
      Temp1 = OutBufLength - FOutIdx_asm;
	  Temp  = Temp1 + POutIdx_asm;

   }
   else
   {
      Temp = POutIdx_asm - FOutIdx_asm ;

   }
   if(Temp >= DecOutLengthDAC*2)  //  DecOutLengthDAC*1 or  DecOutLengthDAC*2
   {

	 OutBufStartAddr = FOutIdx_asm;

	 return 1;
   }

   return 0;
}




void FillOutBufProcess(short FillLength) //Fill DAC OutputBuffer Index Control
{

	FOutIdx_asm += FillLength;

	if(FOutIdx_asm >= OutBufLength)
	{
	   FOutIdx_asm = FOutIdx_asm - OutBufLength;
       FcurIdx ^= 0x0001;

	}
}


short DecodeProF(short *DecOutBufAddr) //Foreground Decode Process
{
short i;
short temp1 ,temp2 ,temp3 ;

	if(CH1_Command != ResetCmd && CH1_Command != StopCmd && CH1_Command != PauseCmd)
	{
		CH1_Status = 0;
		if(g_DecodeFrmCntF < FrmLengthF)
		{
			#ifdef AUDIO32_PLAY
			//====================Audio32 Foreground Decode Process===============================
			if(CH1_AlgType == AUDIO32)
			{

                 #ifdef SilenceDetection 

                  if(Silence_Detection_Func(SilenceDectFlagF, (__RAM long)&gSilence_Frame_StartF , (__RAM long)&g_DecodeFrmCntF , (__RAM long)&gSilence_Frame_EndF,CH1_AlgType,(__RAM short)&subframeindexF , (__GENERIC short)&silence_ptrF))
				  {
				        for(i = 0 ; i < DecOutLengthF ; i++)
						DecOutBufAddr[i] = 0;

						CH1_Status =1;
				  }

                  #else 

				   if(0);
                   
				   #endif 

		          else
				  {
				       Aud32_Out_Init_chL(DecOutBufAddr);
				       ReadWrite_Inbuf_Load(gInputBuf11,gInputBuf12,InBufLength,DecInBuf_Status,DecInBuf_Indx);
				       CH1_Status = Aud32_Process_chL(CH1_Command);	//Decode Process for Channel 1
				       ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_Status,(__RAM short)&DecInBuf_Indx);

                      //========================================================================

                       #ifdef PlayContinue
					   //====================PlayContinue====================================
					   temp1 = ((__RAM short)&DecOutBufAddr[0]-gOutBufAddr)+DecOutLengthF ;
                       if(temp1> OutBufLength)
					   {
					       temp2 = OutBufLength - ((__RAM short)&DecOutBufAddr[0]-gOutBufAddr) ;
					       temp3 = DecOutLengthF - temp2 ;
					       for(i = 0 ; i < temp3 ; i++)
					       {
					         gOutBuf[i]=DecOutBufAddr[temp2+i];
					       }
					   }

                       DecodeProcess_Subframe ++ ;
					   if(DecodeProcess_Subframe==10)
					   {
					      DecodeProcess_Subframe = 0;
					   }
					   //===================================================================================
					   #endif


			      }

                  //==========================================================================

				  #ifdef PlayContinue
				  //====================PlayContinue====================================
				  if((PlayContiHead_Subframe)!=0xFFFF)
		      	  {
			          if(g_DecodeFrmCntF == FrmLengthF-1)
			          {
			     	      if(DecodeProcess_Subframe==PlayContiHead_Subframe)
				          {
						//=================DecodeProcess_Res_Sample_Number //  Play The Resiude sample :1~31 point
					          if(DecodeProcess_Res_Sample_Number!=0)
					          {
					             Aud32_Out_Init_chL(DecOutBufAddr+DecOutLengthF);  //DecOutLengthF=32
				                 ReadWrite_Inbuf_Load(gInputBuf11,gInputBuf12,InBufLength,DecInBuf_Status,DecInBuf_Indx);
				                 CH1_Status = Aud32_Process_chL(CH1_Command);	//Decode Process for Channel 1
				                 ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_Status,(__RAM short)&DecInBuf_Indx);
					           }

					           Fill_ResData_Flag =1 ;
					           Fill_ResData_Length =  DecodeProcess_Res_Sample_Number ;
					           //DecOutLengthF = DecOutLengthF + DecodeProcess_Res_Sample_Number ;
				               CH1_Command = StopCmd;
				               CH1_AlgType = 0;
					           g_DecodeFrmCntF = 0;

					          //===========================PlayConti==================
                               if(PlayConti_Number!=0)
				               {
					               CH1_Command = ResetCmd;
					               __asm
					               {
                                      Ix0=(_PlayConti_Array_Ptr)
					                  R0 = RAM(Ix0)
					                  Ix0= R0
					                  R1 = RAM(Ix0,1)
					                  R0 = RAM(Ix0)
					                  Ix0=(_data_ptr1)
					                  RAM(Ix0,1)=R0
					                  RAM(Ix0) =R1
					               }
					               PlayConti_Array_Ptr=PlayConti_Array_Ptr+2;
					               PlayConti_Number = PlayConti_Number-1 ;
                                   DecInBuf_Status = 0x0007;
					               DecInBuf_Indx = 0;
				                   Audio_Decode_Initial() ;
			                  }

				          }
			         }
		         }
				 //=========================================================================
				 #endif


            }
            //===============================================================================
			#endif

			#ifdef MUSIC96_PLAY
			//====================Music96 Foreground Decode Process===============================
            if(CH1_AlgType == MUSIC96)
			{

 				  #ifdef SilenceDetection    //2013.01.08 wen add

                  if(Silence_Detection_Func(SilenceDectFlagF, (__RAM long)&gSilence_Frame_StartF , (__RAM long)&g_DecodeFrmCntF , (__RAM long)&gSilence_Frame_EndF,CH1_AlgType,(__RAM short)&subframeindexF , (__GENERIC short)&silence_ptrF))
				  {
				        for(i = 0 ; i < DecOutLengthF ; i++)
						DecOutBufAddr[i] = 0;

						CH1_Status =1;
				  }

                  #else 

				   if(0);
                   
				   #endif 


		          else
				  {


				 	 Music96_OutCH1_Init(DecOutBufAddr,32);
					 ReadWrite_Inbuf_Load(gMusic96InputBuf11,gMusic96InputBuf12,g_InBufLengthF,DecInBuf_Status,DecInBuf_Indx);
				 	 CH1_Status = Music96_Process(CH1_Command);	//Decode Process for Channel 1
				  	 if(CH1_Status==32)
				 	 {
						CH1_Status=1;
                 	 }
				     ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_Status,(__RAM short)&DecInBuf_Indx);
                   } 
 
			}
			//===============================================================================
			#endif



            #ifdef SNX8K_PLAY
			//====================SNX8K Foreground Decode Process===============================
            if(CH1_AlgType == SNX8K)
			{

  				  #ifdef SilenceDetection    //2013.01.08 wen add

                  if(Silence_Detection_Func(SilenceDectFlagF, (__RAM long)&gSilence_Frame_StartF , (__RAM long)&g_DecodeFrmCntF , (__RAM long)&gSilence_Frame_EndF,CH1_AlgType,(__RAM short)&subframeindexF , (__GENERIC short)&silence_ptrF))
				  {
				        for(i = 0 ; i < DecOutLengthF ; i++)
						DecOutBufAddr[i] = 0;

						CH1_Status =1;
				  }

                  #else 

				   if(0);
                   
				   #endif 


		          else
				  {

			     		SNX8KDEC_SetOutBuffer(DecOutBufAddr);
				 		ReadWrite_Inbuf_Load((short *)gInputBuf11,(short *)gInputBuf12,g_InBufLengthF ,DecInBuf_Status,DecInBuf_Indx);
				 		CH1_Status = SNX8KDEC_Process(CH1_Command);
						ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_Status,(__RAM short)&DecInBuf_Indx);
				 		if(SNX8KDEC_IsDecEnd() == 1)
				 		g_DecodeFrmCntF = FrmLengthF ;
                  }

			}
			//===============================================================================
			#endif


            #ifdef IMAADPCM_PLAY
			if(CH1_AlgType == IMAADPCM)
			{
			//===================IMADPCM Foreground Decode Process=========================


  				  #ifdef SilenceDetection    //2013.01.08 wen add

                  if(Silence_Detection_Func(SilenceDectFlagF, (__RAM long)&gSilence_Frame_StartF , (__RAM long)&g_DecodeFrmCntF , (__RAM long)&gSilence_Frame_EndF,CH1_AlgType,(__RAM short)&subframeindexF , (__GENERIC short)&silence_ptrF))
				  {
				        for(i = 0 ; i < DecOutLengthF ; i++)
						DecOutBufAddr[i] = 0;

						CH1_Status =1;
				  }

                  #else 

				   if(0);
                   
				   #endif 


		          else
				  {

				 	IMAADPCMDec_SetBitRate(4,128);
		         	IMAADPCMDec_Out_Init_chL(DecOutBufAddr,32);
				 	ReadWrite_Inbuf_Load((short *)gInputBuf11,(short *)gInputBuf12,g_InBufLengthF,DecInBuf_Status,DecInBuf_Indx);
	             	CH1_Status = IMAADPCMDec_Process(CH1_Command);
	             	ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_Status,(__RAM short)&DecInBuf_Indx);
                  }
            //===========================================================================

			}
			#endif


			if(g_DecodeFrmCntF == FrmLengthF && CH1_Status == 1)
		    {
					CH1_Command = StopCmd;
					CH1_AlgType = 0;
	        		g_DecodeFrmCntF = 0;

			}
		}
		else
			for(i = 0 ; i < DecOutLengthF ; i++)
					DecOutBufAddr[i] = 0;

		return CH1_Status;
	}

//	if(CH1_Command == StopCmd || CH1_Command== PauseCmd)
	if(CH1_Command == StopCmd && CH1_Command== PauseCmd)
	{
	     for(i = 0 ; i < DecOutLengthF ; i++)
		 {
		    DecOutBufAddr[i] = 0;
         }

		 return 1;

	}

	return 0;
}



short DecodeProB(short *DecOutBufAddr)  //Background Decode Process
{
short i;
	if(CH2_Command != ResetCmd && CH2_Command != StopCmd&& CH2_Command != PauseCmd)
	{
		CH2_Status = 0;


        #ifdef MELODY_PLAY
		//====================Melody Background Decode Process===============================
		if(CH2_AlgType == MLD)
		{

		    Melody_Out_Init(DecOutBufAddr);
			ReadWrite_Inbuf_Load(gInputBuf21,gInputBuf22,g_InBufLengthB ,DecInBuf_R_Status,DecInBuf_R_Indx);
			CH2_Status = Melody_Process(CH2_Command);	//Decode Process for Channel 1
			ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_R_Status,(__RAM short)&DecInBuf_R_Indx);

			if(CH2_Status == StopCmd) // Melody IP has stop code
			{
				CH2_Command = StopCmd;
				CH2_AlgType = 0;
				g_DecodeFrmCntB = 0;
			}

		}
		//===================================================================================
		#endif

        #ifdef AUDIO32_PLAY
		//====================Audio32 Background Decode Process===============================
		if(CH2_AlgType == AUDIO32)
		{
			if(g_DecodeFrmCntB < FrmLengthB)
			{

               #ifdef SilenceDetection 

				if(Silence_Detection_Func(SilenceDectFlagB, (__RAM long)&gSilence_Frame_StartB , (__RAM long)&g_DecodeFrmCntB , (__RAM long)&gSilence_Frame_EndB,CH2_AlgType,(__RAM short)&subframeindexB , (__GENERIC short)&silence_ptrB))
			    {
				        for(i = 0 ; i < DecOutLengthB ; i++)
						DecOutBufAddr[i] = 0;

				        CH2_Status =1 ;
				}

               #else 
                
                if(0) ;

                #endif
				
				 
				else
				{
					    Aud32_Out_Init_chR(DecOutBufAddr);
					    ReadWrite_Inbuf_Load(gInputBuf21,gInputBuf22,InBufLength,DecInBuf_R_Status,DecInBuf_R_Indx);
					    CH2_Status = Aud32_Process_chR(CH2_Command);	//Decode Process for Channel 2
					    ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_R_Status,(__RAM short)&DecInBuf_R_Indx);
				}


				if(g_DecodeFrmCntB == FrmLengthB && CH2_Status == 1)
		    	{
				       CH2_Command = StopCmd;
				       CH2_AlgType = 0;
				       g_DecodeFrmCntB = 0;
			    }
		   }
		   else
		   {
				for(i = 0 ; i < DecOutLengthB ; i++)
						DecOutBufAddr[i] = 0;
           }
	   }
	   	//====================================================================================
	   #endif

       #ifdef IMAADPCM_PLAY
	   //====================IMAADPCM Background Decode Process===============================
	   if(CH2_AlgType == IMAADPCM)
		{
			if(g_DecodeFrmCntB < FrmLengthB)
			{


                #ifdef SilenceDetection 

				if(Silence_Detection_Func(SilenceDectFlagB, (__RAM long)&gSilence_Frame_StartB , (__RAM long)&g_DecodeFrmCntB , (__RAM long)&gSilence_Frame_EndB,CH2_AlgType,(__RAM short)&subframeindexB , (__GENERIC short)&silence_ptrB))
			    {
				        for(i = 0 ; i < DecOutLengthB ; i++)
						DecOutBufAddr[i] = 0;

				        CH2_Status =1 ;
				}

               #else 

				if(0);

				#endif 


				else
				{

					   IMAADPCMDecR_SetBitRate(4,128);
		               IMAADPCMDec_Out_Init_chR(DecOutBufAddr,32);
				       ReadWrite_Inbuf_Load((short *)gInputBuf21,(short *)gInputBuf22,g_InBufLengthB,DecInBuf_R_Status,DecInBuf_R_Indx);
	                   CH2_Status = IMAADPCMDec_ProcessR(CH2_Command);
	                   ReadWrite_Inbuf_Save((__RAM short)&DecInBuf_R_Status,(__RAM short)&DecInBuf_R_Indx);
				}


				if(g_DecodeFrmCntB == FrmLengthB && CH2_Status == 1)
		    	{
				       CH2_Command = StopCmd;
				       CH2_AlgType = 0;
				       g_DecodeFrmCntB = 0;
			    }
		   }
		   else
		   {
				for(i = 0 ; i < DecOutLengthB ; i++)
						DecOutBufAddr[i] = 0;
           }
	   }
	   #endif

		return CH2_Status;
	}


	if(CH2_Command == StopCmd && CH2_Command== PauseCmd)
	{
	     for(i = 0 ; i < DecOutLengthB ; i++)
		 {
		    DecOutBufAddr[i] = 0;
         }

		 return 1;

	}

	return 0;
}



void MixFunc(short *OutBufAddr, short *DecTempBufAddr,short DecStatusF, short DecStatusB)
{
short i;

	if(DecStatusF == 1 || DecStatusB == 1)
	{
		if(DecStatusF == 1 && DecStatusB == 0)
		{
			__asm
			{
				Ix0 = (_CH1_Volume)
				Y1 = RAM(Ix0)
				Ix0 = (_DecOutLengthF)
				R0 = RAM(Ix0)

			/*	Ix0 = (_DecodeProcess_Res_Sample_Number)
				R1 = RAM(Ix0)
				R0 = R0 +R1*/

			    Ix0 = (_Fill_ResData_Flag)
				R1  = RAM(Ix0)
				Y0  = 1
				R1  = R1-Y0

                JNZ @@loop2
				Ix0 = (_Fill_ResData_Length)
				R1 = RAM(Ix0)
				R0 = R0 +R1

			@@loop2 :
                //=============================
				Ix0 = (_OutBufLength)
				R1  = RAM(Ix0)
				X1  = R1
                //============================

				X0=FP;
				Y0=4;
				X0=X0-Y0;
				Ix0=X0;
				X0 = RAM(Ix0,-1)
				Ix1 = X0
				X0 = RAM(Ix1)

		@@Fill_loop:



				MR = X0*Y1(FS)
				RAM(Ix1,1) = MR1

                //=====================================
				Ix0=(_gOutBufAddr)
				Y0 =RAM(Ix0)
				R1 =Ix1
				R1 =R1-Y0
				Y0 =X1
				R1 =R1-Y0

				JNZ @@NoArrayOverflow

				Ix1 = (_gOutBufAddr)
				R1  = RAM(Ix1)
				Ix1 = R1


         @@NoArrayOverflow :

				X0 = RAM(Ix1)


				R0 = R0 - 1
				JNZ @@Fill_loop
			}

			if(Fill_ResData_Flag==1)
			{
			  FillOutBufProcess(DecOutLengthF+Fill_ResData_Length);
              Fill_ResData_Flag =0 ;
            }
			else
			{

			  FillOutBufProcess(DecOutLengthF);
			}
		}

		if(DecStatusF == 0 && DecStatusB == 1)
		{
			__asm
			{
				Ix0 = (_CH2_Volume)
				Y1 = RAM(Ix0)
				Ix0 = (_DecOutLengthB)
				R0 = RAM(Ix0)

				X0=FP;
				Y0=4;
				X0=X0-Y0;
				Ix0=X0;
				X0 = RAM(Ix0,-1)
				Ix1 = X0
				X0 = RAM(Ix0)
				Ix0 = X0
				X0 = RAM(Ix0,1)
				@@:

				MR = X0*Y1(FS),X0 = RAM(Ix0,1)
				RAM(Ix1,1) = MR1

				R0 = R0 - 1
				JNZ @b
			}

			FillOutBufProcess(DecOutLengthB);
		}

		if(DecStatusF == 1 && DecStatusB == 1)
		{
     		__asm
			{
				PUSH MMR
				R0 = MMR
				R0 = BSET.15 R0
				MMR = R0
				Ix0 = (_CH1_Volume)
				Y0 = RAM(Ix0)
				Ix0 = (_CH2_Volume)
				Y1 = RAM(Ix0)

				X0=FP;
				R0=4;
				X0=X0-R0;
				Ix0=X0;
				X0 = RAM(Ix0,-1)
				Ix1 = X0
				X0 = RAM(Ix0)
				Ix0 = X0
				R0 = DecOutLength
				X0 = RAM(Ix1)
				@@:

				MR = X0*Y0(FS),X0 = RAM(Ix0,1)
				MR = MR + X0*Y1(FS)
				RAM(Ix1,1) = MR1
				X0 = RAM(Ix1)

				R0 = R0 - 1
				JNZ @b

				POP MMR
			}

			FillOutBufProcess(DecOutLength);
		}
	}
}



//void SystemInitial(void)
void AudioPlay_Enable(void)
{

//=======================DAC OutputBuf Control Usage===============

	OutBufLength = 320;
	POutIdx_asm = 0;
	FOutIdx_asm = 0;
	PcurIdx = 0;
	FcurIdx = 0;
	gOutBufAddr = (__RAM short)&gOutBuf[0];
	DecOutLengthF   = 0;
	DecOutLengthB   = 0;
//==================================================================
	g_DecodeFrmCntF = 0; // Frame Count of Decode Foreground
	g_DecodeFrmCntB = 0; // Frame Count of Decode Background
	Level_Sel		= 0;

//========  Wave Mark Usage ========================================
    g_uiWaveMark_1ms_CounterF =0 ;
	g_uiWaveMark_1ms_CounterB =0 ;
    g_uiWaveMark_Time_Counter =0 ;
	g_uiWaveMark_TimeF =0 ;
	g_uiWaveMark_TimeB =0 ;
	g_uiMarkCodeF =(short)0xFFFF ;
	g_uiMarkCodeB =(short)0xFFFF ;

	WaveMarkF_F =0 ;
	WaveMarkF_B =0 ;

//=======   Play End Stop Usage====================================

	g_Play_End_F =1 ;		// 2013.5.21 hk@woohing // 2012.3.23   g_No_Start_Play_F =0 ;
	g_Play_End_B =0 ;		// 2012.3.23   g_No_Start_Play_B =0 ;

//===========Foreground/Background Status and Volume Control=========

	CH1_Command		= StopCmd;
	CH2_Command		= StopCmd;
	CH1_Volume		= 0x7FFF;
	CH2_Volume		= 0x7FFF;
//===================================================================


//===========Header unpack usage ====================================
	SetMBEHeaderArrayAddrF((short)&MBEHeaderStAddrF);
	SetMBEHeaderArrayAddrB((short)&MBEHeaderStAddrB);

//===================================================================




//===================Play Contiune Usage ============================

   PlayConti_Number=0;
   PlayConti_Length=0 ;
   PlayConti_Array_Ptr= (__RAM short)&PlayConti_Array[0] ;
   PlayContiHead_Subframe =0 ;
   DecodeProcess_Subframe =0 ;
   DecodeProcess_Res_Sample_Number =0 ;
   Fill_ResData_Flag = 0;
   Fill_ResData_Length =0 ;
//===================================================================

   g_SPI_DMA_Read_Type = 1 ;  //SPI Flash Control SPI Read Type

//==================== Orientation or AB Play Usage==================
   OrientationTrigFlag_F = 0;
   gOffsetWord_F         = 0;

   AB_PlayF_Flag =0;
   AB_PlayB_Flag =0;

   AB_PlayF_EndFrmcnt =0 ;
   AB_PlayB_EndFrmcnt =0 ;

   AB_PlayF_EndTime =0;
   AB_PlayB_EndTime =0;





//===================================================================

   PlayForeEnd_Check_Flag =0;
   PlayBackEnd_Check_Flag =0;


}

void PlayFore(__GENERIC int *Inptr)
{
	USetBitstreamLabelF(Inptr);
	CH1_Command = ResetCmd;
	CH1_AlgType = 0x0000;

	DecInBuf_Status = 0x0007;
	DecInBuf_Indx = 0;
	g_DecodeFrmCntF = 0;

	PlayForeEnd_Check_Flag =1;
	g_Play_End_F = 0;			   // 2012.3.26 Add

	//=============DAC Initial ==================
    if (PlayBackEnd_Check_Flag == 0)            // 2012.3.27 Add
    {
	    POutIdx_asm = 0;
        FOutIdx_asm = 0;
	    PcurIdx = 0;
	    FcurIdx = 0;
    }
	//===========================================

}




void PlayBack(__GENERIC int *Inptr)
{
	USetBitstreamLabelB(Inptr);
	CH2_Command = ResetCmd;
	CH2_AlgType = 0x0000; // Default

	DecInBuf_R_Status = 0x0007;
	DecInBuf_R_Indx = 0;
	g_DecodeFrmCntB = 0;

	PlayBackEnd_Check_Flag =1;
	g_Play_End_B = 0;				// 2012.3.26 Add
	//=============DAC Initial ==================

    if (PlayForeEnd_Check_Flag == 0)
    {
	    POutIdx_asm = 0;
        FOutIdx_asm = 0;
	    PcurIdx = 0;
	    FcurIdx = 0;
    }
}


//================== PlayForeEnd_Ckeck ===============================


short PlayForeEnd_Check(void)
{
	// 2012.3.21 delete mark start
/*
   if (PlayForeEnd_Check_Flag==0)
   {
      return 0 ;

   }
   else
   {
      if( (PcurIdx == FcurIdx) && (POutIdx_asm >= FOutIdx_asm) && (CH1_Command ==StopCmd) )
	  {

		   PlayForeEnd_Check_Flag =0;
		   return 1 ;
	  }
	  else
	  {
	       return 0 ;
	  }

   }
*/
	// 2012.3.21 delete mark end

	// 2012.3.23 add start
	if (g_Play_End_F)
	{
//		g_Play_End_F = 0;
		return 1;
	}
	else
	{
		return 0;
	}
	// 2012.3.23 add end
}


//================== PlayBackEnd_Ckeck ===============================

short PlayBackEnd_Check(void)
{
	// 2012.3.21 delete mark start
/*
   if (PlayBackEnd_Check_Flag==0)
   {
      return 0 ;

   }
   else
   {
      if( (PcurIdx == FcurIdx) && (POutIdx_asm >= FOutIdx_asm) && (CH2_Command ==StopCmd) )
	  {
           PlayBackEnd_Check_Flag=0;

		   return 1 ;
	  }
	  else
	  {
	       return 0 ;
	  }

   }
*/
	// 2012.3.21 delete mark end

	// 2012.3.23 add start
	if (g_Play_End_B)
	{
		g_Play_End_B = 0;
		return 1;
	}
	else
	{
		return 0;
	}
	// 2012.3.23 add end
}



//=============Stop , Pause , PauseResume ======================
void PlayFore_Stop(void)
{
     CH1_Command =StopCmd ;
    PlayForeEnd_Check_Flag = 0;		// 2012.3.23 add
	 g_Play_End_F = 1;					// 2012.3.26 add
	 g_DecodeFrmCntF =0;
}

void PlayBack_Stop(void)
{
     CH2_Command =StopCmd ;
    PlayBackEnd_Check_Flag = 0;		// 2012.3.23 add
	 g_Play_End_B = 0;					// 2012.3.26 add
	 g_DecodeFrmCntB=0;
}

void PlayFore_Pause(void)
{
  if (CH1_Command == NormalCmd)		// 2012.3.23 add
        CH1_Command =PauseCmd ;
}

void PlayBack_Pause(void)
{
   if (CH2_Command == NormalCmd)		// 2012.3.23 add
        CH2_Command =PauseCmd ;
}


void PlayFore_PauseResume(void)
{
  if (CH1_Command == PauseCmd)		// 2012.3.23 add
        CH1_Command =NormalCmd ;
}

void PlayBack_PauseResume(void)
{
    if (CH2_Command == PauseCmd)		// 2012.3.23 add
        CH2_Command =NormalCmd ;
}


//===============================================================

//==========Foreground/Background Volume Control ================
void PlayFore_VOL_SET (short foreground_volume)
{
   CH1_Volume =foreground_volume ;
}

void PlayBack_VOL_SET (short background_volume)
{
   CH2_Volume =background_volume ;
}

//==================================================================






#ifdef Orientation

//=================== Orientation Usage ===============================

void PlayOrientationF(short UpDown_SelT, long OffsetTimeT)
{
    __asm
	{

		X0=FP;
		R0=4;
		X0=X0-R0;
		Ix0=X0;
		R0 = RAM(Ix0,-1)

		Ix1 =(_gUpDown_Sel_F)
		RAM(Ix1) = R0

		R0 = RAM(Ix0,-1)
		R1 = RAM(Ix0)


		Ix0 =(_gOffsetTime_F)
		RAM(Ix0,1)=R1
		RAM(Ix0)=R0

		R0=1
		Ix0 =(_OrientationTrigFlag_F)
		RAM(Ix0)=R0

    }

}

void PlayOrientationB(short UpDown_SelT, long OffsetTimeT)
{
	 __asm
	{

		X0=FP;
		R0=4;
		X0=X0-R0;
		Ix0=X0;
		R0 = RAM(Ix0,-1)

		Ix1 =(_gUpDown_Sel_B)
		RAM(Ix1) = R0

		R0 = RAM(Ix0,-1)
		R1 = RAM(Ix0)


		Ix0 =(_gOffsetTime_B)
		RAM(Ix0,1)=R1
		RAM(Ix0)=R0

		R0=1
		Ix0 =(_OrientationTrigFlag_B)
		RAM(Ix0)=R0

    }


}


void AB_PlayF(long StartTime, long EndTime)
{
    AB_PlayF_Flag=1;
	OrientationTrigFlag_F =1 ;
	gUpDown_Sel_F=1;
	gOffsetTime_F = StartTime ;
	AB_PlayF_EndTime = EndTime ;

}

void AB_PlayB(long StartTime, long EndTime)
{
    AB_PlayB_Flag=1;
	OrientationTrigFlag_B =1;
	gUpDown_Sel_B=1;
	gOffsetTime_B = StartTime ;
	AB_PlayB_EndTime = EndTime ;

}





//==============================================================
#endif





#ifdef PlayContinue

//=======================Play Continue Usage=============================

void PlayFore_Conti(__GENERIC int *Inptr)
{

__asm
{
	X0=FP;
	R0=4;
	X0=X0-R0;
	Ix1=X0;
    Ix0=(_PlayConti_Array_Ptr) ;
	R0 = RAM(Ix0)
	Ix0= R0

	X0=RAM(Ix1,-1);
    RAM(Ix0,1)=X0; //low
	X0=RAM(Ix1);
	RAM(Ix0)=X0;//high

}

PlayConti_Number++ ;
PlayConti_Length=PlayConti_Length+2 ;
PlayConti_Array_Ptr = PlayConti_Array_Ptr+ 2 ;

}


void PlayFore_Conti_Start(void)
{

   PlayConti_Number=0;
   PlayConti_Length=0 ;
   PlayConti_Array_Ptr= (__RAM short)&PlayConti_Array[0] ;

}

void PlayFore_Conti_End(void)
{

    PlayConti_Array_Ptr = PlayConti_Array_Ptr - PlayConti_Length ;
}

//=====================================================================
#endif



void CFill_DecInBuffer11_12(void)
{
short i,j;


    #ifdef Orientation
	//=============================Orientation Usage ===============================
	if(OrientationTrigFlag_F == 1)
	{

  	   OrientationSetFunc((__RAM short)&gOffsetWord_F,CH1_AlgType, samplerate, bitrate, gOffsetTime_F,0, gUpDown_Sel_F, (__RAM short)&g_DecodeFrmCntF);
	   OrientationTrigFlag_F = 0;
	   data_ptr1 = data_ptr1_StartAddr + gOffsetWord_F;

       //=======================g_PlayDataAddr.DWord = data_ptr1 asm code ============
	    __asm
		{
		  PUSH IX0
		  PUSH R0
		  PUSH R1

		  Ix0 = (_data_ptr1)
		  R0  = RAM(Ix0,1)
          R1  = RAM(Ix0,1)
		  Ix0 = (_g_PlayDataAddr)

		  RAM(Ix0,1) =R0
		  RAM(Ix0) =R1

		  POP R1
		  POP R0
		  POP IX0

		}
       //===========================================================================

	   DecInBuf_Status = 0x0007;
	   DecInBuf_Indx = 0;

    }
	//================================================================================
	#endif

	if((DecInBuf_Status & 0x0001)==0x0001)    			//in_buffer1 empty(bit2)
	{

		//SF_Read_DMA_Mode(g_SPI_DMA_Read_Type, (g_PlayDataAddr.HLWord[1]-0x40), g_PlayDataAddr.HLWord[0], g_InBufLengthF, (unsigned int*)gInputBuf11);
	    //g_PlayDataAddr.DWord += g_InBufLengthF ;
	    //YQ 2013-5-10 Start
		for(j=0;j<g_InBufLengthF;j++)
		{
			gInputBuf11[j] = SongRam[j+g_SongDataAddr];			
		}
		g_SongDataAddr = g_SongDataAddr + g_InBufLengthF;
		//YQ 2013-5-10 End
		
		DecInBuf_Status = DecInBuf_Status & 0x0ffe;

	}

	if((DecInBuf_Status & 0x0004)==0x0004)    			//in_buffer2 empty(bit3)
	{

	  	//SF_Read_DMA_Mode(g_SPI_DMA_Read_Type,(g_PlayDataAddr.HLWord[1]-0x40), g_PlayDataAddr.HLWord[0], g_InBufLengthF, (unsigned int*)gInputBuf12);
	    //g_PlayDataAddr.DWord += g_InBufLengthF ;
	    //YQ 2013-5-10 Start
		for(j=0;j<g_InBufLengthF;j++)
		{
			gInputBuf12[j] = SongRam[j+g_SongDataAddr];			
		}
		g_SongDataAddr = g_SongDataAddr + g_InBufLengthF;
		//YQ 2013-5-10 End
		
		DecInBuf_Status = DecInBuf_Status & 0x0ffb;

	}


}


void CFill_Dec_Music96InBuffer11_12(void)
{
short i;

     #ifdef Orientation
	//=============================Orientation Usage ===============================
	if(OrientationTrigFlag_F == 1)
	{

  	   OrientationSetFunc((__RAM short)&gOffsetWord_F,CH1_AlgType, samplerate, bitrate, gOffsetTime_F,0, gUpDown_Sel_F, (__RAM short)&g_DecodeFrmCntF);
	   OrientationTrigFlag_F = 0;
	   data_ptr1 = data_ptr1_StartAddr + gOffsetWord_F;

       //=======================g_PlayDataAddr.DWord = data_ptr1 asm code ============
	    __asm
		{
		  PUSH IX0
		  PUSH R0
		  PUSH R1

		  Ix0 = (_data_ptr1)
		  R0  = RAM(Ix0,1)
          R1  = RAM(Ix0,1)
		  Ix0 = (_g_PlayDataAddr)

		  RAM(Ix0,1) =R0
		  RAM(Ix0) =R1

		  POP R1
		  POP R0
		  POP IX0

		}
       //===========================================================================

	   DecInBuf_Status = 0x0007;
	   DecInBuf_Indx = 0;

    }
	//================================================================================
	#endif


	#ifdef MUSIC96_PLAY

	if((DecInBuf_Status & 0x0001)==0x0001)    			//in_buffer1 empty(bit2)
	{

		SF_Read_DMA_Mode(g_SPI_DMA_Read_Type,(g_PlayDataAddr.HLWord[1]-0x40), g_PlayDataAddr.HLWord[0], g_InBufLengthF, (unsigned int*)gMusic96InputBuf11);
	    g_PlayDataAddr.DWord += g_InBufLengthF ;

		DecInBuf_Status = DecInBuf_Status & 0x0ffe;
	}

	if((DecInBuf_Status & 0x0004)==0x0004)    			//in_buffer2 empty(bit3)
	{

	    SF_Read_DMA_Mode(g_SPI_DMA_Read_Type,(g_PlayDataAddr.HLWord[1]-0x40), g_PlayDataAddr.HLWord[0], g_InBufLengthF, (unsigned int*)gMusic96InputBuf12);
	    g_PlayDataAddr.DWord += g_InBufLengthF ;

		DecInBuf_Status = DecInBuf_Status & 0x0ffb;
	}

	#endif
}



void CFill_DecInBuffer21_22(void)
{
short i;
	if((DecInBuf_R_Status & 0x0001)==0x0001)    			//in_buffer1 empty(bit2)
	{

		SF_Read_DMA_Mode(g_SPI_DMA_Read_Type,(g_PlayDataAddr_R.HLWord[1]-0x40), g_PlayDataAddr_R.HLWord[0], g_InBufLengthB, (unsigned int*)gInputBuf21);
	    g_PlayDataAddr_R.DWord += g_InBufLengthB ;

		DecInBuf_R_Status = DecInBuf_R_Status & 0x0ffe;
	}

	if((DecInBuf_R_Status & 0x0004)==0x0004)    			//in_buffer2 empty(bit3)
	{

		SF_Read_DMA_Mode(g_SPI_DMA_Read_Type,(g_PlayDataAddr_R.HLWord[1]-0x40), g_PlayDataAddr_R.HLWord[0], g_InBufLengthB, (unsigned int*)gInputBuf22);
	    g_PlayDataAddr_R.DWord += g_InBufLengthB ;

		DecInBuf_R_Status = DecInBuf_R_Status & 0x0ffb;
	}
}



//======================Header Unpack Usage Function ====================


void SetMBEHeaderArrayAddrF(short HeaderStAddrF)
{

	__asm
	{
		X0=FP;
		R0=4;
		X0=X0-R0;
		Ix0=X0;
		X0 = RAM(Ix0,-1)
		Ix0 = (_MBEHeaderInfoF)
		RAM(Ix0) = X0

	}

}

void SetMBEHeaderArrayAddrB(short HeaderStAddrB)
{
	__asm
	{
		X0=FP;
		R0=4;
		X0=X0-R0;
		Ix0=X0;
		X0 = RAM(Ix0,-1)
		Ix0 = (_MBEHeaderInfoB)
		RAM(Ix0) = X0

	}
}

short GetMBEHeaderF(void)
{
short HeaderIndxF=0;
short temp1 =0;


while(1)
	{
		*(MBEHeaderInfoF+HeaderIndxF) = *(data_ptr1+HeaderIndxF);

		  if(*(MBEHeaderInfoF+HeaderIndxF) == (short)0xFFFF)
		      temp1++ ;
		  else
		  	  temp1 = 0;
           if(temp1 ==2)
				break;

		HeaderIndxF++;
	}
	g_SongDataAddr = HeaderIndxF + 1;	//YQ 2013-5-10 

	return (HeaderIndxF+1);
}


short GetMBEHeaderB(void)
{
short HeaderIndxB=0;
short temp1 =0;

while(1)
	{
		*(MBEHeaderInfoB+HeaderIndxB) = *(data_ptr2+HeaderIndxB);


		  if(*(MBEHeaderInfoB+HeaderIndxB) == (short)0xFFFF)
		      temp1++ ;
		  else
		  	  temp1 = 0;
           if(temp1 ==2)
				break;
		HeaderIndxB++;
	}


	return (HeaderIndxB+1);
}


//==================================================================================



void HeaderUnpack_F(void) // Getthe Foreground Data Info about Header ,wavemark,silence_detection
{

   unsigned int TempData1;
   long temp2 ;
   long temp3 ;

        //////////////////////////////////Get the Header Info ///////////////////////

   	    TempData1 = GetMBEHeaderF();
	    data_ptr1_StartAddr = data_ptr1+*(MBEHeaderInfoF+TempData1-3);//kevin
		CH1_AlgType	= *(MBEHeaderInfoF); //////
		samplerate	= *(MBEHeaderInfoF+1); /////
		if(CH1_AlgType == MUSIC96)  //the music96 bite is too big , the Orientation bitrate information is 1 word
		{
		  bitrate	= *(MBEHeaderInfoF+2); //////
		}
		else
		{
		  bitrate	= *(MBEHeaderInfoF+2)*10; //////
                }
		FrmLengthF	= (long)*(MBEHeaderInfoF+4) & (0x0000FFFF); //wensheng update 20100908 //

	    FrmLengthF	= FrmLengthF + ((long)*(MBEHeaderInfoF+5) << 16);

        //=======================================================
        #ifdef Orientation
		if (AB_PlayF_Flag==1)
		{
		    OrientationSetFunc((__RAM short)&gOffsetWord_F,CH1_AlgType, samplerate, bitrate, AB_PlayF_EndTime,0, 1, (__RAM short)&AB_PlayF_EndFrmcnt);
	      	AB_PlayF_Flag=0;
			FrmLengthF =AB_PlayF_EndFrmcnt;
			AB_PlayF_EndFrmcnt = 0;

		}
		#endif


		WaveMarkF_F   = *(MBEHeaderInfoF+8);
		SilenceDectFlagF = *(MBEHeaderInfoF+9);
		//===========================================Wen add 20110928=============

        PlayContiHead_Subframe = (*(MBEHeaderInfoF+11)) >> 5 ;

		DecodeProcess_Res_Sample_Number = (*(MBEHeaderInfoF+11)) & 0x001F;

		if ( *(MBEHeaderInfoF+8) ==1 )   // wavemark  enable
		{
			wavemark_ptrF =data_ptr1+TempData1;

			if ( *(MBEHeaderInfoF+9) ==1)  // silence detection enable
			   silence_ptrF = wavemark_ptrF + *(wavemark_ptrF);
		}
		else  // wave mark disable
		{
			if ( *(MBEHeaderInfoF+9) ==1)  // silence detection enable
    			silence_ptrF =data_ptr1+TempData1;//kevin

        }


		/////////////////////////////////Get g_uiWaveMark_Time ///////////////////
		if ( *(MBEHeaderInfoF+8) ==1 )
		{
		    wavemark_ptrF++ ;

		    if ((*(wavemark_ptrF) & 0x8000) == 0x8000)
            {

			   g_uiWaveMark_TimeF =  ( *(wavemark_ptrF) & 0x00007FFF )  ;

			   wavemark_ptrF++ ;
			   g_uiWaveMark_TimeF = (g_uiWaveMark_TimeF <<16 )+ (*(wavemark_ptrF) & 0x0000FFFF) ;

	        }
	        else
	        {
	           g_uiWaveMark_TimeF = *(wavemark_ptrF);

            }

			wavemark_ptrF ++;
		}


		/////////////////////////////////Get gSilence_Frame_StartF and gSilence_Frame_EndF  ///////////////////

	    if ( *(MBEHeaderInfoF+9) ==1)
	    {
		     silence_ptrF++ ;

		    if ((*(silence_ptrF) & 0x8000) == 0x8000)   //gSilence_Frame_StartF
            {

			   gSilence_Frame_StartF =  *(silence_ptrF) & 0x00007FFF;
			   silence_ptrF++ ;
			   gSilence_Frame_StartF = (gSilence_Frame_StartF << 16) + (*(silence_ptrF) & 0x0000FFFF);

	        }
	        else
	        {
	           gSilence_Frame_StartF = *(silence_ptrF);

            }

		   	silence_ptrF++ ;

		    if ((*(silence_ptrF) & 0x8000) == 0x8000)   //gSilence_Frame_EndF
            {

			   gSilence_Frame_EndF =  *(silence_ptrF) & 0x00007FFF;
			   silence_ptrF++ ;
			   gSilence_Frame_EndF = ( gSilence_Frame_EndF << 16) + (*(silence_ptrF) & 0x0000FFFF) ;
			   gSilence_Frame_EndF = gSilence_Frame_StartF +gSilence_Frame_EndF ;


	        }
	        else
	        {
	           gSilence_Frame_EndF = *(silence_ptrF)+ gSilence_Frame_StartF;

            }

			silence_ptrF++ ;


        }


		data_ptr1 = data_ptr1_StartAddr;


       //=============PlayConti=============================

	   if((PlayConti_Number*2-PlayConti_Length)!=0)
	   {
          if(bitrate == 32000)
		  {
	        data_ptr1 += 40 ;	//Kevin
			//gSPIBufoffset=gSPIBufoffset+40;
	      }
		  else if (bitrate == 28000)
		  {
		    data_ptr1 += 35 ;	//Kevin
			//gSPIBufoffset=gSPIBufoffset+ 35;
		  }
		  else if (bitrate == 24000)
		  {
		    data_ptr1 += 30 ;	//kevin
			//gSPIBufoffset=gSPIBufoffset+ 30;
		  }
		  else if (bitrate == 20000)
		  {
		    data_ptr1 += 25 ;
			//gSPIBufoffset=gSPIBufoffset+ 25;
		  }
		  else if (bitrate == 16000)
		  {
		    data_ptr1 += 20 ;
			//gSPIBufoffset=gSPIBufoffset+ 20;
		  }
			g_DecodeFrmCntF+=1;


	   }

        __asm
		{

		  PUSH IX0
		  PUSH R0
		  PUSH R1

		  Ix0 = (_data_ptr1)
		  R0  = RAM(Ix0,1)
          R1  = RAM(Ix0,1)
		  Ix0 = (_g_PlayDataAddr)

		  RAM(Ix0,1) =R0
		  RAM(Ix0) =R1

		  POP  R1
		  POP  R0
		  POP  IX0

		}

}




void HeaderUnpack_B(void) // Getthe Background Data Info about Header ,wavemark,silence_detection
{
   short TempData2 ;

        //////////////////////////////////Get the Header Info ///////////////////////

   	    TempData2 = GetMBEHeaderB();
		data_ptr2_StartAddr = data_ptr2+*(MBEHeaderInfoB+TempData2-3);
		CH2_AlgType	= *(MBEHeaderInfoB); //////
		samplerate	= *(MBEHeaderInfoB+1); /////
		bitrate		= *(MBEHeaderInfoB+2)*10; //////
		FrmLengthB	= (long)*(MBEHeaderInfoB+4) & (0x0000FFFF);// //wensheng update 20100908 //
		FrmLengthB	= FrmLengthB + ((long)*(MBEHeaderInfoB+5) << 16);

        #ifdef Orientation
        if (AB_PlayB_Flag==1)
		{
		    OrientationSetFunc((__RAM short)&gOffsetWord_B,CH2_AlgType, samplerate, bitrate, AB_PlayB_EndTime,0, 1, (__RAM short)&AB_PlayB_EndFrmcnt);
	        OrientationTrigFlag_B = 0;
			AB_PlayB_Flag=0;
			FrmLengthB =AB_PlayB_EndFrmcnt;

		}
		#endif


		WaveMarkF_B   = *(MBEHeaderInfoB+8);
		SilenceDectFlagB = *(MBEHeaderInfoB+9);

       //////////////////////////////////Get WaveMark and SilenceDetection Info pointer ///////////////////////

		if ( *(MBEHeaderInfoB+8) ==1 )   // wavemark  enable
		{
			wavemark_ptrB =data_ptr2+TempData2;
			if ( *(MBEHeaderInfoB+9) ==1)  // silence detection enable
			   silence_ptrB = wavemark_ptrB + *(wavemark_ptrB);
		}
		else  // wave mark disable
		{
			if ( *(MBEHeaderInfoB+9) ==1)  // silence detection enable
				silence_ptrB =data_ptr2+TempData2;
        }


		/////////////////////////////////Get g_uiWaveMark_Time ///////////////////

		if ( *(MBEHeaderInfoB+8) ==1 )
		{
		    wavemark_ptrB++ ;

		    if ((*(wavemark_ptrB) & 0x8000) == 0x8000)
            {
	           g_uiWaveMark_TimeB =  (*(wavemark_ptrB) & 0x00007FFF );
			   wavemark_ptrB++ ;
			   g_uiWaveMark_TimeB =(g_uiWaveMark_TimeB << 16 )+ (*(wavemark_ptrB) & 0x0000FFFF) ;

	        }
	        else
	        {
	           g_uiWaveMark_TimeB = *(wavemark_ptrB);

            }

			wavemark_ptrB ++;
		}


		/////////////////////////////////Get gSilence_Frame_StartB and gSilence_Frame_EndB  ///////////////////

	    //if ( *(MBEHeaderInfoF+9) ==1)  //the bug ,2012.12.20 modify 
        if ( *(MBEHeaderInfoB+9) ==1)    //background play should use the MBEHeaderInfoB, not MBEHeaderInfoF
	    {


		    silence_ptrB++ ;

		    if ((*(silence_ptrB) & 0x8000) == 0x8000)   //gSilence_Frame_StartF
            {

			   gSilence_Frame_StartB =  (*(silence_ptrB) & 0x00007FFF);
			   silence_ptrB++ ;
			   gSilence_Frame_StartB = (gSilence_Frame_StartB << 16) + (*(silence_ptrB) & 0x0000FFFF);

	        }
	        else
	        {
	           gSilence_Frame_StartB = *(silence_ptrB);

            }

		   	silence_ptrB++ ;

		    if ((*(silence_ptrB) & 0x8000) == 0x8000)   //gSilence_Frame_EndF
            {

			   gSilence_Frame_EndB =  (*(silence_ptrB) & 0x00007FFF);
			   silence_ptrB++ ;
			   gSilence_Frame_EndB =  (gSilence_Frame_EndB << 16) + (*(silence_ptrB) & 0x0000FFFF) ;
			   gSilence_Frame_EndB = gSilence_Frame_StartB +gSilence_Frame_EndB ;


	        }
	        else
	        {
	           gSilence_Frame_EndB = *(silence_ptrB)+ gSilence_Frame_StartB;

            }

			silence_ptrB++ ;

        }



		data_ptr2 = data_ptr2_StartAddr;


		__asm
		{
		  Ix0 = (_data_ptr2)
		  R0  = RAM(Ix0,1)
          R1  = RAM(Ix0,1)
		  Ix0 = (_g_PlayDataAddr_R)

		  RAM(Ix0,1) =R0
		  RAM(Ix0) =R1

		}



	   /*g_PlayDataAddr_R.HLWord[1] = (unsigned int)(data_ptr2 + 1);
	   g_PlayDataAddr_R.HLWord[0] = (unsigned int)(data_ptr2);*/

}




void USetBitstreamLabelF(__GENERIC int *Inptr)
{
	__asm
	{
	 	X0=FP;
		R0=4;
		X0=X0-R0;
		Ix1=X0;
	 	Ix0=(_data_ptr1+1);//RC
	 	X0=RAM(Ix1,-1);
	 	RAM(Ix0,-1)=X0; //low
	 	X0=RAM(Ix1);
		RAM(Ix0)=X0;//high
	}
}

void USetBitstreamLabelB(__GENERIC int *Inptr)
{
	__asm
	{
		X0=FP;
		R0=4;
		X0=X0-R0;
		Ix1=X0;
	 	Ix0=(_data_ptr2+1);//RC
	 	X0=RAM(Ix1,-1);
	 	RAM(Ix0,-1)=X0; //low
	 	X0=RAM(Ix1);
		RAM(Ix0)=X0;//high
	}
}

void ResetWDT(void)
{
  __asm
  {
    	R1=WDT;
  	 	R1=BSET.14 R1;
  	 	WDT=R1;
  }
}





#ifdef WaveMark




void WaveMarkF_Enable(void)
{

   // g_uiWaveMark_TimeF =0 ;
    g_uiMarkCodeF =(short)0xFFFF ;
	g_uiWaveMark_1ms_CounterF =0;
	PlayWaveMarkFlagF =1;
	g_uiWaveMarkN_F = 0 ;

}

void WaveMarkB_Enable(void)
{

//	g_uiWaveMark_TimeB =0 ;
    g_uiMarkCodeB =(short)0xFFFF ;
	g_uiWaveMark_1ms_CounterB =0;
	PlayWaveMarkFlagB =1;
	g_uiWaveMarkN_B = 0 ;

}












//=============================WaveMark Usage============================

void  WaveMark_Routine_F(void)
{
   __asm
   {

	  PUSH  Iy0bk
      PUSH  Iy0

	  // ==============================================================
	  // if WaveMarkFlag =1 , then ckeck the WaveMarkRoutine
	  // ==============================================================
	  // if ( WaveMarkFlag ==1 )
	  // ==============================================================
	  Ix0 = (_WaveMarkF_F)
	  X0 = RAM(Ix0,-1)
      X0 = X0 - 1
      JNZ CheckWaveMarkEndF

      // ==============================================================
	  // if(g_uiWaveMark_1ms_CounterF >= g_uiWaveMark_TimeF)
	  // ==============================================================


	  Ix0 = (_g_uiWaveMark_1ms_CounterF)
      Ix1 = (_g_uiWaveMark_TimeF)
	  R0 = RAM(Ix0,1)
      R1 = RAM(Ix0)
      X0 = RAM(Ix1,1)
      Y0 = RAM(Ix1,-1)
      R0 = R0 - X0
      JAC @f
      R1 = R1 - 1
      @@:
      R1 = R1 - Y0
      R1 = BTST.15 R1
      JNZ CheckWaveMarkEndF


      // ==============================================================
	  // if the  (*wavemark_ptrF) = 0xFFFF ,
	  // don't update g_uiWaveMark_TimeF and wavemark_ptrF
	  //
	  // if the  (*wavemark_ptrF) != 0xFFFF
	  // Get the MarkCode
	  // ==============================================================

	  // ==============================================================
	  // if(*wavemark_ptrF) == 0xFFFF
	  // ==============================================================
      Ix0 = (_wavemark_ptrF)
	  R0 = RAM(Ix0,1)
      Iy0 = R0
      R0 = RAM(Ix0)
      Iy0bk = R0
      R0 = ROM(Iy0,1)
      R1 = 0xFFFF
      R1 = R1 - R0
	  JNZ @f
	  JMP CheckWaveMarkEndF  // if meet the wavemark stop code

	  // ==============================================================
	  // g_uiMarkCode = *wavemark_ptrF
	  // ==============================================================
    @@:
	  Ix0 = (_g_uiMarkCodeF)
	  RAM(Ix0) = R0



	  R0 = ROM(Iy0,1)
      R1 = BTST.15 R0
      JZ Check16bitMarkDataF

	  // ==============================================================
	  //  if continuous twice 0xFFFF,0XFFFF ,
	  //  Means,the Current voice have no wavemark ,upadte wavemark_ptrF
	  //
	  //  if (*wavemark_ptrF == 0xFFFF ) &&  (*wavemark_ptrF == 0xFFFF )
	  //  then wavemark_ptrF =wavemark_ptrF-2
	  // ==============================================================

	  R1 = ROM(Iy0,1)
      Y1 = R0 - R1
      JNZ @f
      Y1 = 0xFFFF
      Y1 = R0 - Y1
	  JNZ @f

	  R1 = ROM(Iy0,-1)
      R1 = ROM(Iy0,-1)
	  Ix0 = (_wavemark_ptrF)
	  R0 = RAM(Ix0,1)
      R0 = Iy0bk
      RAM(Ix0,-1) = R0
      R0 = Iy0
      RAM(Ix0) = R0
      JMP CheckWaveMarkEndF

   	  // ==============================================================
	  // then update g_uiWaveMark_TimeF and wavemark_ptrF
	  // check g_uiWaveMark_TimeF length is 16bit or 32bit
	  //
	  //
	  // wavemark_ptrF++                                          //16bit
	  // g_uiWaveMark_TimeF =g_uiWaveMark_TimeF + *wavemark_ptrF
	  // wavemark_ptrF++
	  // g_uiWaveMark_TimeF =g_uiWaveMark_TimeF + *wavemark_ptrF  //32bit
	  //
	  // ==============================================================

   @@:
      //==============================================================================
      R0 =BCLR.15 R0 // the 32 bit adder // bit15 =0  ==  ( HWord & 0x7FFF) + LWord
	  //===========================================================================
      R1 = X0 + R1
      R0 = R0 + Y0 + C
      RAM(Ix1,1) = R1
      RAM(Ix1) = R0

	  Ix0 = (_wavemark_ptrF)
	  R0 = RAM(Ix0,1)
	  R0 = Iy0bk
      RAM(Ix0,-1) = R0
	  R0 = Iy0
      RAM(Ix0) = R0
	  JMP CheckWaveMarkEndF




	  Check16bitMarkDataF:

      R1 = 0
      R0 = R0 + X0
      R1 = R1 + Y0 + C
      RAM(Ix1,1) = R0
      RAM(Ix1) = R1

	  Ix0 = (_wavemark_ptrF)
	  R0 = RAM(Ix0,1)
	  R0 = Iy0bk
      RAM(Ix0,-1) = R0
	  R0 = Iy0
      RAM(Ix0) = R0


      CheckWaveMarkEndF :

	  POP Iy0
      POP Iy0bk



   }



}



void  WaveMark_Routine_B(void)
{
   __asm
   {

	  PUSH  Iy0bk
      PUSH  Iy0

	  // ==============================================================
	  // if WaveMarkFlag =1 , then ckeck the WaveMarkRoutine
	  // ==============================================================
	  // if ( WaveMarkFlag ==1 )
	  // ==============================================================
	  Ix0 = (_WaveMarkF_B)
	  X0 = RAM(Ix0,-1)
      X0 = X0 - 1
      JNZ CheckWaveMarkEndB

      // ==============================================================
	  // if(g_uiWaveMark_1ms_CounterF >= g_uiWaveMark_TimeF)
	  // ==============================================================


	  Ix0 = (_g_uiWaveMark_1ms_CounterB)
      Ix1 = (_g_uiWaveMark_TimeB)
	  R0 = RAM(Ix0,1)
      R1 = RAM(Ix0)
      X0 = RAM(Ix1,1)
      Y0 = RAM(Ix1,-1)
      R0 = R0 - X0
      JAC @f
      R1 = R1 - 1
      @@:
      R1 = R1 - Y0
      R1 = BTST.15 R1
      JNZ CheckWaveMarkEndB


      // ==============================================================
	  // if the  (*wavemark_ptrF) = 0xFFFF ,
	  // don't update g_uiWaveMark_TimeF and wavemark_ptrF
	  //
	  // if the  (*wavemark_ptrF) != 0xFFFF
	  // Get the MarkCode
	  // ==============================================================

	  // ==============================================================
	  // if(*wavemark_ptrF) == 0xFFFF
	  // ==============================================================
      Ix0 = (_wavemark_ptrB)
	  R0 = RAM(Ix0,1)
      Iy0 = R0
      R0 = RAM(Ix0)
      Iy0bk = R0
      R0 = ROM(Iy0,1)
      R1 = 0xFFFF
      R1 = R1 - R0
	  JNZ @f
	  JMP CheckWaveMarkEndB   // if meet the wavemark stop code

	  // ==============================================================
	  // g_uiMarkCode = *wavemark_ptrF
	  // ==============================================================
    @@:
	  Ix0 = (_g_uiMarkCodeB)
	  RAM(Ix0) = R0



	  R0 = ROM(Iy0,1)
      R1 = BTST.15 R0
      JZ Check16bitMarkDataB

	  // ==============================================================
	  //  if continuous twice 0xFFFF,0XFFFF ,
	  //  Means,the Current voice have no wavemark ,upadte wavemark_ptrF
	  //
	  //  if (*wavemark_ptrF == 0xFFFF ) &&  (*wavemark_ptrF == 0xFFFF )
	  //  then wavemark_ptrF =wavemark_ptrF-2
	  // ==============================================================

	  R1 = ROM(Iy0,1)
      Y1 = R0 - R1
      JNZ @f
      Y1 = 0xFFFF
      Y1 = R0 - Y1
	  JNZ @f

	  R1 = ROM(Iy0,-1)
      R1 = ROM(Iy0,-1)
	  Ix0 = (_wavemark_ptrB)
	  R0 = RAM(Ix0,1)
      R0 = Iy0bk
      RAM(Ix0,-1) = R0
      R0 = Iy0
      RAM(Ix0) = R0
      JMP CheckWaveMarkEndB

   	  // ==============================================================
	  // then update g_uiWaveMark_TimeF and wavemark_ptrF
	  // check g_uiWaveMark_TimeF length is 16bit or 32bit
	  //
	  //
	  // wavemark_ptrF++                                          //16bit
	  // g_uiWaveMark_TimeF =g_uiWaveMark_TimeF + *wavemark_ptrF
	  // wavemark_ptrF++
	  // g_uiWaveMark_TimeF =g_uiWaveMark_TimeF + *wavemark_ptrF  //32bit
	  //
	  // ==============================================================

   @@:
      //==============================================================================
      R0 =BCLR.15 R0 // the 32 bit adder // bit15 =0  ==  ( HWord & 0x7FFF) + LWord
	  //===============================================================================
      R1 = X0 + R1
      R0 = R0 + Y0 + C
      RAM(Ix1,1) = R1
      RAM(Ix1) = R0

	  Ix0 = (_wavemark_ptrB)
	  R0 = RAM(Ix0,1)
	  R0 = Iy0bk
      RAM(Ix0,-1) = R0
	  R0 = Iy0
      RAM(Ix0) = R0

	  JMP CheckWaveMarkEndB



	  Check16bitMarkDataB:

      R1 = 0
      R0 = R0 + X0
      R1 = R1 + Y0 + C
      RAM(Ix1,1) = R0
      RAM(Ix1) = R1

	  Ix0 = (_wavemark_ptrB)
	  R0 = RAM(Ix0,1)
	  R0 = Iy0bk
      RAM(Ix0,-1) = R0
	  R0 = Iy0
      RAM(Ix0) = R0


      CheckWaveMarkEndB :

	  POP Iy0
      POP Iy0bk
   }

}

//==================================================================================
#endif





#ifdef SilenceDetection

//=============================SilenceDetection Usage============================

short Silence_Detection_Func(short gSilenceDectFlag_Local, short gSilence_Frame_StartAddr , short g_DecodeFrmCntAddr , short gSilence_Frame_EndAddr,short gAlgTypeAddr,short gsubframeindexAddr , short silence_ptr)
{
short ReturnTemp;

ReturnTemp = 0;
__asm
  {


     PUSH Iy0bk
     PUSH Iy0

     X0=FP;
	 R0=4;
	 X0=X0-R0
	 Ix0=X0      //Ix0 =(_SilenceDectFlag_Local)

     X0 = RAM(Ix0,-1)
     X0 = X0 - 1
     JFNZ SilenceDetectEndL   // if( SilenceDectFlagB == 1)


     X1 = RAM(Ix0,-1) //gSilence_Frame_StartAddr
     X0 = RAM(Ix0) //g_DecodeFrmCntAddr
     R1 = Ix0
     Y1 = R1  // The Ix0 temp for g_DecodeFrmCntAddr

     Ix0 = X0  //g_DecodeFrmCntAddr
     Ix1 = X1  //gSilence_Frame_StartAddr

     R0 = RAM(Ix0,1)
     R1 = RAM(Ix0)
     X0 = RAM(Ix1,1)
     Y0 = RAM(Ix1,-1)
     R0 = R0 - X0
     JAC @f
     R1 = R1 - 1
  @@:
     R1 = R1 - Y0
     R1 = BTST.15 R1
     JFNZ SilenceDetectEndL    //g_DecodeFrmCntAddr >= gSilence_Frame_StartAddr

     }

	 ReturnTemp = 1; // indicate current state is in silence interval

    __asm
    {

    R0 = Y1    // The Ix0 temp for g_DecodeFrmCntAddr
	R1 = 2
    R0 = R0 - R1
    Ix0 = R0 // The Ix0 temp for gAlgTypeAddr
    X0  = RAM(Ix0,-1) //gAlgTypeAddr
    R0  = RAM(Ix0) //gsubframeindexAddr
    Ix1= R0
	R0  = RAM(Ix1)
	R0  = R0 +1
	RAM(Ix1) = R0
    //X1 = X1 +1
    //RAM(Ix0)=X1  //gsubframeindexAddr+1


    R0=0x5541 //Audio32
    R0= R0-X0
    JNZ @SNX8K

    R0 = RAM(Ix1)
    R1 =10     // Audio32 => 10 subframe update DecodeFrmCnt
    R0 = R0-R1
    JZ @Updtae_subframeindex_DecodeFrmCnt
    JMP @Silence_Frame_End_Check

@SNX8K :
    R0=0x3947   //2013.01.08
	R0=R0-X0
	JNZ @IMAADPCM

    R0 = RAM(Ix1)
    R1 =2
    R0 = R0-R1 // SNX8K => 2 subframe update DecodeFrmCnt
    JZ @Updtae_subframeindex_DecodeFrmCnt
    JMP @Silence_Frame_End_Check

@IMAADPCM :
    R0=0x4D49   //2013.01.08
	R0=R0-X0
	JNZ @MUSIC96

    R0 = RAM(Ix1)
    R1 =4
    R0 = R0-R1 // IMAADPCM => 4 subframe update DecodeFrmCnt
    JZ @Updtae_subframeindex_DecodeFrmCnt
    JMP @Silence_Frame_End_Check

@MUSIC96:

    R0 = RAM(Ix1)  //2013.01.08
    R1 =36
    R0 = R0-R1 // IMAADPCM => 36 subframe update DecodeFrmCnt
    JZ @Updtae_subframeindex_DecodeFrmCnt
    JMP @Silence_Frame_End_Check



@Updtae_subframeindex_DecodeFrmCnt:  // gsubframeindexAddr =0 and  g_DecodeFrmCntAddr ++
    R0= RAM(Ix0)
	Ix1 = R0
	R0 = 0
    RAM(Ix1)=R0 // gsubframeindexAddr =0

    R0 = Y1
    Ix0 = R0 // The Ix0 temp for g_DecodeFrmCntAddr
    R0=RAM(Ix0)
    Ix1 = R0
    R0 = RAM(Ix1)
	R0 = R0+1
	RAM(Ix1) = R0

@Silence_Frame_End_Check:

    R0=Y1   // The Ix0 temp for g_DecodeFrmCntAddr
    Ix0 = R0
    X1=RAM(Ix0,-1) //g_DecodeFrmCntAddr
   /* R0=R0+1
    Ix0 = R0*/
    X0 =RAM(Ix0) //gSilence_Frame_EndAddr


    Ix0 = X1  //g_DecodeFrmCntAddr
    Ix1 = X0  //gSilence_Frame_EndAddr

    R0 = RAM(Ix0,1)        // g_DecodeFrmCntAddr >= gSilence_Frame_EndAddr
    R1 = RAM(Ix0)
    X0 = RAM(Ix1,1)
    Y0 = RAM(Ix1,-1)
    R0 = R0 - X0
    JAC @f
    R1 = R1 - 1
    @@:
    R1 = R1 - Y0
    R1 = BTST.15 R1
    JNZ SilenceDetectEndL

    R0= Y1   // The Ix0 temp for g_DecodeFrmCntAddr    //gSilence_Frame_StartAddr update
    R0= R0-1
	Ix0 = R0
    R0 = RAM(Ix0)
    Ix1 =R0
    X0 = RAM(Ix1,1)     //gSilence_Frame_EndAddr
    Y0 = RAM(Ix1,1)

    R0=Y1   // The Ix0 temp for g_DecodeFrmCntAddr
	R1 =4
    R0 =R0-R1
    Ix0 = R0  //The Ix0 temp for  silence_ptr
    R0 =RAM(Ix0)
	Ix0 =R0
    R0 = RAM(Ix0,1)
    Iy0 = R0
    R0 = RAM(Ix0)
    Iy0bk = R0

    R0 = ROM(Iy0,1)
    R1 = BTST.15 R0
    JZ @@Check16bitSilenceDataS  //


    R1 = ROM(Iy0,1)
    X1 = R0 - R1
    JNZ @f
    X1 = 0xFFFF
    X1 = R0 - X1
    JNZ @f
                     // //gSilence_Frame_StartAddr update 0xFFFF ,0xFFFF

    R0= Y1   // The Ix0 temp for g_DecodeFrmCntAddr    //gSilence_Frame_EndAddr update
    R0= R0+1
	Ix0 = R0
	R0 =RAM(Ix0)
	Ix1 = R0
	R0 =0XFFFF
    RAM(Ix1,1) =R0     //gSilence_Frame_StartAddr
	R0=0x7FFF
    RAM(Ix1) =R0




  /*  R1 = ROM(Iy0,-1)
    R1 = ROM(Iy0,-1)
    R0 = Iy0bk
    RAM(Ix0,-1) = R0
    R0 = Iy0
    RAM(Ix0) = R0*/
    }

	ReturnTemp = 1;


    __asm
	{


    JMP SilenceDetectEndL // Stop Code Condition
@@:
    //==============================================================================

    R0 =BCLR.15 R0 // the 32 bit adder // bit15 =0  ==  ( HWord & 0x7FFF) + LWord
	//===============================================================================
    R1 = X0 + R1         // 32 bit adder
    R0 = R0 + Y0 + C
    RAM(Ix1,1) = R1
    RAM(Ix1) = R0
    R0 = Iy0bk
    RAM(Ix0,-1) = R0
    R0 = Iy0
    RAM(Ix0) = R0

    JMP @@Silence_Frame_EndAddr_update

@@Check16bitSilenceDataS :
    R1 = 0
    R0 = R0 + X0
    R1 = R1 + Y0 + C
    RAM(Ix1,1) = R0
    RAM(Ix1) = R1
    R0 = Iy0bk
    RAM(Ix0,-1) = R0
    R0 = Iy0
    RAM(Ix0) = R0

	JMP @@Silence_Frame_EndAddr_update


@@Silence_Frame_EndAddr_update :


    R0= Y1   // The Ix0 temp for g_DecodeFrmCntAddr    //gSilence_Frame_EndAddr update
    R0= R0+1
	Ix0 = R0
	R0 =RAM(Ix0)
	Ix1 = R0
    X0 = RAM(Ix1,-1)     //gSilence_Frame_StartAddr
    Y0 = RAM(Ix1,-1)


    R0=Y1   // The Ix0 temp for g_DecodeFrmCntAddr
	R1 =4
    R0 =R0-R1
    Ix0 = R0  //The Ix0 temp for  silence_ptr
    R0 =RAM(Ix0)
	Ix0 =R0
    R0 = RAM(Ix0,1)
    Iy0 = R0
    R0 = RAM(Ix0)
    Iy0bk = R0


	R0 = ROM(Iy0,1)
    R1 = BTST.15 R0
    JZ @@Check16bitSilenceDataE  //
	//==============================================================================
	R0 =BCLR.15 R0 // the 32 bit adder // bit15 =0  ==  ( HWord & 0x7FFF) + LWord
	R1 =ROM(Iy0)
    //===============================================================================
	R1 = X0 + R1         // 32 bit adder
    R0 = R0 + Y0 + C
    RAM(Ix1,1) = R1
    RAM(Ix1) = R0
    R0 = Iy0bk
    RAM(Ix0,-1) = R0
    R0 = Iy0
    RAM(Ix0) = R0

	JMP SilenceDetectEndL

@@Check16bitSilenceDataE  :

    R1 = 0
    R0 = R0 + X0
    R1 = R1 + Y0 + C
    RAM(Ix1,1) = R0
    RAM(Ix1) = R1
    R0 = Iy0bk
  //  RAM(Ix0,-1) = R0
    RAM(Ix0,-1) = R0
    R0 = Iy0
    RAM(Ix0) = R0


SilenceDetectEndL :


        POP Iy0
        POP Iy0bk  //  return 0 ; // SilenceDectFlagF =0


}
	return ReturnTemp;
}


//===========================================================================
#endif



//======================SysCommon.c===========================================

//============================================================================
//=================== Input Buffer and Header Section Start ==================
//============================================================================
	__asm
	{
  	   extern data 	inbufstatus
  	   extern data 	inbufindx
  	   extern data 	curinbuf1
  	   extern data 	curinbuf2
  	   extern data 	Dec_NFa

		SYSCOM_PUSH_RAMBK macro
 		PUSH RAMBK
  		R1 = (inbufindx).h
  		RAMBK = R1
  		endm

  		SYSCOM_POP_RAMBK	macro
  		POP RAMBK
  		endm
	}


void ReadWrite_Inbuf_Load(short *InBuf11, short *InBuf12, short length, unsigned short Status, unsigned short indx)
{
	__asm
	{
		X0=FP;
		R0=4;
		X0=X0-R0;
		Ix0=X0;
		SYSCOM_PUSH_RAMBK
		X0=RAM(Ix0,-1);
		curinbuf1=X0;
		X0=RAM(Ix0,-1);
		curinbuf2=X0;
		X0=RAM(Ix0,-1);
		Dec_NFa=X0;
		X0 = RAM(Ix0,-1)
		inbufstatus = X0
		X0 = RAM(Ix0)
		inbufindx = X0

        SYSCOM_POP_RAMBK
	}
}

void ReadWrite_Inbuf_Save(short Status, short indx)
{
	__asm
	{
		X0=FP;
		R0=4;
		X0=X0-R0;
		Ix0=X0;
		SYSCOM_PUSH_RAMBK
		R0 = RAM(Ix0,-1)
		R1 = RAM(Ix0)
		X0 = inbufstatus
		Ix0 = R0
		RAM(Ix0) = X0
		Ix0 = R1
		X0 = inbufindx
		RAM(Ix0) = X0

        SYSCOM_POP_RAMBK
	}
}


void GetInBufWord_L(void)
{

	__asm
	{
			//Ix1,Ix0,R1,Y0,*R0,*X1
	 			//PUSH Ix1;
				PUSH Ix0;
				PUSH R1;
				PUSH Y0;
				PUSH X0;
				//PUSH R0

				SYSCOM_PUSH_RAMBK

				//Ix1=(_DecInBuf_Status);
				//Y0=RAM(Ix1); //Y0=MelodyBuf_Status
				Y0 = inbufstatus
				R0 = 0

				X0=0x0002;
				R1=X0 AND Y0;
				R1=X0-R1;	 //if((MelodyBuf_Status & 0x0002) == 0x0002)
				JNZ ChkBuf12Use;
				R0=curinbuf1;
				R1=inbufindx;
				R0=R1+R0;
				Ix0=R0;
				R0=RAM(Ix0); //output==>X1
				X0=0;
				RAM(Ix0)=X0; //DecInBuf11[IndxInBuf]=0;
				R1=R1+1;
				inbufindx=R1;//IndxInBuf++

			checkbuflength11:
				X0=Dec_NFa;
				R1=R1-X0;	 //if(IndxInBuf == Length1)
				JZ ReSetBuf1;

				JMP GetInWordEnd;
ReSetBuf1:
				inbufindx=R1; //IndxInBuf = 0

				X0=0x000d;
				R1=X0 AND Y0; //MelodyBuf_Status = MelodyBuf_Status & 0x000d
				X0=0x0009;
				R1=X0 OR R1;  //setting input buffer12 is in used && setting input buffer11 is empty
				inbufstatus = R1
				//RAM(Ix1)=R1;


				JMP GetInWordEnd;
ChkBuf12Use:
				X0=0x0008;
				R1=X0 AND Y0;
				R1=X0-R1; //if((MelodyBuf_Status & 0x0008) == 0x0008)
				JNZ GetInWordEnd;
				R0=curinbuf2;
				R1=inbufindx;
				R0=R1+R0;
				Ix0=R0;
				R0=RAM(Ix0); //output==>X1
				X0=0;
				RAM(Ix0)=X0; //DecInBuf12[IndxInBuf]=0;
				R1=R1+1;
				inbufindx=R1;//IndxInBuf++

			checkbuflength12:
				X0=Dec_NFa;
				R1=R1-X0;	 //if(IndxInBuf == Length1)
				JZ ReSetBuf2;

				JMP GetInWordEnd;
ReSetBuf2:
				inbufindx=R1; //IndxInBuf = 0

				X0=0x0007;
				R1=X0 AND Y0; //MelodyBuf_Status = MelodyBuf_Status & 0x0007
				X0=0x0006;
				R1=X0 OR R1;  //setting input buffer12 is in used && setting input buffer11 is empty
				inbufstatus = R1
				//RAM(Ix1)=R1;


GetInWordEnd:
				SYSCOM_POP_RAMBK

				//POP R0
				POP X0;
				POP Y0;
				POP R1;
				POP Ix0;
				//POP Ix1;
	}
}



#ifdef Orientation //Dec_Orientation
// ======== 定位系統 Start========//
void CalAlgBitFrmFunc(void)
{
	__asm
	{
		Y0 = 0x5541 // Audio32
		Y0 = X0 - Y0
		JZ CalAudio32BitFrmL
		Y0 = 0x3947	// SNX8K
		Y0 = X0 - Y0
		JZ CalSNX8KBitFrmL
	/*	Y0 = 0x534D	// MSADPCM
		Y0 = X0 - Y0
		JZ CalMSADPCMBitFrmL
		Y0 = 0x4148	// HASC
		Y0 = X0 - Y0
		JZ CalHASCBitFrmL
		Y0 = 0x5244	// DRC
		Y0 = X0 - Y0
		JFZ CalDRCBitFrmL
		Y0 = 0x524C	// LRC5
		Y0 = X0 - Y0
		JFZ CalLRC5BitFrmL*/
		Y0 = 0x554D	// Music96
		Y0 = X0 - Y0
		JFZ CalMusic96BitFrmL

		//JMP CalAlgBitFrmEndL
		// ======== Audio32 Start =======//
	   CalAudio32BitFrmL:
	   	Y1 = 3277
		Y0 = 16000
		Y0 = R1 - Y0
		JZ SetBitFrmAudio3216KbpsL
		Y0 = 20000
		Y0 = R1 - Y0
		JZ SetBitFrmAudio3220KbpsL
		Y0 = 24000
		Y0 = R1 - Y0
		JZ SetBitFrmAudio3224KbpsL
		Y0 = 28000
		Y0 = R1 - Y0
		JZ SetBitFrmAudio3228KbpsL
		Y0 = 32000
		Y0 = R1 - Y0
		JZ SetBitFrmAudio3232KbpsL
		JMP CalAlgBitFrmEndL

	   SetBitFrmAudio3216KbpsL:
		Y0 = 320
		JMP CalAlgBitFrmEndL
	   SetBitFrmAudio3220KbpsL:
		Y0 = 400
		JMP CalAlgBitFrmEndL
	   SetBitFrmAudio3224KbpsL:
		Y0 = 480
		JMP CalAlgBitFrmEndL
	   SetBitFrmAudio3228KbpsL:
		Y0 = 560
		JMP CalAlgBitFrmEndL
	   SetBitFrmAudio3232KbpsL:
		Y0 = 640
		JMP CalAlgBitFrmEndL
		// ======== Audio32 End =======//

		// ======== SNX8K Start =======//
	   CalSNX8KBitFrmL:
	   	Y1 = 6554
	   	Y0 = 8000
		Y0 = R0 - Y0
		JZ CheckSNX8K_SREndL
		Y0 = 10000
		Y0 = R0 - Y0
		JNZ CheckSNX8K_SREndL
		Y1 = 8192
	   CheckSNX8K_SREndL:
		Y0 = 80
		JMP CalAlgBitFrmEndL
		// ======== SNX8K End =======//

		// ======== MSADPCM Start =======//
	   /*CalMSADPCMBitFrmL:
		Y0 = 8000
		Y0 = R0 - Y0
		JNZ CheckMSADPCMSR10kL
		Y1 = 4096
		JMP CheckMSADPCMSRXXkEndL
	   CheckMSADPCMSR10kL:
		Y0 = 10000
		Y0 = R0 - Y0
		JNZ CheckMSADPCMSR12kL
		Y1 = 5120
		JMP CheckMSADPCMSRXXkEndL
	   CheckMSADPCMSR12kL:
		Y0 = 12000
		Y0 = R0 - Y0
		JNZ CheckMSADPCMSR14kL
		Y1 = 6144
		JMP CheckMSADPCMSRXXkEndL
	   CheckMSADPCMSR14kL:
		Y0 = 14000
		Y0 = R0 - Y0
		JNZ CheckMSADPCMSR16kL
		Y1 = 7168
		JMP CheckMSADPCMSRXXkEndL
	   CheckMSADPCMSR16kL:
		Y1 = 8192
	   CheckMSADPCMSRXXkEndL:
		Y0 = 560
		JMP CalAlgBitFrmEndL*/
		// ======== MSADPCM End =======//

		// ======== HASC Start =======//
	   /*CalHASCBitFrmL:
		Y0 = 8000
		Y0 = R0 - Y0
		JNZ CheckHASCSR10kL
		Y1 = 4096
		JMP CheckHASCSRXXkEndL
	   CheckHASCSR10kL:
		Y0 = 10000
		Y0 = R0 - Y0
		JNZ CheckHASCSR12kL
		Y1 = 5120
		JMP CheckHASCSRXXkEndL
	   CheckHASCSR12kL:
		Y0 = 12000
		Y0 = R0 - Y0
		JNZ CheckHASCSR14kL
		Y1 = 6144
		JMP CheckHASCSRXXkEndL
	   CheckHASCSR14kL:
		Y0 = 14000
		Y0 = R0 - Y0
		JNZ CheckHASCSR16kL
		Y1 = 7168
		JMP CheckHASCSRXXkEndL
	   CheckHASCSR16kL:
		Y1 = 8192
	   CheckHASCSRXXkEndL:
		Y0 = 10000
		Y0 = R1 - Y0
		JNZ CheckHASCBR12kL
		Y0 = 160
		JMP CalAlgBitFrmEndL
	   CheckHASCBR12kL:
		Y0 = 12000
		Y0 = R1 - Y0
		JNZ CheckHASCBR14kL
		Y0 = 192
		JMP CalAlgBitFrmEndL
	   CheckHASCBR14kL:
		Y0 = 14000
		Y0 = R1 - Y0
		JNZ CheckHASCBR16kL
		Y0 = 224
		JMP CalAlgBitFrmEndL
	   CheckHASCBR16kL:
		Y0 = 16000
		Y0 = R1 - Y0
		JNZ CheckHASCBR20kL
		Y0 = 256
		JMP CalAlgBitFrmEndL
	   CheckHASCBR20kL:
		Y0 = 20000
		Y0 = R1 - Y0
		JNZ CheckHASCBR24kL
		Y0 = 320
		JMP CalAlgBitFrmEndL
	   CheckHASCBR24kL:
		Y0 = 24000
		Y0 = R1 - Y0
		JGT CheckHASCBR29kL
		Y0 = 384
		JMP CalAlgBitFrmEndL
	   CheckHASCBR29kL:
	   	Y0 = 464
		JMP CalAlgBitFrmEndL*/
		// ======== HASC End =======//

		// ======== DRC Start =======//
	   /*CalDRCBitFrmL:
		Y0 = 8000
		Y0 = R0 - Y0
		JNZ CheckDRCSR10kL
		Y1 = 2185
		Y0 = 5000
		Y0 = R1 - Y0
		JNZ CheckDRCBR_6kL
		Y0 = 158
		JMP CheckDRC_SREndL
	   CheckDRCBR_6kL:
		Y0 = 6000
		Y0 = R1 - Y0
		JNZ CheckDRC_SREndL
		Y0 = 189
		JMP CheckDRC_SREndL
	   CheckDRCSR10kL:
		Y0 = 10000
		Y0 = R0 - Y0
		JNZ CheckDRC_SREndL
		Y1 = 2731
		Y0 = 6250
		Y0 = R1 - Y0
		JNZ CheckDRCBR_7p5kL
		Y0 = 158
		JMP CheckDRC_SREndL
	   CheckDRCBR_7p5kL:
		Y0 = 7500
		Y0 = R1 - Y0
		JNZ CheckDRC_SREndL
		Y0 = 189
		JMP CheckDRC_SREndL
	   CheckDRC_SREndL:
		JMP CalAlgBitFrmEndL*/
		// ======== DRC End   =======//

		// ======== LRC5 Start =======//
	  /* CalLRC5BitFrmL:
		Y0 = 8000
		Y0 = R0 - Y0
		JNZ CheckLRC5SR10kL
		Y0 = 1500
		Y0 = R1 - Y0
		JNZ CheckBR_1p72k_SR8k
		Y0 = 48
		Y1 = 2048
		JMP CheckLRC5_SREndL
	   CheckBR_1p72k_SR8k:
		Y0 = 1720
		Y0 = R1 - Y0
		JNZ CheckBR_2k_SR8k
		Y0 = 48
		Y1 = 2341
		JMP CheckLRC5_SREndL
	   CheckBR_2k_SR8k:
		Y0 = 2000
		Y0 = R1 - Y0
		JNZ CheckBR_2p4k_SR8k
		Y0 = 48
		Y1 = 2731
		JMP CheckLRC5_SREndL
	   CheckBR_2p4k_SR8k:
		Y0 = 2400
		Y0 = R1 - Y0
		JNZ CheckBR_3k_SR8k
		Y0 = 48
		Y1 = 3277
		JMP CheckLRC5_SREndL
	   CheckBR_3k_SR8k:
		Y0 = 3000
		Y0 = R1 - Y0
		JNZ CheckBR_4k_SR8k
		Y0 = 48
		Y1 = 4096
		JMP CheckLRC5_SREndL
	   CheckBR_4k_SR8k:
		Y0 = 4000
		Y0 = R1 - Y0
		JNZ CheckLRC5_SREndL
		Y0 = 48
		Y1 = 5461
		JMP CheckLRC5_SREndL
	   CheckLRC5SR10kL:
		Y0 = 10000
		Y0 = R0 - Y0
		JNZ CheckLRC5_SREndL
		Y0 = 1875
		Y0 = R1 - Y0
		JNZ CheckBR_2p15k_SR10k
		Y0 = 48
		Y1 = 2560
		JMP CheckLRC5_SREndL
	   CheckBR_2p15k_SR10k:
		Y0 = 2150
		Y0 = R1 - Y0
		JNZ CheckBR_2p5k_SR10k
		Y0 = 48
		Y1 = 2926
		JMP CheckLRC5_SREndL
	   CheckBR_2p5k_SR10k:
		Y0 = 2500
		Y0 = R1 - Y0
		JNZ CheckBR_3k_SR10k
		Y0 = 48
		Y1 = 3413
		JMP CheckLRC5_SREndL
	   CheckBR_3k_SR10k:
		Y0 = 3000
		Y0 = R1 - Y0
		JNZ CheckBR_3p75k_SR10k
		Y0 = 48
		Y1 = 4096
		JMP CheckLRC5_SREndL
	   CheckBR_3p75k_SR10k:
		Y0 = 3750
		Y0 = R1 - Y0
		JNZ CheckBR_5k_SR10k
		Y0 = 48
		Y1 = 5120
		JMP CheckLRC5_SREndL
	   CheckBR_5k_SR10k:
		Y0 = 5000
		Y0 = R1 - Y0
		JNZ CheckLRC5_SREndL
		Y0 = 48
		Y1 = 6827
	   CheckLRC5_SREndL:
		JMP CalAlgBitFrmEndL*/
		// ======== LRC5 End =======//


		// ======== Music96 Start =======//
	   CalMusic96BitFrmL:
		Y1 = 910
		Y0 = 4000
		Y0 = R1 - Y0
		JZ SetBitFrmMusic9640KbpsL
		Y0 = 4800
		Y0 = R1 - Y0
		JZ SetBitFrmMusic9648KbpsL
		Y0 = 5600
		Y0 = R1 - Y0
		JZ SetBitFrmMusic9656KbpsL
		Y0 = 6400
		Y0 = R1 - Y0
		JZ SetBitFrmMusic9664KbpsL
		Y0 = 8000
		Y0 = R1 - Y0
		JZ SetBitFrmMusic9680KbpsL
		Y0 = 9600
		Y0 = R1 - Y0
		JZ SetBitFrmMusic9696KbpsL
		JMP CalAlgBitFrmEndL

	   SetBitFrmMusic9640KbpsL:
		Y0 = 2880
		JMP CalAlgBitFrmEndL
	   SetBitFrmMusic9648KbpsL:
		Y0 = 3456
		JMP CalAlgBitFrmEndL
	   SetBitFrmMusic9656KbpsL:
		Y0 = 4032
		JMP CalAlgBitFrmEndL
	   SetBitFrmMusic9664KbpsL:
		Y0 = 4608
		JMP CalAlgBitFrmEndL
	   SetBitFrmMusic9680KbpsL:
		Y0 = 5760
		JMP CalAlgBitFrmEndL
	   SetBitFrmMusic9696KbpsL:
		Y0 = 6912
		// ======== Music96 End   =======//

	   CalAlgBitFrmEndL:
	}
}


void OrientationSetFunc(short OffsetWordAddr, short AlgType, short SampleRate, short BitRate, long OffsetTime, short SilenceDectFlag,short UpDownSel, short CurPosFrmAddr)
{

	__asm
	{
		X0=FP;
		R0=4;
		X0=X0-R0;
		Ix0=X0;
		X0 = RAM(Ix0,-1)
		Ix1 = X0
		X0 = RAM(Ix0,-1)
		R0 = RAM(Ix0,-1)
		R1 = RAM(Ix0,-1)


		PUSH Ix1
		CALLFF _CalAlgBitFrmFunc

		PUSH Y0

		R1 = RAM(Ix0,-1) // Offset Time
		R0 = RAM(Ix0,-1)
		Y0 = 0
		Y0 = R1 - Y0
		JZ @f
		nop
		nop
		@@:
		Y0 = 2500
		Y0 = R0 - Y0
		JZ @f
		nop
		nop
		@@:
		X0 = RAM(Ix0,-1) // Read Silence Detection
		X0 = X0 - 1
		JZ SilenceDectSkipLevel_Orietation
		// R0 LWord
		// R1 HWord


		Y0 = Y1

		PUSH R1
		//Y0 = UFTime
		R0 = SRL R0
		X0 = R0
		MR = X0*Y0(IS)
		R1 = MR1
		R1 = SL R1
		R0 = SL MR0
		JNAC NCF_OreHascL_NHasc1
		R1 = R1 + 1
   	   NCF_OreHascL_NHasc1:
   		X1 = R1
		POP R1
		X0 = R1
		MR = X0*Y0(IS)
		Y0 = 1
		MR = MR + X1*Y0(IS)
		R0 = MR0
		R1 = MR1

	   SilenceDectSkipLevel_Orietation:

		X0 = RAM(Ix0,-1)
		X1 = RAM(Ix0,-1)
		Ix1 = X1
		X1 = RAM(Ix1,1)		// Cur Pos L Word
		Y1 = RAM(Ix1,-1)	// Cur Pos H Word

		X0 = X0 - 1
		JZ PlayUpCalAbsPosL
		X0 = X1 - R0
		JAC @f
		Y1 = Y1 - 1
		@@:
		R1 = Y1 - R1
		JMP PlayUpDownCalAbsPosEndL
	   PlayUpCalAbsPosL:
		X0 = R0 + X1
		R1 = R1 + Y1 + C

	   PlayUpDownCalAbsPosEndL:

	   	R0 = BTST.15 R1
		JZ @f
		R1 = 0
		X0 = R1
		@@:
		RAM(Ix1,1) = X0
		RAM(Ix1) = R1

		POP Y0;

		X1 = R1;

        MR = X1*Y0(fs);

        X1 = MR0;
        Y1 = 0x4000;
        MR = X1*Y1(fs);
        MR = MR + X0*Y0(is);

		//R0 = MR0
		//R1 = MR1
		R0 = SRL.4 MR0
		R1 = SRA.4 MR1
		X0 = shv2
		R0 = X0 OR R0

		POP Ix1


		RAM(Ix1,1) = R0
		RAM(Ix1) = R1

	}

}
// ======== 定位系統  End ========//
#endif
