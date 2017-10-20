#include "can.h" 
#include <stdlib.h>
#include "conmunication.h"
#include "uart.h"

extern CanRxMsg RxMessage;
extern CanTxMsg TxMessage;

struct DriverDataStruct *MotorPara;
/* 水质信息数据存储结构体指针 */
struct    WQSDataStruct *WQSPara;
/* 水质数据记录标志位 */
volatile unsigned char WQS_flag = 0x00;
/* 滑翔机数据记录标志位 */
volatile unsigned char Glider_flag = 0x00;
/* 水质信息数据存储结构体 */
struct WQSDataStruct wqs_data;
/* 驱动数据存储结构体 */
struct DriverDataStruct driver_data;
/* MCU&Raspi串口协议结构体 */
struct MCU2Raspi UploadData;

float Tempph = 0, Temporp, Tempec, Temptur, TempWQS[4], TempGlider[9];

void WQS2RaspberryPi(void);

void DriverWriteData(struct DriverDataStruct *DriverWriteData)
{
	TxMessage.ExtId=DriverWriteData->Dfi;					 //使用的扩展ID
	TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
	TxMessage.RTR=CAN_RTR_REMOTE;				 //发送的是数据
	TxMessage.DLC=8;							 //数据长度为2字节
	TxMessage.Data[0]=(DriverWriteData->Volocity >> 8) & 0xff;
	TxMessage.Data[1]=DriverWriteData->Volocity & 0xff;
	TxMessage.Data[2]=(int)DriverWriteData->Kp;
	TxMessage.Data[3]=(int)((DriverWriteData->Kp-(int)DriverWriteData->Kp)*100);
	TxMessage.Data[4]=(int)DriverWriteData->Ki;
	TxMessage.Data[5]=(int)((DriverWriteData->Ki-(int)DriverWriteData->Ki)*100);
	TxMessage.Data[6]=DriverWriteData->Volt;
	TxMessage.Data[7]=DriverWriteData->Tc;
	CAN_Transmit(CAN1, &TxMessage);
}

void DriverReadData(struct DriverDataStruct *DriverRemoteData)
{
	TxMessage.ExtId=DriverRemoteData->Dfi;					 //使用的扩展ID
	TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
	TxMessage.RTR=CAN_RTR_REMOTE;				 //发送的是数据
	CAN_Transmit(CAN1, &TxMessage);
}

/*
函数名称: DriverReadWriteData
输入参数: *DriverSendData
输出参数: 0 参数错误, 1 运动参数遥测, 2 功率参数遥测, 3 运动参数写入
函数功能: 主机使用该函数与从机(驱动板)交互
*/

unsigned char DriverReadWriteData(struct DriverDataStruct *DriverSendData)
{
	static CanTxMsg TxMessage;
	if (DriverSendData->Dfi == DriverFrameMotion)
	{
		TxMessage.ExtId=DriverSendData->Dfi;					 //使用的扩展ID
		TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
		TxMessage.RTR=CAN_RTR_REMOTE;				 //发送的是数据
		TxMessage.DLC = 0;
		CAN_Transmit(CAN1, &TxMessage);
		return 1;
	}
	else if (DriverSendData->Dfi == DriverFrameCapacity)
	{
		TxMessage.ExtId=DriverSendData->Dfi;					 //使用的扩展ID
		TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
		TxMessage.RTR=CAN_RTR_REMOTE;				 //发送的是数据
		CAN_Transmit(CAN1, &TxMessage);
		return 2;
	}
	else if (DriverSendData->Dfi == DriverFrameWrite)
	{
		TxMessage.ExtId=DriverSendData->Dfi;					 //使用的扩展ID
		TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
		TxMessage.RTR=CAN_RTR_DATA;				 //发送的是数据
		TxMessage.DLC=8;							 //数据长度为2字节
		TxMessage.Data[0]=(DriverSendData->Volocity >> 8) & 0xff;
		TxMessage.Data[1]=DriverSendData->Volocity & 0xff;
		TxMessage.Data[2]=(int)DriverSendData->Kp;
		TxMessage.Data[3]=(int)((DriverSendData->Kp-(int)DriverSendData->Kp)*100);
		TxMessage.Data[4]=(int)DriverSendData->Ki;
		TxMessage.Data[5]=(int)((DriverSendData->Ki-(int)DriverSendData->Ki)*100);
		TxMessage.Data[6]=DriverSendData->Volt;
		TxMessage.Data[7]=DriverSendData->Tc;
		CAN_Transmit(CAN1, &TxMessage);
		return 3;
	}
	else
	{
		return 0;
	}
}

