#ifndef _H_Robot
#define _H_Robot

void SetRobotLevelPara(short RobotLevel);
void  SetRobotRAMBank(short RamBk);
void  SetRobotInterVolume(short RobotInterVolT);
void  Robot_Out_Init_chL(short *OutBufLAddr);
short RobotTimeDomain_GenProcess(short Robot_Cmd);

#endif