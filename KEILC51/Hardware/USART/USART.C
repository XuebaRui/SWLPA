#include "usart.h"

/***********************************************************************************************
*函数名 ： void MasterUsart_Init(u16 bps)
*函数功能描述 ：初始化主机串口 
*函数参数 ： BPS-波特率
*函数返回值 ： void
*作者 ：WangR
*函数创建日期 ： 20190106
*函数修改日期 ： --
*修改人 ：--
*修改原因 ： --
*版本 ： 1.0
*历史版本 ： --
***********************************************************************************************/
void MasterUsart_Init(u16 bps)
{
	  ACC = P_SW1;
    ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
    P_SW1 = ACC;                //(P3.0/RxD, P3.1/TxD)
    
#if (PARITYBIT == NONE_PARITY)
    SCON = 0x50;                //8位可变波特率
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9位可变波特率,校验位初始为1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9位可变波特率,校验位初始为0
#endif

    AUXR = 0x40;                //定时器1为1T模式
    TMOD = 0x00;                //定时器1为模式0(16位自动重载)
    TL1 = (65536 - (FOSC/4/bps));   //设置波特率重装值
    TH1 = (65536 - (FOSC/4/bps))>>8;
    TR1 = 1;                    //定时器1开始启动
    ES = 1;                     //使能串口中断
    EA = 1;
}
/***********************************************************************************************
*函数名 ： void MasterUsart_SendByte(u8 byte)
*函数功能描述 ： 主机串口发送一个字节
*函数参数 ： byte--发送数据
*函数返回值 ： void
*作者 ：WangR
*函数创建日期 ： 20190106
*函数修改日期 ： --
*修改人 ：--
*修改原因 ： --
*版本 ： 1.0
*历史版本 ： --
***********************************************************************************************/
void MasterUsart_SendByte(u8 byte)
{
    while (usart1_busy);               //等待前面的数据发送完成
    ACC = byte;                  //获取校验位P (PSW.0)
    if (P)                      //根据P来设置校验位
    {
#if (PARITYBIT == ODD_PARITY)
				TB8 = 0;                //设置校验位为0
#elif (PARITYBIT == EVEN_PARITY)
				TB8 = 1;                //设置校验位为1
#endif
		}
		else
		{
#if (PARITYBIT == ODD_PARITY)
				TB8 = 1;                //设置校验位为1
#elif (PARITYBIT == EVEN_PARITY)
				TB8 = 0;                //设置校验位为0
#endif
		}
    usart1_busy = 1;
    SBUF = ACC;                 //写数据到UART数据寄存器
}
/***********************************************************************************************
*函数名 ： void SlaverUsart_Init(u16 bps)
*函数功能描述 ：初始化从机串口 
*函数参数 ： BPS-波特率
*函数返回值 ： void
*作者 ：WangR
*函数创建日期 ： 20190106
*函数修改日期 ： --
*修改人 ：--
*修改原因 ： --
*版本 ： 1.0
*历史版本 ： --
***********************************************************************************************/
void SlaverUsart_Init(u16 bps)
{

    P_SW2 &= ~S3_S0;            //S3_S0=0 (P0.0/RxD3, P0.1/TxD3)
//  P_SW2 |= S3_S0;             //S3_S0=1 (P5.0/RxD3_2, P5.1/TxD3_2)

#if (PARITYBIT == NONE_PARITY)
    S3CON = 0x10;               //8位可变波特率
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    S3CON = 0x9a;               //9位可变波特率,校验位初始为1
#elif (PARITYBIT == SPACE_PARITY)
    S3CON = 0x92;               //9位可变波特率,校验位初始为0
#endif

    T2L = (65536 - (FOSC/4/bps));   //设置波特率重装值
    T2H = (65536 - (FOSC/4/bps))>>8;
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
    IE2 = 0x08;                 //使能串口3中断
    EA = 1;

}
/***********************************************************************************************
*函数名 ： void SlaverUsart_SendByte(u8 byte)
*函数功能描述 ： 从机串口发送一个字节
*函数参数 ： byte--发送数据
*函数返回值 ： void
*作者 ：WangR
*函数创建日期 ： 20190106
*函数修改日期 ： --
*修改人 ：--
*修改原因 ： --
*版本 ： 1.0
*历史版本 ： --
***********************************************************************************************/
void SlaverUsart_SendByte(u8 byte)
{
	  while (usart3_busy);               //等待前面的数据发送完成
    ACC = byte;                  //获取校验位P (PSW.0)
    if (P)                      //根据P来设置校验位
    {
#if (PARITYBIT == ODD_PARITY)
        S3CON &= ~S3TB8;        //设置校验位为0
#elif (PARITYBIT == EVEN_PARITY)
        S3CON |= S3TB8;         //设置校验位为1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        S3CON |= S3TB8;         //设置校验位为1
#elif (PARITYBIT == EVEN_PARITY)
        S3CON &= ~S3TB8;        //设置校验位为0
#endif
    }
    usart3_busy = 1;
    S3BUF = ACC;                //写数据到UART3数据寄存器

}
