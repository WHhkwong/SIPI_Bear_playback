#ifndef __USB_H__
#define __USB_H__

#define USBMODE 	  MODE1

#define USB_DISK_LUN0   SDCARD  		//NAND
#define USB_DISK_LUN1   NONE
#define USB_CDROM_LUN0  NONE
#define USB_CDROM_LUN1  NONE

/*
#define USBMODE 	  MODE2

#define USB_DISK_LUN0   SDCARD 		//NAND
#define USB_DISK_LUN1   NAND   		//SDCARD
#define USB_CDROM_LUN0  NONE
#define USB_CDROM_LUN1  NONE
*/
/*
#define USBMODE 	  MODE3

#define USB_DISK_LUN0   SDCARD 		//NAND
#define USB_DISK_LUN1   NONE
#define USB_CDROM_LUN0  NONE
#define USB_CDROM_LUN1  NOR_FLASH1    //SERIAL_FLASH
*/
/*
#define USBMODE 	  MODE4

#define USB_DISK_LUN0   NONE
#define USB_DISK_LUN1   NONE
#define USB_CDROM_LUN0  NOR_FLASH1   //NORFLASH
#define USB_CDROM_LUN1  NONE
*/

//Extern Variable

extern u16 g_uiUsbConfigMode;
extern u16 g_uiUsbDiskLun0;
extern u16 g_uiUsbDiskLun1;
extern u16 g_uiUsbCdromLun0;
extern u16 g_uiUsbCdromLun1;
extern u16 g_uiPID;
extern u16 g_uiBytePerSecLun0;
extern u16 g_uiBytePerSecLun1;
extern u16 g_uiBulkStrAddr;
extern u16 g_USBBusStatus;

//Extern Function
//extern u16 USB_SetPID(void);
extern void USB_DeviceInit(void);
extern u32  USB_SetCapacity(u16 LUNNum);

extern u16  USB_BulkInLUN0(u32 BULKIN_ADDR,u32 BULKIN_LBA, u32 DataResidue,u32 TotalLen);
extern u16  USB_BulkInLUN1(u32 BULKIN_ADDR,u32 BULKIN_LBA, u32 DataResidue,u32 TotalLen);
extern u16  USB_BulkOutLUN0(u32 BULKIN_ADDR,u32 BULKIN_LBA, u32 DataResidue,u32 TotalLen);
extern u16  USB_BulkOutLUN1(u32 BULKIN_ADDR,u32 BULKIN_LBA, u32 DataResidue,u32 TotalLen);

extern void USB_Service(void);
extern void USB_PowerDown(void);
extern void USB_Init(void);
extern void USB_ISR_Function(void);
extern u16 	Packet_Xfer(u16 Dir ,u16 *WRAM ,u16 DataSize);


#endif