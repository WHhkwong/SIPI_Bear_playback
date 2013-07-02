
#define _INT_C

#include <SFR.h>
#include "../../H/SNC7001A_Common_H/SNC7001A_Common_def.h"
#include "../../H/System/SNC7001A_System.h"
#include "../../H/Peripheral/SNC7001A_SPI.h"
#include "hw_setup.h"

#ifdef AUDIO_BUF_1KW

#define BUF_SIZE	1016

extern int SongRam1[0x400];
extern int SongRam2[0x400];
extern int SongRam3[0x400];
extern int SongRam4[0x400];
extern int SongRam5[0x400];
extern int SongRam6[0x400];
extern int SongRam7[0x400];
extern int SongRam8[0x400];
extern int SongRam9[0x400];

#else

#define BUF_SIZE  1516

extern int SongRam1[0x600];
extern int SongRam2[0x600];
extern int SongRam3[0x600];
extern int SongRam4[0x600];
extern int SongRam5[0x600];
extern int SongRam6[0x600];

#endif


u16 g_uiSPI_RX_F;
u16 g_uiSPI_RX_0;
u16 g_uiSPI_RX_1;
u16 g_uiSPI_RX_WORD;
u16 g_uiSPI_BUF_INDEX;
u16 g_uiFUNC_SELECT;
u16 g_uiFUNC_INI_SELECT;
u16 g_uiFUNC_PROC;
u16 g_uiFUNC_PLAY;
u16 g_uiKEY_CNT;

//=========================================
//
//=========================================
void __interrupt [0x14] AD_ISR(void)
{
	//_setSR(SFR_INTCR, SET_BIT8);
	Clr_SD_ADC_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x18] T0_ISR(void)
{
	//_setSR(SFR_INTCR, SET_BIT7);
	Clr_T0_Req();

	g_uiKEY_CNT++;
	DEBUG_PIN2_TOGGLE;

	if(g_uiKEY_CNT == 3)
	{
		Disable_SPI_INT();
		Disable_P00_INT();
		Disable_P01_INT();

		CC2540_RESET_PIN_LO;

		WDT_0P25_Sec();

		while(1)
		{};			// wait for watchdog reset
	}
}

//=========================================
//
//=========================================
void __interrupt [0x1C] P00_ISR(void)
{
	//_setSR(SFR_INTCR, SET_BIT6);
	Clr_P00_Req();

	if(!KEY_PIN_EDGE_IS_HI && !KEY_PIN_IS_HI)	// lo
	{
		KEY_PIN_EDGE_TOGGLE;

		_setSR(SFR_T0CNT, T0_COUNT_VALUE);
		T0_ENABLE;
		Enable_T0_INT();

		g_uiKEY_CNT = 0;
		if(!g_uiFUNC_SELECT)
		{
			g_uiFUNC_SELECT = 1;
			g_uiFUNC_INI_SELECT = 3;
		}
	}
	else if(KEY_PIN_EDGE_IS_HI && KEY_PIN_IS_HI)	// hi
	{
		KEY_PIN_EDGE_TOGGLE;

		if(g_uiKEY_CNT <= 2)
		{
			if(g_uiFUNC_INI_SELECT == 3)
			{
				g_uiFUNC_SELECT = 0;
				g_uiFUNC_INI_SELECT = 0;
			}
		}

		Disable_T0_INT();
		T0_DISABLE;
	}
}

//=========================================
//
//=========================================
void __interrupt [0x20] T1_ISR(void)
{
	//_setSR(SFR_INTCR, SET_BIT5);
	Clr_T1_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x24] P01_ISR(void)
{
	//_setSR(SFR_INTCR, SET_BIT4);
	Clr_P01_Req();

	if(WAKEUP_PIN_EDGE_IS_HI && WAKEUP_PIN_IS_HI)	// high
	{
		WAKEUP_PIN_EDGE_TOGGLE;	// reverse edge

//		DEBUG_PIN2_TOGGLE;

		g_uiFUNC_PROC = 0;

		g_uiFUNC_INI_SELECT = 1;

		g_uiFUNC_SELECT = 1;

		g_uiSPI_BUF_INDEX = 0;

		Clr_SPI_Req();

		Enable_SPI_INT();

	}
	else if(!WAKEUP_PIN_EDGE_IS_HI && !WAKEUP_PIN_IS_HI) // lo
	{
		WAKEUP_PIN_EDGE_TOGGLE;	// reverse edge

//		DEBUG_PIN2_TOGGLE;

//		g_uiFUNC_PROC = 0;

		g_uiFUNC_INI_SELECT = 2;

		Disable_SPI_INT();

	}
}

//=========================================
//
//=========================================
void __interrupt [0x28] T2_ISR(void)
{
	Clr_T2_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x2C] P02_ISR(void)
{
	//_setSR(SFR_INTCR, SET_BIT2);
	Clr_P02_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x30] Reserved_0x30(void)
{

}

//=========================================
//
//=========================================
/*void __interrupt [0x34] DA_ISR(void)
{
	_setSR(SFR_INTCR, SET_BIT0);
}*/

