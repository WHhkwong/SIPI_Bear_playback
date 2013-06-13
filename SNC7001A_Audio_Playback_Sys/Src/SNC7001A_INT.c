
#define _INT_C

#include <SFR.h>
#include "../../H/SNC7001A_Common_H/SNC7001A_Common_def.h"
#include "../../H/System/SNC7001A_System.h"
#include "../../H/Peripheral/SNC7001A_SPI.h"

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

//=========================================
//
//=========================================
void __interrupt [0x10] Reserved_0x10(void)
{

}

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
}

//=========================================
//
//=========================================
void __interrupt [0x1C] P00_ISR(void)
{
	//_setSR(SFR_INTCR, SET_BIT6);
	Clr_P00_Req();
	_setSR(SFR_INTEC, _getSR(SFR_INTEC) ^ 0x0001);	// reverse edge
	if(_getSR(SFR_P0) & 0x0001)	// high
	{
//		_setSR(SFR_P3, _getSR(SFR_P3)^0x0010);

		g_uiFUNC_PROC = 0;

		g_uiFUNC_INI_SELECT = 1;

		g_uiFUNC_SELECT = 1;

		g_uiSPI_BUF_INDEX = 0;

		SPI_Enable(SPI_Slave); 
	}
	else	// lo
	{
//		_setSR(SFR_P3, _getSR(SFR_P3)^0x0010);

//		g_uiFUNC_PROC = 0;

		g_uiFUNC_INI_SELECT = 2;

		SPI_Disable(); 
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
				_setSR(SFR_P3, _getSR(SFR_P3)^0x0004);
			}
		}
		else if( g_uiSPI_BUF_INDEX < 2 * BUF_SIZE )
		{
			SongRam2[ g_uiSPI_BUF_INDEX - BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 2 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 2;
				_setSR(SFR_P3, _getSR(SFR_P3)^0x0004);
			}
		}
		else if( g_uiSPI_BUF_INDEX < 3 * BUF_SIZE )
		{
			SongRam3[ g_uiSPI_BUF_INDEX - 2 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 3 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 3;
				_setSR(SFR_P3, _getSR(SFR_P3)^0x0004);
			}
		}
		else if( g_uiSPI_BUF_INDEX < 4 * BUF_SIZE )
		{
			SongRam4[ g_uiSPI_BUF_INDEX - 3 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 4 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 4;
				_setSR(SFR_P3, _getSR(SFR_P3)^0x0004);
			}
		}
		else if( g_uiSPI_BUF_INDEX < 5 * BUF_SIZE )
		{
			SongRam5[ g_uiSPI_BUF_INDEX - 4 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 5 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 5;
				_setSR(SFR_P3, _getSR(SFR_P3)^0x0004);
			}
		}
		else if( g_uiSPI_BUF_INDEX < 6 * BUF_SIZE )
		{
			SongRam6[ g_uiSPI_BUF_INDEX - 5 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 6 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 6;
#ifndef AUDIO_BUF_1KW
				g_uiSPI_BUF_INDEX = 0;
#endif
				_setSR(SFR_P3, _getSR(SFR_P3)^0x0004);
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
				_setSR(SFR_P3, _getSR(SFR_P3)^0x0004);
			}
		}
		else if( g_uiSPI_BUF_INDEX < 8 * BUF_SIZE )
		{
			SongRam8[ g_uiSPI_BUF_INDEX - 7 * BUF_SIZE ] = g_uiSPI_RX_WORD;
			g_uiSPI_BUF_INDEX++;
			if( g_uiSPI_BUF_INDEX == 8 * BUF_SIZE)
			{
				g_uiFUNC_PROC = 8;
				_setSR(SFR_P3, _getSR(SFR_P3)^0x0004);
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
				_setSR(SFR_P3, _getSR(SFR_P3)^0x0004);
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
