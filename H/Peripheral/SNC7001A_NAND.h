#ifndef _SNC7001A_NAND
#define _SNC7001A_NAND

extern u16  NF_Enable(void);
extern void NF_Disable(void);
extern void NF_NfFlash_Init(u16 PageSize ,u16 BlockSize ,u16 NfAddrCycle ,u16 NfRdWidth,u16 NfWrWidth);
extern void NF_ECC_function(void);
extern u16  NF_Rst(void);
extern u16  NF_ErasePhyOneBlock(u32 PhyAddr);
extern u16  NF_WritePhyPage(u32 PhyAddr, u16 DataSize, u16 *pWRAM, u16 ecc_en);
extern u16  NF_ReadPhyPage(u32 PhyAddr, u16 DataSize, u16 *pWRAM, u16 ecc_en);
extern u16  NF_ReadPhyPageInfo(u32 PhyAddr);
extern u16  NF_ReadID_MsReg(u16 *PTR);
extern u16  NF_Wait_MS_RDY(void);
extern u16  NF_EraseMultiPlaneBlock(u32 PhyAddr);
extern u16  NF_WriteMultiPlanePage(u32 PhyAddr1,u32 PhyAddr2, u16 DataSize, u16 *pWRAM1,u16 *pWRAM2, u16 ecc_en);

#endif