//=========================================
//	
//=========================================
void __interrupt [0x38] SPI_ISR(void)
{ 
  
   // _setSR(SFR_INTCR, SET_BIT10); //Clr SPI Interrupt Flag

	Clr_SPI_Req();

	g_uiSPI_RX_0 = _getSR(SFR_SPIDADA1);	// swap for hi-byte lo-byte issue

	g_uiSPI_RX_1 = _getSR(SFR_SPIDADA0);

	if(g_uiFUNC_SELECT == 0x0001)
	{
		g_uiSPI_RX_WORD = (g_uiSPI_RX_1 << 8) + g_uiSPI_RX_0;

		if( g_uiSPI_BUF_INDEX < BUF_SIZE )
		{
			SongRam1[ g_uiSPI_BUF_INDEX++ ] = g_uiSPI_RX_WORD;
			if( g_uiSPI_BUF_INDEX == BUF_SIZE)
			{
				g_uiFUNC_PROC = 1;
				if(g_uiFUNC_PLAY == 2)
				{
					BUFFER_CTRL_PIN_LO;
				}
				DEBUG_PIN1_TOGGLE;
			}
		}
		else if( g_uiSPI_BUF_INDEX < 2 * BUF_SIZE )
		{
			SongRam2[ g_uiSPI_BUF_INDEX - BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 2 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 2;
				if(g_uiFUNC_PLAY == 3)
				{
					BUFFER_CTRL_PIN_LO;
				}
				DEBUG_PIN1_TOGGLE;
			}
		}
		else if( g_uiSPI_BUF_INDEX < 3 * BUF_SIZE )
		{
			SongRam3[ g_uiSPI_BUF_INDEX - 2 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 3 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 3;
				if(g_uiFUNC_PLAY == 4)
				{
					BUFFER_CTRL_PIN_LO;
				}
				DEBUG_PIN1_TOGGLE;
			}
		}
		else if( g_uiSPI_BUF_INDEX < 4 * BUF_SIZE )
		{
			SongRam4[ g_uiSPI_BUF_INDEX - 3 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 4 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 4;
				if(g_uiFUNC_PLAY == 5)
				{
					BUFFER_CTRL_PIN_LO;
				}
				DEBUG_PIN1_TOGGLE;
			}
		}
		else if( g_uiSPI_BUF_INDEX < 5 * BUF_SIZE )
		{
			SongRam5[ g_uiSPI_BUF_INDEX - 4 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 5 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 5;
				if(g_uiFUNC_PLAY == 6)
				{
					BUFFER_CTRL_PIN_LO;
				}
				DEBUG_PIN1_TOGGLE;
			}
		}
		else if( g_uiSPI_BUF_INDEX < 6 * BUF_SIZE )
		{
			SongRam6[ g_uiSPI_BUF_INDEX - 5 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 6 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 6;
				if(g_uiFUNC_PLAY == 1)
				{
					BUFFER_CTRL_PIN_LO;
				}
#ifndef AUDIO_BUF_1KW
				g_uiSPI_BUF_INDEX = 0;
#endif
				DEBUG_PIN1_TOGGLE;
			}
		}
#ifdef AUDIO_BUF_1KW
		else if( g_uiSPI_BUF_INDEX < 7 * BUF_SIZE )
		{
			SongRam7[ g_uiSPI_BUF_INDEX - 6 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 7 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 7;
				DEBUG_PIN1_TOGGLE;
			}
		}
		else if( g_uiSPI_BUF_INDEX < 8 * BUF_SIZE )
		{
			SongRam8[ g_uiSPI_BUF_INDEX - 7 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 8 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 8;
				DEBUG_PIN1_TOGGLE;
			}
		}
		else if( g_uiSPI_BUF_INDEX < 9 * BUF_SIZE )
		{
			SongRam9[ g_uiSPI_BUF_INDEX - 8 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 9 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 9;
				g_uiSPI_BUF_INDEX = 0;
				DEBUG_PIN1_TOGGLE;
			}
		}
#endif
	}
	else
	{
    	g_uiSPI_RX_F = 1;
	}

	_IObitSET(SFR_SPICTRL,0);

}

//=========================================
//
//=========================================
void __interrupt [0x3C] MSP_ISR(void)
{
	//_setSR(SFR_INTCR, SET_BIT11);
	Clr_MSP_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x40] I2S_ISR(void)
{
	//_setSR(SFR_INTCR, SET_BIT12);
	Clr_I2S_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x44] Reserved_0x44(void)
{

}

//=========================================
//
//=========================================
void __interrupt [0x48] Reserved_0x48(void)
{

}

//=========================================
//
//=========================================
void __interrupt [0x4C] Reserved_0x4C(void)
{

}

//=========================================
//
//=========================================
void __interrupt [0x50] USB_ISR(void)
{
	//_setSR(SFR_INTCR2, SET_BIT14);
	Clr_USB_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x54] CIS_HREF_ISR(void)
{
	//_setSR(SFR_INTCR2, SET_BIT13);
	Clr_CIS_HREF_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x58] RTC_ISR(void)
{
	//_setSR(SFR_INTCR2, SET_BIT12);
	Clr_RTC_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x5C] NF_ISR(void)
{
	//_setSR(SFR_INTCR2, SET_BIT11);
	Clr_NF_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x60] DMA_CIS_W_ISR(void)
{
	//_setSR(SFR_INTCR2, SET_BIT10);
	Clr_DMA_CIS_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x64] DMA_NF_RW_ISR(void)
{
	//_setSR(SFR_INTCR2, SET_BIT9);
	Clr_DMA_NF_Req();
}

//=========================================
//
//=========================================
void __interrupt [0x68] SAR_AD_ISR(void)
{
	//_setSR(SFR_INTCR2, SET_BIT8);
	Clr_SAR_ADC_Req();

}
//=========================================
//
//=========================================
void __interrupt [0x6C] Reserved_0x6C(void)
{

}

//=========================================
//
//=========================================
void __interrupt [0x70] Reserved_0x70(void)
{

}

//=========================================
//
//=========================================
void __interrupt [0x74] Reserved_0x74(void)
{

}

//=========================================
//
//=========================================
void __interrupt [0x78] DMA_DEV_RW_ISR(void)
{
	//_setSR(SFR_INTCR2, SET_BIT4);
	Clr_DMA_USB_Req();
}
