#ifndef _MAIN_H_
#define _MAIN_H_
/*******************Include***********************/
#include "STC15F2K60S2.H"
#include "usart.h"
#include "string.h"
#include "IO_FUNC.h"
/*********************End*************************/
/********************Define***********************/
#define IRQ_ENABLE    EA = 1
#define IRQ_DISABLE   EA = 0
#define True  1
#define False 0
typedef struct 
{
	u8 ST;
	u8  sss;
	u8 PSA;
	u8  CS; 
	u8  AA;
	u16 FS;
	u8  PD;
}sys_para;
/*********************End*************************/
/********************Extern***********************/
u8 Rec_Buff[8];
u8 Rec_Len = 0;
u8 Rec_Finish = True;


/*********************End*************************/
#endif