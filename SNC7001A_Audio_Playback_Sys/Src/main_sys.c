
//******************************************************************
// SNC7001A Audio Playback Sample Code SysMain
// 

//******************************************************************
#include <SFR.H>
#include "../../H/SNC7001A_Common_H/SNC7001A_Common_def.h"
#include "../../H/System/SNC7001A_System.h"
#include "../../H/Peripheral/SNC7001A_Serial_Flash.h"
#include "../../H/Peripheral/SNC7001A_SD_DAC.h"
#include "../../H/Peripheral/SNC7001A_SPI.h"
#include "../../SNC7001A_Audio_Playback_Sys/Include/SNC7001A_Audio_Playback_Usage.h"
#include "../../SNC7001A_Audio_Playback_Sys/Include/SNC7001A_Algorithm_Define.h"

extern void MainRoutine(void);

void sys_main(void)
{
	WDT_2_Sec(); //Set WDT 2 sec 

    Reset_WDT();

	SF_Enable();
	//=====================================================
	// SPI Slave mode Initial
	//=====================================================
    SPI_HW_CS1_Setting(CS_Active_Low);
	SPI_Set_Interface_Mode(SPI_Mode0);	     // SPI Mode 0
	SPI_Set_Access_Mode(Read_Mode, SPI_1X);
	_setSR(SFR_SPITRANSFER, 16);
	_setSR(SFR_INTCR, 0x0400);
#ifdef ENABLE_PIN_WAKEUP
	SPI_Disable(); 
#else
	SPI_Enable(SPI_Slave); 
#endif
	Enable_SPI_INT();

	_setSR(SFR_P0En, 0x0001);
	_setSR(SFR_P0M,  0x0000);
	_setSR(SFR_P0PH, 0x0007);
#ifdef ENABLE_PIN_WAKEUP
	_setSR(SFR_INTEC, 0x0001);	// rising edge
	Enable_P00_INT();
#endif

	_setSR(SFR_P3En, 0x0015);
	_setSR(SFR_P3M,  0x0015);
	_setSR(SFR_P3PH, 0x0000);

	//=====================================================
	// Wake up source selection with P0
	//===================================================== 
	P0_WakeUp_Setting(0x0001);	//P0.0 is wake up source

	AudioPlay_Enable(); //Audio Algorithm Initial

	Gie();

    //===================USB Power Down Start=============
    //USB_PowerDown();
	//===================USB Power Down End=============
   
    MainRoutine();

	SD_DAC_Turn_Off();


}

