#include "main.h"


int main(void)
{
	sys_para cur_syspara,old_syspara;
	memset(&cur_syspara,0,sizeof(cur_syspara));
	memset(&old_syspara,0,sizeof(old_syspara)); //
	memset(Rec_Buff,0,sizeof(Rec_Buff)); //接收输出赋予初值
	IO_init();
	MasterUsart_Init(9600);//主机串口初始化
	//SlaverUsart_Init(115200);//从机串口初始化
	/***需要确认初始值来开机初始化同时修改 old_syspara 的值**/
	IRQ_ENABLE; //开启全局中断

	while(1)
	{
		if(Rec_Finish == True)  //接收完成
		{
			if(Rec_Buff[0] == 'A' && Rec_Buff[3] == 'F')
			{
				if(Rec_Buff[2] == '1')
				{
					if(Rec_Buff[1] == '3')
					{
						S1 = 1;
						PD1 = 1;					
						D1 = 0;			
					}
					else if(Rec_Buff[1] == '4')
					{
						S1 = 0;
						PD1 = 0;				
						D1 = 0;			
					}
					else
					{
					
					}
				}
				else if(Rec_Buff[2] == '2')
				{
					if(Rec_Buff[1] == '3')
					{
						S2 = 1;
						PD2 = 1;					
						D1 = 0;							
					}
					else if(Rec_Buff[1] == '4')
					{
						S2 = 0;
						PD2 = 0;					
						D1 = 0;						
					}
					else
					{
					
					}
				}
				else if(Rec_Buff[2] == '3')
				{
					if(Rec_Buff[1] == '3')
					{
						S3 = 1;
						PD3 = 1;					
						D1 = 0;						
					}
					else if(Rec_Buff[1] == '4')
					{
						S3 = 0;
						PD3 = 0;					
						D1 = 0;					
					}
					else
					{
					}	
				}
				else if(Rec_Buff[2] == '5')
				{
					if(Rec_Buff[1] == '3')
					{
						S5 = 1;
						PD1 = 1;					
						D1 = 1;						
					}
					else if(Rec_Buff[1] == '4')
					{
						S5 = 0;
						PD1 = 0;					
						D1 = 0;						
					}
					else
					{
					}			
				}
				else if(Rec_Buff[2] == '6')
				{
					if(Rec_Buff[1] == '3')
					{
						S6 = 1;
						PD2 = 1;					
						D2 = 1;					
					}
					else if(Rec_Buff[1] == '4')
					{
						S6 = 0;
						PD2 = 0;					
						D2 = 0;				
					}
					else
					{
					}		
				}
				else if(Rec_Buff[2] == '7')
				{
					if(Rec_Buff[1] == '3')
					{
						S7 = 1;					
					}
					else if(Rec_Buff[1] == '4')
					{
						S7 = 0;
					
					}
					else
					{
					}			
				}

			}
			memset(&cur_syspara,0,sizeof(cur_syspara));
			memset(Rec_Buff,0,sizeof(Rec_Buff)); 
			Rec_Finish = ~Rec_Finish;
		}
	}
}