/* 水质数据读写
   参数:水质数据结构体
*/
unsigned char WQSReadWriteData(struct WQSDataStruct *WQSSendData)
{
	CanTxMsg TxMessage;
	if (WQSSendData->WQSFi == WQSFrameWrite)
	{
		TxMessage.ExtId=WQSFrameWrite;					 //使用的扩展ID
		TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
		TxMessage.RTR=CAN_RTR_DATA;				 //发送的是数据
		TxMessage.DLC = 0;
		CAN_Transmit(CAN1, &TxMessage);
		return 1;
	}
	else if (WQSSendData->WQSFi == WQSFrameRead)
	{
		/* 发送的是水质信息采集帧 */
		TxMessage.ExtId=WQSFrameRead;					 
		TxMessage.IDE=CAN_ID_EXT;		
		/* 该帧的基本类型为数据帧 */
		TxMessage.RTR=CAN_RTR_DATA;				
		TxMessage.DLC = 1;
		/* 传感器数据通道 */
		TxMessage.Data[0] = WQSSendData->WQSchannel;
		CAN_Transmit(CAN1, &TxMessage);
		return 2;
	}
	else
	{
		return 0;
	}
}

unsigned char GliderParameterGet(struct GliderDataStruct *GliderRecData)
{
	
}

float Test_a, Test_b;

unsigned char GliderReadWriteData(struct GliderDataStruct *GliderSendData)
{
	CanTxMsg TxMessage;
	union int2char i2c;
	if (GliderSendData->GLIDERFi == GliderFrameWrite)
	{
		TxMessage.ExtId=GliderFrameWrite;					 //使用的扩展ID
		TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
		TxMessage.RTR=CAN_RTR_DATA;				 //发送的是数据
		TxMessage.DLC = 5;
//				USART2_SendByte('%');
//				USART2_SendByte(GliderSendData->Gliderchannel); //%%
		switch(GliderSendData->Gliderchannel)
		{
				case GliderAng:
					TxMessage.Data[0] = GliderSendData->Gliderchannel;
					i2c.num = GliderSendData->angSink;
					TxMessage.Data[1] = i2c.byte[0];
					TxMessage.Data[2] = i2c.byte[1];
					i2c.num = GliderSendData->angFloat;
					TxMessage.Data[3] = i2c.byte[0];
					TxMessage.Data[4] = i2c.byte[1];
					break;
				case GliderTim:
					TxMessage.Data[0] = GliderSendData->Gliderchannel;
					i2c.num = GliderSendData->timSink;
					TxMessage.Data[1] = i2c.byte[0];
					TxMessage.Data[2] = i2c.byte[1];
					i2c.num = GliderSendData->timFloat;
					TxMessage.Data[3] = i2c.byte[0];
					TxMessage.Data[4] = i2c.byte[1];
					break;
				case GliderDeep:
					TxMessage.Data[0] = GliderSendData->Gliderchannel;
					i2c.num = GliderSendData->deepInit;
					TxMessage.Data[1] = i2c.byte[0];
					TxMessage.Data[2] = i2c.byte[1];
					i2c.num = GliderSendData->deepEnd;
					TxMessage.Data[3] = i2c.byte[0];
					TxMessage.Data[4] = i2c.byte[1];
					break;	
				case GliderTurbine:
					TxMessage.Data[0] = GliderSendData->Gliderchannel;
					i2c.num = GliderSendData->leftTurbine; Test_b = i2c.num;
					TxMessage.Data[1] = i2c.byte[0];
					TxMessage.Data[2] = i2c.byte[1];
					i2c.num = GliderSendData->rightTurbine; Test_a = i2c.num;
					TxMessage.Data[3] = i2c.byte[0];
					TxMessage.Data[4] = i2c.byte[1];
					break;
		}
		CAN_Transmit(CAN1, &TxMessage);
		return 1;
	}
	else if (GliderSendData->GLIDERFi == GliderFrameRead)
	{
		/* 发送的是滑翔机信息采集帧 */
		TxMessage.ExtId=FrameID_R_GliderRead;					 
		TxMessage.IDE=CAN_ID_EXT;		
		/* 该帧的基本类型为数据帧 */
		TxMessage.RTR=CAN_RTR_DATA;				
		TxMessage.DLC = 1;
		/* 传感器数据通道 */
		TxMessage.Data[0] = GliderSendData->Gliderchannel;
		CAN_Transmit(CAN1, &TxMessage);
		return 2;
	}
	else
	{
		return 0;
	}
}

