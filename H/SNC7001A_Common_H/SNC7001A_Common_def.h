#ifndef _SNC7001A_COMMON_DEF
#define _SNC7001A_COMMON_DEF

#include "SNC7001A_MMIO_Register.h"

// Bit define
#define BIT0 		    0x0001U
#define BIT1   	  	    0x0002U
#define BIT2   	  	    0x0004U
#define BIT3  	 	    0x0008U
#define BIT4  	 	    0x0010U
#define BIT5  	 	    0x0020U
#define BIT6  	 	    0x0040U
#define BIT7  	 	    0x0080U
#define BIT8  	 	    0x0100U
#define BIT9  	 	    0x0200U
#define BIT10 	 	    0x0400U
#define BIT11 	 	    0x0800U
#define BIT12 	 	    0x1000U
#define BIT13 	 	    0x2000U
#define BIT14 	 	    0x4000U
#define BIT15 	 	    0x8000U

#define SET_BIT0 	    0x0001U
#define SET_BIT1   	    0x0002U
#define SET_BIT2   	    0x0004U
#define SET_BIT3  	    0x0008U
#define SET_BIT4  	    0x0010U
#define SET_BIT5  	    0x0020U
#define SET_BIT6  	    0x0040U
#define SET_BIT7  	    0x0080U
#define SET_BIT8  	    0x0100U
#define SET_BIT9  	    0x0200U
#define SET_BIT10 	    0x0400U
#define SET_BIT11 	    0x0800U
#define SET_BIT12 	    0x1000U
#define SET_BIT13 	    0x2000U
#define SET_BIT14 	    0x4000U
#define SET_BIT15 	    0x8000U

//========== Unit Type Define =======================================
typedef unsigned int    INT16U;          // Unsigned 16 bit quantity
typedef signed   int    INT16S;          // Signed   16 bit quantity
typedef unsigned long   INT32U;          // Unsigned 32 bit quantity
typedef signed   long   INT32S;          // Signed   32 bit quantity
typedef float           FP32;            // Single precision floating point
typedef double          FP64;            // Double precision floating point
typedef unsigned char   uchar;
typedef unsigned short  ushort;

#define v1 volatile

typedef v1 INT16S		vINT16S;
typedef v1 INT16U		vINT16U;
typedef v1 INT32S		vINT32S;
typedef v1 INT32U		vINT32U;

#define u16 INT16U
#define s16 INT16S
#define u32 INT32U
#define s32 INT32S

#define vu16 vINT16U
#define vs16 vINT16S
#define vu32 vINT32U
#define vs32 vINT32S

union DWORD_TYPE
{
	unsigned long DWord;
	unsigned int  HLWord[2];
};

//==========================================================
#define TRUE			0
#define FALSE			1

#define SUCCESS			0
#define FAILURE			1

#define CS1				1
#define CS2				2
#define NONE			0
#define SERIAL_FLASH  	1
#define SERIALFLASH  	1
#define NOR_FLASH		2
#define NORFLASH		2
#define SRAM			3
#define MASKROM			4
#define MASK_ROM		4
#define MCU8080      	5
#define MCU_8080      	5

//----------------------------------------------------------------------------------
//                                   Play Process Define Section
//----------------------------------------------------------------------------------
//========== Algorithm Header Type Define =======
#define	AUDIO32	  		0x5541
#define	SNX8K 	  		0x3947
#define	MLD		   		0x454D
#define IMAADPCM        0x4D49
#define MUSIC96         0x554D



//========== Algorithm Command Type Define =======
#define NormalCmd		0x0000
#define	ResetCmd		0x0001
#define	MuteCmd			0x0002
#define	PauseCmd		0x0004
#define	StopCmd			0x0008
#define	NplayStopCmd	0x0018

//----------------------------------------------------------------------------------
//                                   DATA TYPES
//----------------------------------------------------------------------------------
#define NONE		    0
#define MODE1 		    1
#define MODE2 		    2
#define MODE3 		    3
#define MODE4 		    4

#define SDCARD		    1
#define NAND		    2
#define NOR_FLASH1	    3
//#define SERIAL_FLASH  4

#define unionLONGWORD  		    union  {  u32 LW;  u16 WD[2];}

