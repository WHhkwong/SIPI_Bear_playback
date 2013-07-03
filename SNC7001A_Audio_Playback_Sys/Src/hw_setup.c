//******************************************************************
// SNC7001A Hardware Setup Code for SIPI
// 

//******************************************************************
#include <SFR.H>
#include "../../H/SNC7001A_Common_H/SNC7001A_Common_def.h"
#include "../../H/System/SNC7001A_System.h"
#include "../../H/Peripheral/SNC7001A_Serial_Flash.h"
#include "../../H/Peripheral/SNC7001A_SD_DAC.h"
#include "../../H/Peripheral/SNC7001A_SPI.h"
#include "hw_setup.h"

void hw_setup(void)
{
	SF_Enable();

	//====================================================
	//  Set T0 Interrupt = 1s
	//====================================================
	_setSR(SFR_T0, 0x0F00);
	_setSR(SFR_T0CNT, T0_COUNT_VALUE);	//1.0s
	Disable_T0_INT();

	//=====================================================
	// SPI Slave mode Initial
	//=====================================================
    SPI_HW_CS1_Setting(CS_Active_Low);
	SPI_Set_Interface_Mode(SPI_Mode0);	     // SPI Mode 0
	SPI_Set_Access_Mode(Read_Mode, SPI_1X);
	_setSR(SFR_SPITRANSFER, 16);
	_setSR(SFR_INTCR, 0x0400);
	SPI_Enable(SPI_Slave); 
#ifdef ENABLE_PIN_WAKEUP
	Disable_SPI_INT(); 
#else
	Enable_SPI_INT();
#endif

	_setSR(SFR_P0En, 0x400F);	//enable P00, P01, P02, P03, P14
	_setSR(SFR_P0M,  0x400C);	//P02 P03 P14 o/p, P01 & P00 i/p
	_setSR(SFR_P0PH, 0x0003);	//pull-up P01 & P00
	_setSR(SFR_P0, 	 0x4004);	//P02 P14 initial high; P03 initial lo

#ifdef ENABLE_PIN_WAKEUP
	_setSR(SFR_INTEC, _getSR(SFR_INTEC) | 0x0002);	// rising edge
	Clr_P01_Req();
	Enable_P01_INT();
#endif

	_setSR(SFR_INTEC, _getSR(SFR_INTEC) & 0xFFFE);	// falling edge
	Clr_P00_Req();
	Enable_P00_INT();

	_setSR(SFR_P1En, 0x0080);	//enable P17
	_setSR(SFR_P1M,  0x0080);	//P17 o/p
	_setSR(SFR_P1PH, 0x0000);	//P1 no pull-up
	_setSR(SFR_P1,   0x0080);	//P17 initial high

	DEBUG_PINS_ENABLE;
	DEBUG_PINS_DIR;
	DEBUG_PINS_PULLUP;

	//=====================================================
	// Wake up source selection with P0
	//===================================================== 
	P0_WakeUp_Setting(0x0003);	//P0.0 & P0.1 are wake up source
}