unsigned char TailReadWriteData(struct Tail_Rudder *TailData)
{
	CanTxMsg TxMessage;
	union int2char i2c;
	if (TailData->TAILFi  == FrameID_W_Tail)
	{
		TxMessage.ExtId=FrameID_W_Tail;					 //使用的扩展ID
		TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
		TxMessage.RTR=CAN_RTR_DATA;				 //发送的是数据
		TxMessage.DLC = 5;
//				USART2_SendByte('%');
//				USART2_SendByte(GliderSendData->Gliderchannel); //%%
		switch(TailData->Tailchannel)
		{
				case 0x00:
					TxMessage.Data[0] = TailData->Tailchannel;
					i2c.num = TailData->AngTail;
					TxMessage.Data[1] = i2c.byte[0];
					TxMessage.Data[2] = i2c.byte[1];
					break;
		}
		CAN_Transmit(CAN1, &TxMessage);
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned char GliderSerialRWData(unsigned char RW,struct GliderDataStruct *GliderSendData)
{
	union int2char i2c;
	unsigned int sum;
	if (RW == 0x01)
	{
		USART1_SendByte(0xca);
		USART1_SendByte(0xac);
		USART1_SendByte(18);
		USART1_SendByte(0x03);
		
		sum = 18+0x03;
		
		i2c.num = GliderSendData->angSink;
		sum += i2c.byte[0];
		USART1_SendByte(i2c.byte[0]);
		sum += i2c.byte[1];
		USART1_SendByte(i2c.byte[1]);
		
		i2c.num = GliderSendData->angFloat;
		sum += i2c.byte[0];
		USART1_SendByte(i2c.byte[0]);
		sum += i2c.byte[1];
		USART1_SendByte(i2c.byte[1]);
		
		i2c.num = GliderSendData->timSink;
		sum += i2c.byte[0];
		USART1_SendByte(i2c.byte[0]);
		sum += i2c.byte[1];
		USART1_SendByte(i2c.byte[1]);

		i2c.num = GliderSendData->keepSink;
		sum += i2c.byte[0];
		USART1_SendByte(i2c.byte[0]);
		sum += i2c.byte[1];
		USART1_SendByte(i2c.byte[1]);
		
		i2c.num = GliderSendData->timFloat;
		sum += i2c.byte[0];
		USART1_SendByte(i2c.byte[0]);
		sum += i2c.byte[1];
		USART1_SendByte(i2c.byte[1]);

		i2c.num = GliderSendData->keepFloat;
		sum += i2c.byte[0];
		USART1_SendByte(i2c.byte[0]);
		sum += i2c.byte[1];
		USART1_SendByte(i2c.byte[1]);
		
		i2c.num = GliderSendData->deepInit;
		sum += i2c.byte[0];
		USART1_SendByte(i2c.byte[0]);
		sum += i2c.byte[1];
		USART1_SendByte(i2c.byte[1]);
		
		i2c.num = GliderSendData->deepEnd;
		sum += i2c.byte[0];
		USART1_SendByte(i2c.byte[0]);
		sum += i2c.byte[1];
		USART1_SendByte(i2c.byte[1]);
		
		USART1_SendByte(sum|0xff);
		USART1_SendByte(0xbb);
	}
	else if(RW == 0x00)
	{
		
	}
}
/********************************************************************/
void DriverSalveHander(void)
{
	unsigned char i;
	CanRxMsg RxMessage;
	unsigned char TEMP[8];
	struct DriverDataStruct *DriverReciveData;
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
  if((RxMessage.ExtId==FrameID_W_DriverWrite) && (RxMessage.RTR==CAN_RTR_DATA) && (RxMessage.DLC==8))
  {
		//receive
		DriverReciveData->Volocity = (RxMessage.Data[0] << 8) | RxMessage.Data[1];
		DriverReciveData->Kp = (float)(RxMessage.Data[2] + ((float)RxMessage.Data[3]/100));
		DriverReciveData->Ki = (float)(RxMessage.Data[4] + ((float)RxMessage.Data[5]/100));
		DriverReciveData->Volt = RxMessage.Data[6];
		DriverReciveData->Tc = RxMessage.Data[7];
		for (i = 0; i < 8; i++)
		{
			USART1_SendByte(RxMessage.Data[i]);
		}
  }
	  /* ExtId扩展标识 数据帧 数据长度匹配 */
  else if ((RxMessage.ExtId==FrameID_R_DriverMotion) && (RxMessage.RTR==CAN_RTR_REMOTE))
  {
		
		TxMessage.ExtId=FrameID_R_DriverMotion;					 //使用的扩展ID
		TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
		TxMessage.RTR=CAN_RTR_DATA;				 //发送的是数据
		TxMessage.DLC=6;							 //数据长度为2字节
		TxMessage.Data[0]=0xf1;
		TxMessage.Data[1]=0xf2;
		TxMessage.Data[2]=0xf3;
		TxMessage.Data[3]=0xf4;
		TxMessage.Data[4]=0xf5;
		TxMessage.Data[5]=0xf7;

		CAN_Transmit(CAN1, &TxMessage);
	}
	else if ((RxMessage.ExtId==FrameID_R_DriverCapcity) && (RxMessage.RTR==CAN_RTR_REMOTE))
	{
		TxMessage.ExtId=FrameID_R_DriverCapcity;					 //使用的扩展ID
		TxMessage.IDE=CAN_ID_EXT;					 //扩展模式
		TxMessage.RTR=CAN_RTR_DATA;				 //发送的是数据
		TxMessage.DLC=4;							 //数据长度为2字节
		TxMessage.Data[0]=0xc1;
		TxMessage.Data[1]=0xc2;
		TxMessage.Data[2]=0xc3;
		TxMessage.Data[3]=0xc4;

		CAN_Transmit(CAN1, &TxMessage);
	}
}

void GliderSalveHander(void)
{
	CanRxMsg RxMessage;
	union int2char i2c;
	int temp;
	
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	
	switch(RxMessage.ExtId)
	{
		case FrameID_R_GliderRead:
			switch(RxMessage.Data[0])
			{
				case GliderAng:
					i2c.byte[0] = RxMessage.Data[1];
					i2c.byte[1] = RxMessage.Data[2];
					temp = i2c.num;
					i2c.byte[0] = RxMessage.Data[3];
					i2c.byte[1] = RxMessage.Data[4];
					temp = i2c.num;
					break;
				case GliderTim:
					i2c.byte[0] = RxMessage.Data[1];
					i2c.byte[1] = RxMessage.Data[2];
					temp = i2c.num;
					i2c.byte[0] = RxMessage.Data[3];
					i2c.byte[1] = RxMessage.Data[4];
					temp = i2c.num;
					break;
				case GliderDeep:
					i2c.byte[0] = RxMessage.Data[1];
					i2c.byte[1] = RxMessage.Data[2];
					temp = i2c.num;
					i2c.byte[0] = RxMessage.Data[3];
					i2c.byte[1] = RxMessage.Data[4];
					temp = i2c.num;
					break;
			}
			break;
	}
}
extern int test_data;
extern struct Tail_Rudder TailData;
void MatserHandler(void)
{
	union float2char f2c;
	CanRxMsg RxMessage;
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	
	switch(RxMessage.ExtId)
	{
		
		case FrameID_R_DriverMotion:
			if (RxMessage.RTR == CAN_RTR_DATA && RxMessage.DLC == 8)
			{

			}
			break;
		case FrameID_R_DriverCapcity:
			if (RxMessage.RTR == CAN_RTR_DATA && RxMessage.DLC == 4)
			{

			}
			break;
		case FrameID_R_WQSRead:
//			USART2_SendByte(FrameID_R_WQSRead);
//			USART2_SendByte(RxMessage.RTR);
//			USART2_SendByte(RxMessage.DLC);
			if (RxMessage.RTR == CAN_RTR_DATA && RxMessage.DLC == 5)
			{
//				USART2_SendByte(RxMessage.Data[0]);
				
				switch(RxMessage.Data[0])
				{
					USART2_SendByte(RxMessage.Data[0]);
					
					case WQSPH://0x01 0000 0001
//						WQS_flag &= 0x00;
						f2c.byte[0] = RxMessage.Data[1];
						f2c.byte[1] = RxMessage.Data[2];
						f2c.byte[2] = RxMessage.Data[3];
						f2c.byte[3] = RxMessage.Data[4];
						TempWQS[0] = f2c.num;
						WQS_flag |= WQSPH;
						break;
					case WQSORP://0x02 0000 0010
//						WQS_flag &= 0x00;
						f2c.byte[0] = RxMessage.Data[1];
						f2c.byte[1] = RxMessage.Data[2];
						f2c.byte[2] = RxMessage.Data[3];
						f2c.byte[3] = RxMessage.Data[4];
						TempWQS[1] = f2c.num; 
						WQS_flag |= WQSORP;
						break;
					case WQSEC://0x03 0000 0011
//						WQS_flag &= 0x00;
						f2c.byte[0] = RxMessage.Data[1];
						f2c.byte[1] = RxMessage.Data[2];
						f2c.byte[2] = RxMessage.Data[3];
						f2c.byte[3] = RxMessage.Data[4];
						TempWQS[2] = f2c.num; 
						WQS_flag |= WQSEC;
						break;
					case WQSTUR:
//						WQS_flag &= 0x00;
						f2c.byte[0] = RxMessage.Data[1];
						f2c.byte[1] = RxMessage.Data[2];
						f2c.byte[2] = RxMessage.Data[3];
						f2c.byte[3] = RxMessage.Data[4];
						TempWQS[3] = f2c.num;
						WQS_flag |= WQSTUR; test_data = 5;
						break;
					case WQSALL:
						break;
				}
			}
			break;
			case FrameID_R_GliderRead:
				
					if (RxMessage.RTR == CAN_RTR_DATA && RxMessage.DLC == 5)
					{
						switch(RxMessage.Data[0])
						{
							case GliderAng:
//								USART1_SendByte(RxMessage.Data[0]);
								f2c.byte[0] = RxMessage.Data[1];
								f2c.byte[1] = RxMessage.Data[2];
								f2c.byte[2] = RxMessage.Data[3];
								f2c.byte[3] = RxMessage.Data[4];
								TempGlider[1] = f2c.num;
								Glider_flag |= GliderAng;
								break;
							case GliderTim:
								f2c.byte[0] = RxMessage.Data[1];
								f2c.byte[1] = RxMessage.Data[2];
								f2c.byte[2] = RxMessage.Data[3];
								f2c.byte[3] = RxMessage.Data[4];
								TempGlider[2] = f2c.num;
								if (TempGlider[2] != 0)
								{
									TailData.AngTail = TempGlider[2];
								}
								Glider_flag |= GliderTim;
								break;
							case GliderDeep:
//								USART1_SendByte(RxMessage.Data[0]);
								f2c.byte[0] = RxMessage.Data[1];
								f2c.byte[1] = RxMessage.Data[2];
								f2c.byte[2] = RxMessage.Data[3];
								f2c.byte[3] = RxMessage.Data[4];
								TempGlider[0] = f2c.num;
								Glider_flag |= GliderDeep;//TempGlider
								break;
						}
					}						
			break;
			/*case FrameID_W_GliderWrite:
					if (RxMessage.RTR == CAN_RTR_DATA && RxMessage.DLC == 5)
					{
						switch(RxMessage.Data[0])
						{
							case GliderTurbineL:
//								USART1_SendByte(RxMessage.Data[0]);
								f2c.byte[0] = RxMessage.Data[1];
								f2c.byte[1] = RxMessage.Data[2];
								f2c.byte[2] = RxMessage.Data[3];
								f2c.byte[3] = RxMessage.Data[4];
								TempGlider[3] = f2c.num;
								Glider_flag |= GliderTurbineL;
								break;
							case GliderTurbineR:
								f2c.byte[0] = RxMessage.Data[1];
								f2c.byte[1] = RxMessage.Data[2];
								f2c.byte[2] = RxMessage.Data[3];
								f2c.byte[3] = RxMessage.Data[4];
								TempGlider[4] = f2c.num;
								Glider_flag |= GliderTurbineL;
								break;
						}
					}
			break;*/			
	}
}

void WQS2RaspberryPi(void)
{
		signed char i, k;
		union float2char f2c;
	
		UploadData.FrameHeadI = 0xca;
		UploadData.FrameHeadII = 0xac;
		UploadData.FrameIDI  = FrameID_R_WQSRead & 0xff;
		UploadData.FrameIDII = FrameID_R_WQSRead >> 8;
		UploadData.DataLength= 4*4 + 5;
		UploadData.DataSum   = UploadData.FrameIDI + UploadData.FrameIDII + UploadData.DataLength;
		
		USART1_SendByte(UploadData.FrameHeadI);
		USART1_SendByte(UploadData.FrameHeadII);
		USART1_SendByte(UploadData.FrameIDI);
		USART1_SendByte(UploadData.FrameIDII);
		USART1_SendByte(UploadData.DataLength);
	
		for (k = 0; k < 4; k++)
		{
			f2c.num = TempWQS[k];
			for (i = 0; i < 4; i++)
			{
				USART1_SendByte(f2c.byte[i]);
				UploadData.DataSum += f2c.byte[i];
			}
		}
		USART1_SendByte(UploadData.DataSum);
		UploadData.DataSum = 0x00;
		USART1_SendByte(0xCC);
}

void Glider2RaspberryPi()
{
		signed char i, k;
		union float2char f2c;
	
		UploadData.FrameHeadI = 0xca;
		UploadData.FrameHeadII = 0xac;
		UploadData.FrameIDI  = FrameID_R_GliderRead & 0xff;
		UploadData.FrameIDII = FrameID_R_GliderRead >> 8;
		UploadData.DataLength= 2*4 + 5;
		UploadData.DataSum   = UploadData.FrameIDI + UploadData.FrameIDII + UploadData.DataLength;
		
		USART1_SendByte(UploadData.FrameHeadI);
		USART1_SendByte(UploadData.FrameHeadII);
		USART1_SendByte(UploadData.FrameIDI);
		USART1_SendByte(UploadData.FrameIDII);
		USART1_SendByte(UploadData.DataLength);
	
		for (k = 0; k < 2; k++)
		{
			f2c.num = TempGlider[k];
			TempGlider[k] = 0;
			for (i = 0; i < 4; i++)
			{
				USART1_SendByte(f2c.byte[i]);
				UploadData.DataSum += f2c.byte[i];
			}
		}
		USART1_SendByte(UploadData.DataSum);
		UploadData.DataSum = 0x00;
		USART1_SendByte(0xCC);
}
