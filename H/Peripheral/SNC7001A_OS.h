#ifndef _SNC7001A_OS
#define _SNC7001A_OS

// User Define Task Number and Task Buffer Size
	#define  TOTAL_TASK_NUM  	1
	#define  TASK_BUFFER_SIZE	128


// Don't Modify
	unsigned int Task_SP[TOTAL_TASK_NUM + 1];
	unsigned int Task_Control[TOTAL_TASK_NUM + 1];
	unsigned int Task_Status[TOTAL_TASK_NUM + 1];
	unsigned int Task_Timer[TOTAL_TASK_NUM + 1];
	unsigned int Task_StackBuffer[TOTAL_TASK_NUM][TASK_BUFFER_SIZE];

	extern void OS_Initial(unsigned int, unsigned int);
	extern void OS_Start(void);
	extern void OS_Stop(void);
	extern void Set_Main_CPU_Time(unsigned int);
	extern unsigned int Assign_Task(unsigned int, void (*)(void) , unsigned int);
	extern unsigned int Close_Task(unsigned int);
	extern unsigned int Suspend_Task(unsigned int);
	extern unsigned int Resume_Task(unsigned int);
	extern unsigned int Restart_Task(unsigned int);
	extern void Terminate_Task(void);
	extern void Force_To_Leave_Task(void);
#endif