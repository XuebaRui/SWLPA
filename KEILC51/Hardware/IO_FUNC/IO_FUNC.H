#ifndef _IO_FUNC_H_
#define _IO_FUNC_H_
/*******************Include***********************/
#include "STC15F2K60S2.H"
#include "intrins.h"
#include "typedef.h"
/*********************End*************************/
/********************Define***********************/
sbit PD1 = P2^0;
sbit PD2 = P2^1;
sbit PD3 = P2^2;
sbit D1 = P1^0;

sbit D2 = P1^1;
sbit S1 = P1^2;
sbit S2 = P1^3;
sbit S3 = P1^4;
sbit S5 = P1^5;
sbit S6 = P1^6;
sbit S7 = P1^7;
/*********************End*************************/
/********************Extern***********************/
/*********************End*************************/
void IO_init(void);
#endif
/**End**/