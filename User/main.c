#include "stm32f10x_it.h"
#include "init.h"
#include "conmunication.h"
#include "string.h"
#define CLI()		__set_PRIMASK(1)
#define SEI()		__set_PRIMASK(0)

 FATFS fs; 
 FRESULT res;  
 FIL file;                       
 UINT br,bw;
 DIR dir;

extern signed short OutData[4];
CanTxMsg aTxMessage;	
extern unsigned char WQS_flag, Glider_flag;
extern struct Tail_Rudder TailData;
extern float TempGlider[9];

int test_data = 0;
/* ************************************* */
char temp[10];
char fatbufw1[50]={0};//滑翔机控制数据缓冲区
char fatbufw2[50]={0};//水质信息数据缓冲区
     
int main(void)
{	
	CLI();	
    LED_Config();
	SysTick_Init();
	UART_INIT();				// U1-PA09-PA10		U2-PA02-PA03	U4-PC10_PC11
	PWM_INIT();
	CAN_Config();
	NVIC_of_All();
	SEI();
	
    res = SD_Init();
	
	res = f_mount(&fs,"0:",0); //挂载文件系统
	
//	res = f_open(&file,"test.txt",FA_OPEN_ALWAYS|FA_WRITE);//创建并打开一个文件
//    	
//    f_close(&file);     //关闭文件系统
        TempWQS[0]=1.141;
		TempWQS[1]=2.142;
		TempWQS[2]=3.143;
		TempWQS[3]=4.144;
	    TempGlider[0]=2.547;
		TempGlider[1]=25.547;
		TempGlider[2]=30.547;
		TempGlider[3]=15.547;
		TempGlider[4]=257.154;
		TempGlider[5]=0.547;
		TempGlider[6]=24.547;
	    
		
	while (1)
	{	
        strcpy (fatbufw1,"depth:");   //深度
		sprintf(temp,"%.3f",TempGlider[0]);
		strcat (fatbufw1,temp);
		strcat (fatbufw1,",");
		strcat (fatbufw1,"T:");       //温度
		sprintf(temp,"%.3f",TempGlider[1]);
		strcat (fatbufw1,temp);
		strcat (fatbufw1,",");
		strcat (fatbufw1,"aop:");     //俯仰角
		sprintf(temp,"%.3f",TempGlider[2]);
		strcat (fatbufw1,temp);
		strcat (fatbufw1,",");
		strcat (fatbufw1,"roll:");    //横滚角
		sprintf(temp,"%.3f",TempGlider[3]);
		strcat (fatbufw1,temp);
		strcat (fatbufw1,",");
		strcat (fatbufw1,"orient:");    //航向角
		sprintf(temp,"%.3f",TempGlider[4]);
		strcat (fatbufw1,temp);
		strcat (fatbufw1,",");
		strcat (fatbufw1,"d_rate:");    //下潜速度
		sprintf(temp,"%.3f",TempGlider[5]);
		strcat (fatbufw1,temp);
		strcat (fatbufw1,",");
		strcat (fatbufw1,"power:");    //电源电压
		sprintf(temp,"%.3f",TempGlider[6]);
		strcat (fatbufw1,temp);
		strcat (fatbufw1,"\r\n");
		printf("%s",fatbufw1);
		
		res = f_open(&file,"1.txt",FA_OPEN_ALWAYS|FA_WRITE);//滑翔机控制数据存储到SD卡
		if(!res)
		{
			//LED1=!LED1; 
			f_lseek(&file,file.fsize);                             //移动文件指针到结尾处
			res = mf_write(fatbufw1,strlen(fatbufw1)); 		
			if(!res)
			{
			  strcpy (fatbufw1,"0");
			
			}
							
		 f_close(&file);	
		}else f_close(&file);	
		
		strcpy (fatbufw2,"PH:");
		sprintf(temp,"%.3f",TempWQS[0]);
		strcat (fatbufw2,temp);
		strcat (fatbufw2,",");
		strcat (fatbufw2,"ORP:");
		sprintf(temp,"%.3f",TempWQS[1]);
		strcat (fatbufw2,temp);
		strcat (fatbufw2,",");
		strcat (fatbufw2,"EC:");
		sprintf(temp,"%.3f",TempWQS[2]);
		strcat (fatbufw2,temp);
		strcat (fatbufw2,",");
		strcat (fatbufw2,"TUR:");
		sprintf(temp,"%.3f",TempWQS[3]);
		strcat (fatbufw2,temp);
		strcat (fatbufw2,"\r\n");
		printf("%s",fatbufw2);
		
		res = f_open(&file,"0:1.txt",FA_OPEN_ALWAYS|FA_WRITE);  //水质信息存储到SD卡
		if(!res)
		{
			//LED1=!LED1; 
			f_lseek(&file,file.fsize);                             //移动文件指针到结尾处
			res = mf_write(fatbufw2,strlen(fatbufw2)); 		
			if(!res)
			{
			  strcpy (fatbufw2,"0");
			 
			}
							
		 f_close(&file);	
		}else f_close(&file);		
		
	Delay_ms(1000);	
	

//		PWMoutput1 = (uint16_t)(1700 + (1000*TailData.AngTail)/90.0f);
//		PWMoutput1 = (int16_t)TailData.AngTail;
		/* 滑翔机控制板状态信息采集完成后上传到树莓派 */
//		switch(1)
//		{
//		case 1:
		 						
//				Glider2RaspberryPi();
//				Glider_flag &= 0x00;
//				break;
//			case 0x11:
//				break;
//		}

//		/* 水质信息采集完成后上传到树莓派 */
//		if (WQS_flag == 0x0f)
//		{
////			test_data = 1;
//			WQS_flag &= 0x00;
//			WQS2RaspberryPi();
//		}
	}
}

//OutPut_Data(); //uart2
/*********************************************END OF FILE**********************/