//================== SPI Communication IF ===============
#define SPI_Master      0
#define SPI_Slave       1
#define CS_Active_Low   0
#define CS_Active_High  1

#define Write_Mode      0
#define Read_Mode       1

#define SPI_1X          1
#define SPI_2X          2
#define SPI_4X          4

#define SPI_Mode0       0
#define SPI_Mode1       1
#define SPI_Mode2       2
#define SPI_Mode3       3


//===================== SD-ADC/SD-DAC/I2S IF ======================
#define	SR_32K			0
#define	SR_16K			1
#define	SR_8K			2
#define	SR_4K			3
#define	SR_44_1K		4
#define	SR_22_05K		5
#define	SR_11_025K		6
#define	SR_5_5125K		7
#define	SR_48K			8
#define	SR_24K			9
#define	SR_12K			10
#define	SR_6K			11

#define FIFO_FULL		0
#define FIFO_HALF		1
#define FIFO_EMPTY		2

#define MUTE_OFF        0
#define MUTE_ON         1

//===================== I2S IF ======================
#define I2S_RECEIVER    0
#define I2S_TRANSMITTER 1

#define I2S_MONO        0
#define I2S_STEREO      1

#define I2S_STD         0
#define I2S_LJ          1
#define I2S_RJ          2

#define I2S_8BIT        0
#define I2S_16BIT       1

//============= Serial Flash Controller =============
#define SF_BR_48M       0
#define SF_BR_24M       1
#define SF_BR_12M       2
#define SF_BR_6M        3

//===================== MSP IF ======================
#define MSP_ACK	        0
#define MSP_NACK	    1

//===================== CIS IF ======================
#define SCALING			1
#define WINDOW_SETTING 	2

#define HREF_POSEDGE    0x00
#define HREF_NEGEDGE	0x20
#define VSYN_POSEDGE	0x00
#define VSYN_NEGEDGE	0x10
#define PIXEL_POSEDGE	0x00
#define PIXEL_NEGEDGE	0x08
#define PIXEL_WORD		0x00
#define PIXEL_BYTE      0x04
#define CIS_12MHZ		0x02

//===================== UART IF ====================
#define UART_BR_1200    0x0277
#define UART_BR_2400    0x0276
#define UART_BR_4800    0x0275
#define UART_BR_9600    0x0274
#define UART_BR_19200   0x0273
#define UART_BR_38400   0x0272
#define UART_BR_51200   0x03A9
#define UART_BR_57600   0x0341
#define UART_BR_102400  0x01D9
#define UART_BR_115200  0x01A1

#define UART_8BIT_MODE          0x00
#define UART_16BIT_MODE         0x01

#define UART_PARITY_EVEN        0x00
#define UART_PARITY_ODD         0x01

#define UART_PARITY_ERROR       0x00
#define UART_PARITY_OK          0x01

//===================== SAR ADC IF ====================
#define	AIN0 		    0x01
#define	AIN1 		    0x02
#define	AIN2 		    0x03
#define	AIN3		    0x04
#define	AIN0_DI		    0x11
#define	AIN1_DI 	    0x12
#define	AIN2_DI 	    0x13
#define	AIN3_DI		    0x14

//===================== SD Card IF ====================
#define	SD_4BIT_MODE    0x01
#define	SD_SPI_MODE     0X04

#define NO_ERROR		0x00
#define RW_TO_ERR		0x01
#define CRC_ERR			0x02
#define WRITE_ERR		0x03
#define RETRY_TO_ERR    0x04
#define CMD_TO_ERR		0x05

#define CMD7_ERR		0x06
#define ACMD6_ERR		0x07
#define ACMD41_ERR		0x08
#define CMD6_ERR		0x09
#define CMD55_ERR       0x0A
#define CMD58_ERR       0x0B
#define NO_SUPPLY_CARD  0x0C

#define RES_NONE		0
#define RES_R1			1
#define RES_R2			2
#define RES_R3			3
#define RES_R4			4
#define RES_R5			5
#define RES_R6			6
#define RES_R7			7
#define RES_R1B			8

#define SD_CARD			1
#define MMC_CARD		2

#define	V1X_SDSC		1
#define	V20_SDSC		2
#define	V20_SDHC		3

#define	HEAD			1
#define	MIDDLE			2
#define	TAIL			3

#endif