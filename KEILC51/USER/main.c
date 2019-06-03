#include "main.h"

int main(void)
{
	sys_para cur_syspara,old_syspara;
	memset(&cur_syspara,0,sizeof(cur_syspara));
	memset(&old_syspara,0,sizeof(old_syspara)); //
	memset(Rec_Buff,0,sizeof(Rec_Buff)); //接收输出赋予初值
	IO_init();
	MasterUsart_Init(115200);//主机串口初始化
	SlaverUsart_Init(115200);//从机串口初始化
	/***需要确认初始值来开机初始化同时修改 old_syspara 的值**/
	IRQ_ENABLE; //开启全局中断
	PDD = 0;
	PDC = 0;	
	PDB = 0;	
	PDA = 0;	
	while(1)
	{
		if(Rec_Finish == True)  //接收完成
		{
			if(Rec_Buff[0] == 0xa5 && Rec_Buff[1] == 0xa5
					&& Rec_Buff[6] == 0x5a && Rec_Buff[7] == 0x5a) //检测报头报尾
			{//解析
				cur_syspara.ST  =  Rec_Buff[3] >> 7;
				cur_syspara.sss = (Rec_Buff[3] >> 5) & 0x03;
				cur_syspara.PSA = (Rec_Buff[3] >> 4) & 0x01;
				cur_syspara.CS = Rec_Buff[3] & 0x03; 
				cur_syspara.AA = Rec_Buff[4] & 0x07;
				cur_syspara.FS = (Rec_Buff[4] & 0x0f) << 8 | Rec_Buff[5];
				cur_syspara.PD = Rec_Buff[5] & 0x0f;
			}
			//根据解析值设置
			if(cur_syspara.ST != old_syspara.ST)
			{
				ST = (cur_syspara.ST > 0) ? 1 : 0;
				STY = ~ST;
				old_syspara.ST = cur_syspara.ST;
			}
			if(cur_syspara.sss != old_syspara.sss)
			{
				SSS0 = ((cur_syspara.sss & 0x01) > 0) ? 1 : 0;
				SSS1 = ((cur_syspara.sss & 0x02) > 0) ? 1 : 0;
				old_syspara.sss = cur_syspara.sss;
			}
			if(cur_syspara.PSA != old_syspara.PSA)
			{
				PSA = (cur_syspara.PSA > 0) ? 1 : 0;
				old_syspara.PSA = cur_syspara.PSA;
			}
		  if(cur_syspara.CS != old_syspara.CS)
			{
				CS0 = ((cur_syspara.CS & 0x01) > 0) ? 1 : 0;
				CS1 = ((cur_syspara.CS & 0x02) > 0) ? 1 : 0;				
				old_syspara.CS = cur_syspara.CS;
			}
			if(cur_syspara.AA != old_syspara.AA)
			{
//				AA0 = ((cur_syspara.CS & 0x01) > 0) ? 1 : 0;
//				AA1 = ((cur_syspara.CS & 0x02) > 0) ? 1 : 0;	
//				AA2 = ((cur_syspara.CS & 0x02) > 0) ? 1 : 0;	
					if(cur_syspara.AA * 5 == 0)
					{
						A1_0_5dB  = 1;
						A1_1dB = 1;
						A1_2dB = 1;
						A1_4dB = 1;
						A1_8dB = 1;
						A1_16dB = 1;
						A1_15dB = 1;
						A2_0_5dB = 1;
						A2_1dB = 1;
						A2_2dB = 1;
						A2_4dB = 1;
						A2_8dB = 1;
						A2_16dB = 1;
						A2_15dB = 1;
					}
					else if(cur_syspara.AA * 5 == 5)
					{
						A1_0_5dB  = 1;
						A1_1dB = 0;
						A1_2dB = 1;
						A1_4dB = 0;
						A1_8dB = 1;
						A1_16dB = 1;
						A1_15dB = 1;
						A2_0_5dB = 1;
						A2_1dB = 0;
						A2_2dB = 1;
						A2_4dB = 0;
						A2_8dB = 1;
						A2_16dB = 1;
						A2_15dB = 1;
					}
					else if(cur_syspara.AA * 5 == 15)
					{
						A1_0_5dB  = 1;
						A1_1dB = 0;
						A1_2dB = 0;
						A1_4dB = 0;
						A1_8dB = 0;
						A1_16dB = 1;
						A1_15dB = 1;
						A2_0_5dB = 1;
						A2_1dB = 0;
						A2_2dB = 0;
						A2_4dB = 0;
						A2_8dB = 0;
						A2_16dB = 1;
						A2_15dB = 1;
					}
					else if(cur_syspara.AA * 5 == 20)
					{
						A1_0_5dB  = 1;
						A1_1dB = 1;
						A1_2dB = 1;
						A1_4dB = 0;
						A1_8dB = 1;
						A1_16dB = 0;
						A1_15dB = 1;
						A2_0_5dB = 1;
						A2_1dB = 1;
						A2_2dB = 1;
						A2_4dB = 0;
						A2_8dB = 1;
						A2_16dB = 0;
						A2_15dB = 1;
					}
					else if(cur_syspara.AA * 5 == 25)
					{
						A1_0_5dB  = 1;
						A1_1dB = 0;
						A1_2dB = 1;
						A1_4dB = 1;
						A1_8dB = 0;
						A1_16dB = 0;
						A1_15dB = 1;
						A2_0_5dB = 1;
						A2_1dB = 0;
						A2_2dB = 1;
						A2_4dB = 1;
						A2_8dB = 1;
						A2_16dB = 0;
						A2_15dB = 1;
					}
					else if(cur_syspara.AA * 5 == 30)
					{
						A1_0_5dB  = 1;
						A1_1dB = 1;
						A1_2dB = 0;
						A1_4dB = 0;
						A1_8dB = 0;
						A1_16dB = 0;
						A1_15dB = 1;
						A2_0_5dB = 1;
						A2_1dB = 1;
						A2_2dB = 0;
						A2_4dB = 0;
						A2_8dB = 0;
						A2_16dB = 0;
						A2_15dB = 1;				
					}
					else
					{
						A1_0_5dB  = 1;
						A1_1dB = 0;
						A1_2dB = 0;
						A1_4dB = 0;
						A1_8dB = 0;
						A1_16dB = 1;
						A1_15dB = 0;
						A2_0_5dB = 1;
						A2_1dB = 0;
						A2_2dB = 0;
						A2_4dB = 0;
						A2_8dB = 0;
						A2_16dB = 1;
						A2_15dB = 0;		
					}
				A4_5dB = ((cur_syspara.AA & 0x01) > 0) ? 1 : 0;
				A4_10dB = ((cur_syspara.AA & 0x02) > 0) ? 1 : 0;				
				A4_15dB = ((cur_syspara.AA & 0x04) > 0) ? 1 : 0;
				A3_5dB = A4_5dB;
 				A3_10dB = A4_10dB;
				A3_15dB = A4_15dB;
				old_syspara.AA = cur_syspara.AA;
			}
			if(cur_syspara.FS != old_syspara.FS)
			{
				if((cur_syspara.FS * 5 + 380) >= 380 && (cur_syspara.FS * 5 + 380) <= 470)
				{
					S1Y = 1; // 需要修改
					S1N = 0;
					
					S2Y1 = 1;
					S2N1 = 1;
					S2Y2 = 1;
					S2N2 = 1;
				}
				else if((cur_syspara.FS * 5 + 380) > 470 && (cur_syspara.FS * 5 + 380)  <= 700)
				{
					S1Y = 1; // 需要修改
					S1N = 0; //
					
					S2Y1 = 1;
					S2N1 = 1;
					S2Y2 = 1;
					S2N2 = 1;
				}
				else if((cur_syspara.FS * 5 + 380) > 700 && (cur_syspara.FS * 5 + 380)  <= 1100)
				{
					S2Y1 = 1;
					S2N1 = 0;
					S2Y2 = 0;
					S2N2 = 0;
				}
				else if((cur_syspara.FS * 5 + 380) > 1100 && (cur_syspara.FS * 5 + 380)  <= 1500)
				{
					S2Y1 = 0;
					S2N1 = 1;
					S2Y2 = 0;
					S2N2 = 1;				
				}
				else if((cur_syspara.FS * 5 + 380) > 1500 && (cur_syspara.FS * 5 + 380)  <= 2000)
				{
					S2Y1 = 0;
					S2N1 = 0;
					S2Y2 = 1;
					S2N2 = 0;				
				}
				else if((cur_syspara.FS * 5 + 380) > 2000 && (cur_syspara.FS * 5 + 380)  <= 2750)
				{
					S3Y = 0;
					S3N = 0;
					S2Y1 = 1;
					S2N1 = 1;
					S2Y2 = 1;
					S2N2 = 1;
				}
				else if((cur_syspara.FS * 5 + 380) > 2750 && (cur_syspara.FS * 5 + 380) <= 3250)
				{
					S3Y = 0;
					S3N = 1;
					S2Y1 = 1;
					S2N1 = 1;
					S2Y2 = 1;
					S2N2 = 1;
				}
				else if((cur_syspara.FS * 5 + 380) > 3250 && (cur_syspara.FS * 5 + 380) <= 4000)
				{
					S3Y = 1;
					S3N = 0;
					S2Y1 = 1;
					S2N1 = 1;
					S2Y2 = 1;
					S2N2 = 1;
				}		
				else if((cur_syspara.FS * 5 + 380) > 4000 && (cur_syspara.FS * 5 + 380) <= 6000)
				{
					S3Y = 1;
					S3N = 1;
					S2Y1 = 1;
					S2N1 = 1;
					S2Y2 = 1;
					S2N2 = 1;
				}			
				else if((cur_syspara.FS * 5 + 380) > 6000 && (cur_syspara.FS * 5 + 380) <= 9750)
				{
					S4_1 = 0;
					S4_2 = 1;
					S4_3 = 1;
					S2Y1 = 1;
					S2N1 = 1;
					S2Y2 = 1;
					S2N2 = 1;
				}		
				else if((cur_syspara.FS * 5 + 380) > 9750 && (cur_syspara.FS * 5 + 380) <= 12000)
				{
					S4_1 = 1;
					S4_2 = 1;
					S4_3 = 0;
					S2Y1 = 1;
					S2N1 = 1;
					S2Y2 = 1;
					S2N2 = 1;
				}		
				else if((cur_syspara.FS * 5 + 380) > 12000 && (cur_syspara.FS * 5 + 380) <= 18000)
				{
					S4_1 = 1;
					S4_2 = 0;
					S4_3 = 1;
					S2Y1 = 1;
					S2N1 = 1;
					S2Y2 = 1;
					S2N2 = 1;
				}					
				old_syspara.FS = cur_syspara.FS;
			}
			if(cur_syspara.PD != old_syspara.PD)
			{
				PDD = ((cur_syspara.PD & 0x01) > 0) ? 1 : 0;
				PDC = ((cur_syspara.PD & 0x02) > 0) ? 1 : 0;	
				PDB = ((cur_syspara.PD & 0x04) > 0) ? 1 : 0;	
				PDA = ((cur_syspara.PD & 0x08) > 0) ? 1 : 0;	
				old_syspara.PD = cur_syspara.PD;
			}
			memset(&cur_syspara,0,sizeof(cur_syspara));
			memset(Rec_Buff,0,sizeof(Rec_Buff)); 
			Rec_Finish = ~Rec_Finish;
		}
	}
}