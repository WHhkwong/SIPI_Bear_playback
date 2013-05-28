#ifndef __USB_H__
#define __USB_H__

//----------------------------------------------------------------------------------
//                                   CONSTANT DEFINE
//----------------------------------------------------------------------------------
#define HID_OTHERS		0
#define HID_KEYBOARD 	1
#define HID_MOUSE		2
#define HID_BOOTEN		1
#define HID_NONE		0
#define HID_STALL		1
#define HID_PASS		0


//CONSTANT DEFINE
#define USB_INT_VEC			0x000050
#define HID_OUTBUF_STR		0x300

#define	PID 0x6831
#define	HID_PROTOCOL 		HID_OTHERS //HID_KEYBOARD //HID_MOUSE
#define	HID_BOOT_INTERFACE	HID_NONE   //HID_BOOTEN
#define	HID_REPORT_SIZE	    0x21

#define	HID_POLLING_INTERVAL	0x0A  //10ms


//HID DATA PORT DEFINE by word
#define HID_INBUF		((u16 *)0xE210U)


//Extern Variable

extern u16 g_uiPID;
extern u16 g_uiHID_ReportSize;
extern u16 g_uiHID_IntTime;
extern u16 g_uiHID_InterProtocol;
extern u16 g_uiHID_InterSubclass;


//Extern Function
//extern u16 USB_SetPID(void);
extern void USB_DeviceInit(void);

extern void USB_Service(void);
extern void USB_PowerDown(void);
extern void USB_Init(void);
extern void USB_ISR_Function(void);
//extern void HID_Request(void);
/*
extern u16 USB_Set_Report(void);
extern u16 USB_Get_Report(void);
extern u16 USB_Get_Protocol(void);
extern u16 USB_Set_Idle(void);
extern u16 USB_Set_Protocol(void);
*/
extern void USB_HIDClrPktRdy(void);
extern void USB_HIDInPktRdy(void);

#endif