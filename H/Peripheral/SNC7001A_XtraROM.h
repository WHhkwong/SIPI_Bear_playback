#ifndef _SNC7001A_XtraROM
#define _SNC7001A_XtraROM
struct XtraROMTYPE {
	u16 ID[5];
	u16 PageSz;			// Physical page size
	u16 PageBit;
  u16 MaxPages;		// Max physical pages per block
	u16 TolPhyBlocks;  	// Total Physical Blocks of nf
	u16 BlockBit;		// BlockBit	=18 if 2^18=256k bytes/block 	
	u16 MLC;            // 1: MLC,						
};


#define XtraROM_MS_REG_WR()            ( (*(vu16 *)0xF007U) &= 0xFFDFU ) // 0 : Use command to write data to SD/Nf.	
#define XtraROM_MS_REG_RD()            ( (*(vu16 *)0xF007U) |= 0x0020U ) // 1 : Use command to read data from SD/NF. 

#define NF_MS_CMD_REG		   (*(vu16 *)0xF01CU)
#define NF_MS_ADDR_REG		   (*(vu16 *)0xF01DU)
#define NF_MS_DATA_REG		   (*(vu16 *)0xF01EU)

#define PG_WR_SEQ_W(arg0)      ( (*(vu16 *)0xF009U) = (*(vu16 *)0xF009U)&0xFFF0U | arg0 )
#define USER_DEF_W(arg0)       ( (*(vu16 *)0xF009U) = (*(vu16 *)0xF009U) | (arg0<<8) )
#define LBA_W(arg0)            ( (*(vu16 *)0xF00aU) = arg0 )


#define PG_WR_SEQ()            ( (*(vu16 *)0xF017U) & 0x000FU ) 
#define PAGE_EMPTY()           ( (*(vu16 *)0xF017U) & SET_BIT4 ) // 0: Page Written; 1: Not written
#define USER_DEF()             ( ((*(vu16 *)0xF017U) & 0x1F00U)>>8 )
#define LBA()                  ((*(vu16 *)0xF018U) )
extern u16  XtraROM_Enable(void);
extern void XtraROM_Disable(void);
extern void XtraROM_Init(u16 PageSize ,u16 BlockSize ,u16 NfAddrCycle ,u16 NfRdWidth,u16 NfWrWidth);
extern u16  XtraROM_Rst(void);
extern u16  XtraROM_ReadPhyPage(u32 PhyAddr, u16 DataSize, u16 *pWRAM);
extern u16  XtraROM_ReadID_MsReg(u16 *PTR);

#endif