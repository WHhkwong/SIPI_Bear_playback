
//******************************************************************
// SNC7001A Audio Playback Sample Code SysMain
// 

//******************************************************************
#include <SFR.H>
#include "../../H/SNC7001A_Common_H/SNC7001A_Common_def.h"
#include "../../H/System/SNC7001A_System.h"
#include "../../SNC7001A_Audio_Playback_Sys/Include/SNC7001A_Audio_Playback_Usage.h"
#include "../../SNC7001A_Audio_Playback_Sys/Include/SNC7001A_Algorithm_Define.h"
#include "hw_setup.h"

extern void MainRoutine(void);

void sys_main(void)
{
	WDT_2_Sec(); //Set WDT 2 sec 

    Reset_WDT();

	hw_setup();

	AudioPlay_Enable(); //Audio Algorithm Initial

	Gie();

    //===================USB Power Down Start=============
    //USB_PowerDown();
	//===================USB Power Down End=============
   
    MainRoutine();

//	SD_DAC_Turn_Off();
}

