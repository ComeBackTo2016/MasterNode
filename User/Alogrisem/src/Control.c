#include "Control.h"
#include "stm32f10x.h"
#include "timer.h"
#include "bsp_SysTick.h"
#include "init.h"
#include "CRC.h"
#include "GPIOLIKE51.h"
#include "conmunication.h"

/****************************************************************************/
#define IIC_BUFFER_SIZE	40
#define FLAG_RECV_REG_ADDR	    0
#define FLAG_RECV_DATA			1
#define FLAG_SEND_DATA			2

/* 寄存器地址宏定义 */
#define REG_SENSOR 0xB1
#define REG_LENGTH 0xB2
#define REG_READ   0xB3

/****接收数据类型定义*****/
#define CPG_Weiqi 0X00
#define CPG_Xiongqi 0X01
#define Static_Offset_1_Sub 0X02
#define Static_Offset_2_Sum 0X03
#define AUTU_ACTION 0X04
#define Static_Offset_3_Sum 0X05
#define Static_Offset_3_Sub 0X06
#define Clear_data 0X07

unsigned char IIC_Buffer[IIC_BUFFER_SIZE];
unsigned char *P_Data = (&IIC_Buffer[0] + 2);
unsigned char Data_Length = 0;
unsigned char Sensor_NO = 0;
  signed int  Check = 0;
unsigned char Count = 0;
unsigned char IIC_Reg_Flag = 0;
unsigned char Bottom_Data[84];
unsigned char Start_Add;
/****************************************************************************/
extern float Motor_Speed; 
extern float Motor_Log_degree_12;
extern float Motor_Log_degree_13;
extern float Motor_Amplitude_degree[3];    
extern float Motor_Dynamic_Offset_degree[3];

extern float Pectoral_Volcety;                 // 胸鳍速度
extern float Pectoral_Phase_Dif;               // 胸鳍相角差
extern float Pectoral_Amplitude[2];            // 幅值参数
extern float Pectoral_Dynamic_Offset[2];       // 动角

extern CanTxMsg TxMessage;

signed int LengthPosi = 0;
signed int LengthNega = 0;
signed int BoomPosition = 100;
signed int ModeIndex = 0;
signed int PowerOff = 1;

float SensorBox[21];                            // 传感器数据上传缓存区
union FLOAT2CHAR f2c;
unsigned char float2byte[4];
/*************************************************************/
unsigned char* Send_float_to_byte(float temp);
float Receive_byte_to_float(unsigned char* temp);
void CharDataProcess(void);
void PectoralDataProcess(void);
void GliderParameter(void);
void PectoralDynAngProcess(void);
void CanDataProcess(void);
void Gpg_Parameter_Get(void);
void DC_Parameter_Get(void);
void CancommondProcess(void);
/**
  * @brief  float数据2char型
	* @discrib 
  * @param  
  * @retval 
  */
unsigned char* Send_float_to_byte(float temp)
{
	union UFLOAT
	{
		float f;
		unsigned char byte[4];
	};
	union UFLOAT data;	
	int i;
	data.f = temp;
	for(i=0;i<4;i++)
	float2byte[i] = data.byte[i];
	return float2byte;
}

float Receive_byte_to_float(unsigned char* temp)
{
	union UFLOAT
	{
		float f;
		unsigned char byte[4];
	};
	union UFLOAT data;
	unsigned char i;
	for(i=0;i<4;i++)
	data.byte[i] = *(temp+i);
	return data.f;
}

int Receive_byte_to_int(unsigned char* temp)
{
	union UINT
	{
		int in;
		unsigned char byte[2];
	};
	union UINT data;
	unsigned char i;
	for(i=0;i<2;i++)
	data.byte[i] = *(temp+i);
	return data.in;
}

short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}

/***************************************************串口解析程序（开始）************************************************************/


/**************************************************************************
函数功能:控制参数解析函数（中断中执行）
入口参数:data 串口接收到的每一帧
返 回 值:无
数据格式:0xca 0xac reg1 reg2 num ... data ... sum() 0xcc
作    者:何宇帆(2016-09-20)
**************************************************************************/
#define FRAME_BYTE_FST 0xca
#define FRAME_BYTE_SEC 0xac
#define FRAME_BYTE_LST 0xcc
#define FRAME_HEAD_FLAG 0x01
#define FRAME_OVER_FLAG 0x02
#define BUFFER_SIZE 120

volatile unsigned char rec_data[BUFFER_SIZE];
volatile unsigned char rec_index = 0x00;
volatile unsigned char rec_flag = 0x00;

void FrameGet(unsigned char data)
{
	unsigned char i;

	if (data == FRAME_BYTE_FST)
	{
		rec_flag = rec_flag | FRAME_HEAD_FLAG;
		rec_data[rec_index] = data;
		rec_index++;
	}
	else if (data == FRAME_BYTE_SEC)
	{
		if (rec_flag & FRAME_HEAD_FLAG)
		{
			rec_flag = rec_flag & ~FRAME_OVER_FLAG;
			rec_index = 0;
		}
		else
		{
			rec_data[rec_index] = data;
			rec_index++;
			rec_flag = rec_flag & ~FRAME_HEAD_FLAG;
		}
	}
	else
	{
		rec_data[rec_index] = data;
		rec_flag &= ~FRAME_HEAD_FLAG;
		rec_index++;
		/* 当索引数值rec_index等于帧长度rec_data[2] */
		if (rec_index == rec_data[2])
		{
			
			if (rec_data[rec_index-1] == FRAME_BYTE_LST)
			{
				rec_flag |= FRAME_OVER_FLAG;
				/* 添加命令解析 */
//				CommondProcess();
				CancommondProcess();
			}
		}
	}
	
	if (rec_index == BUFFER_SIZE)
	{
		rec_index--;
	}
}

/**************************************************************************
函数功能:接收数据帧和校验
入口参数: 串口接收到的每一帧数据
返 回 值:和校验标志位 0 失败    1 成功
数据格式:reg1 reg2 num  ... data ... crc 0x
作    者:何宇帆(2016-09-20)
**************************************************************************/
unsigned char SumCheck(void)
{
	unsigned char i = 0;
	unsigned int sum_byte = 0x00;
	
	for (i = 0; i < rec_data[2] - 2; i++)
	{
		sum_byte += rec_data[i];
	}

	if ((sum_byte & 0xff) == rec_data[rec_data[2] - 2])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*************************************************************************
函数功能:接收数据帧分类处理
入口参数: 串口接收到的每一帧数据
备    注:判断rec_ID(rec_data[1]) 标识符然后对数据进行分类处理
作    者:何宇帆(2016-09-20)
**************************************************************************/
#define CPG_PARAMETER 0x42
#define DC_PARAMETER 0x02
#define GLIDER_PARAMETER 0x03
void CommondProcess(void)
{
	unsigned char rec_ID;
	if (rec_flag & FRAME_OVER_FLAG)
	{
		rec_flag &= ~FRAME_OVER_FLAG;
		if (SumCheck())
		{
			rec_ID = rec_data[0];
			switch(rec_ID)
			{
				case CPG_PARAMETER:
				break;
				case DC_PARAMETER:	
				break;
				case GLIDER_PARAMETER:
				break;
			}
		}
	}
}
int testa, testb, temp_in;
extern struct DriverDataStruct driver_data;
extern struct WQSDataStruct wqs_data;
struct GliderDataStruct GliderData;
struct Tail_Rudder TailData;
void CancommondProcess()
{
	union float2char f2c;
	static uint16_t canID;
	canID = rec_data[1];
	canID = canID << 8;
	canID |= rec_data[0];
//	testb = canID;
	if (rec_flag & FRAME_OVER_FLAG)
	{
		if (SumCheck())
		{
			switch(canID)
			{
				case FrameID_W_DriverWrite:
					
				break;
				case FrameID_R_DriverMotion:	
				break;
				case FrameID_R_DriverCapcity:
				break;
				case FrameID_R_WQSRead:
					
//					USART1_SendByte(FrameID_R_WQSRead);
					wqs_data.WQSFi = WQSFrameRead;
					wqs_data.WQSchannel = WQSALL;
					WQSReadWriteData(&wqs_data);
//					testa = 90;
				break;
				case FrameID_W_GliderWrite:
//					USART2_SendByte('%');
//					USART2_SendByte(FrameID_W_GliderWrite);//%%
					GliderData.GLIDERFi = GliderFrameWrite;
					GliderData.Gliderchannel = GliderTurbine;
					GliderData.leftTurbine = rec_data[5];
					GliderData.leftTurbine = GliderData.leftTurbine << 8;
					GliderData.leftTurbine |= rec_data[4];
					GliderData.rightTurbine = rec_data[7];
					GliderData.rightTurbine = GliderData.rightTurbine << 8;
					GliderData.rightTurbine |= rec_data[6];
					GliderReadWriteData(&GliderData);
					testb = GliderData.rightTurbine;
					testa = GliderData.leftTurbine;
				break;
				case FrameID_R_GliderRead:
					
					GliderData.GLIDERFi = GliderFrameRead;
					GliderData.Gliderchannel = 0x05;
					GliderReadWriteData(&GliderData);
				break;
				case FrameID_W_Tail:
					TailData.TAILFi = FrameID_W_Tail;
					TailData.Tailchannel = 0x00;
					f2c.byte[3] = rec_data[7];
					f2c.byte[2] = rec_data[6];
					f2c.byte[1] = rec_data[5];
					f2c.byte[0] = rec_data[4];
					TailData.AngTail = f2c.num;
					break;
			}
		}
		rec_flag &= ~FRAME_OVER_FLAG;
	}
}


/****************************************************IICBUS-RaspberryPi Communication***********************************************/
/**
  * @brief  iic传输错误后执行.
  * @param  None
  * @retval None
  */
void I2C_Error()
{
   ;
}

/**
  * @brief  IIC中断从机接收事件触发函数.
  * @param  
  * @retval 全局变量Count(数据长度)会在函数里面更新；IIC_Reg_Flag 在函数里面更新
  */
void IIC_EV_SALVE_RECV(unsigned char receive_data)
{
	static unsigned char iic_i;							// IIC数据接收累加标志位
	static unsigned char iic_read_flag = 0;	// IIC读一字节数据标志位
	static unsigned char iic_reg = 0;				// 虚拟寄存器暂存变量
				 unsigned char len_i;							// IIC发送缓存更新下标
	
	if (I2C_ReceiveData(I2C2) == 0x36 && iic_read_flag == 0)
	{
		iic_i = 0;
		iic_read_flag = 1;
	}
	else if (iic_read_flag ==1)
	{
		IIC_Buffer[iic_i] = I2C_ReceiveData(I2C2);
		iic_i++;
		if (iic_i == IIC_BUFFER_SIZE)
		{
			iic_i = 0;
			iic_read_flag = 0;
		}
	}
	else if (IIC_Reg_Flag == FLAG_RECV_REG_ADDR)
	{
		switch(I2C_ReceiveData(I2C2)) // 判断选中的是哪个寄存器
		{													   
			case REG_SENSOR:
				iic_reg = REG_SENSOR;
				IIC_Reg_Flag=FLAG_RECV_DATA;//下一个收到的字节是数据

				break;
			case REG_LENGTH:
				iic_reg=REG_LENGTH;
				IIC_Reg_Flag=FLAG_RECV_DATA;//下一个收到的字节是数据

				break;
			case REG_READ:
				iic_reg=REG_READ;
				Count=Data_Length+2;/* 将length装载入count，以便进行发送计数。加3是因为要加上起始位、校验位、结束位。
															 但是I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED会发掉起始位，所以count只需要
															 加2就行了 */

				IIC_Reg_Flag=FLAG_SEND_DATA;//下一个字节开始向主机发送数据
				break;
			default:
				I2C_Error();
				break;
		}
	}
	else if (IIC_Reg_Flag == FLAG_RECV_DATA)
	{
		switch(iic_reg)
		{
			case REG_SENSOR:
				Sensor_NO = I2C_ReceiveData(I2C2);												// 接收待读取的虚拟寄存器地址(参考Control.h中传感器虚拟寄存器地址)
				Start_Add = (Sensor_NO - 0xe0) * 4;												// 对应到发送缓存区中的数组下标

				break;
		case REG_LENGTH:
				Data_Length = I2C_ReceiveData(I2C2);
				for (len_i = 0; len_i < Data_Length;len_i++)											// 存储树莓派指令中指定长度的数据Bottom_Data到发送缓存中
				{
					f2c.num = SensorBox[Sensor_NO -0xe0 + len_i];
					Bottom_Data[Start_Add + len_i * 4 + 0] = f2c.byte[0];
					Bottom_Data[Start_Add + len_i * 4 + 1] = f2c.byte[1];
					Bottom_Data[Start_Add + len_i * 4 + 2] = f2c.byte[2];
					Bottom_Data[Start_Add + len_i * 4 + 3] = f2c.byte[3];
				}

				break;
		default:
				I2C_Error();
				break;
		}
		IIC_Reg_Flag = FLAG_RECV_REG_ADDR;//下一个收到的是寄存器地址
	}
	else
	{
		I2C_Error();
	}
}

extern float Motor_Speed; 
extern float Motor_Log_degree_12;
extern float Motor_Log_degree_13;
extern float Motor_Amplitude_degree[3];    
extern float Motor_Dynamic_Offset_degree[3];

extern float Pectoral_Volcety ;                 // 胸鳍速度
extern float Pectoral_Phase_Dif;                // 胸鳍相角差
extern float Pectoral_Amplitude[2];             // 幅值参数
extern float Pectoral_Dynamic_Offset[2];        // 动角
/**
  * @brief  IIC中断从机接收终止信号函数函数.
	* @discrib 判断首尾帧数据正确后开始解包数据
  * @param  
  * @retval 
  */

void IIC_EV_SALVE_STOP(void) //I2C_EVENT_SLAVE_STOP_DETECTED
{
	unsigned char i = 0;
	unsigned char e = 0;

	if((IIC_Buffer[0]==0XFE) && IIC_Buffer[39]==0XFA)
	{

		I2C_ITConfig( I2C2, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR, DISABLE );
		switch(IIC_Buffer[1])
		{
			case CPG_Weiqi:
				Motor_Speed                  = Receive_byte_to_float(P_Data);		P_Data += 4;        //Motor_Right  Grip_Front Grip_Back
				Motor_Log_degree_12          = Receive_byte_to_float(P_Data);		P_Data += 4;
				Motor_Log_degree_13	         = Receive_byte_to_float(P_Data);		P_Data += 4;
				Motor_Amplitude_degree[0]  	 = Receive_byte_to_float(P_Data);		P_Data += 4;
				Motor_Amplitude_degree[1] 	 = Receive_byte_to_float(P_Data);		P_Data += 4;
				Motor_Amplitude_degree[2]  	 = Receive_byte_to_float(P_Data);       P_Data += 4;
				Motor_Dynamic_Offset_degree[0]  = Receive_byte_to_float(P_Data);    P_Data += 4;
				Motor_Dynamic_Offset_degree[1]  = Receive_byte_to_float(P_Data);    P_Data += 4;
				Motor_Dynamic_Offset_degree[2]  = Receive_byte_to_float(P_Data);			
				P_Data                          = (&IIC_Buffer[0] + 2);                                 //数据指针归位;
                PBout(9) =0;  	
            break;
			case CPG_Xiongqi:
				Pectoral_Volcety             = Receive_byte_to_float(P_Data);		P_Data += 4;
                Pectoral_Phase_Dif           = Receive_byte_to_float(P_Data);		P_Data += 4; 
                Pectoral_Amplitude[0]        = Receive_byte_to_float(P_Data);		P_Data += 4; 
				Pectoral_Amplitude[1]        = Receive_byte_to_float(P_Data);		P_Data += 4; 			
                Pectoral_Dynamic_Offset[0]   = Receive_byte_to_float(P_Data);		P_Data += 4;   
				Pectoral_Dynamic_Offset[1]   = Receive_byte_to_float(P_Data);
				P_Data                       = (&IIC_Buffer[0] + 2);                                    //数据指针归位;   
                PBout(9) =0;            
			break;
			case Static_Offset_1_Sub:

			break;
			case Static_Offset_2_Sum:

			break;
			case AUTU_ACTION:
				
			break;
			case Static_Offset_3_Sum:

			break;
			case Static_Offset_3_Sub:

			break;
			case Clear_data:
				for (e = 0; e < 40; e++)
				{
					IIC_Buffer[e] = 0;
				}
			break;
			default :
				for (e = 0; e < 40; e++)
				{
					IIC_Buffer[e] = 0;
				}
			break;	
		}
		for (i = 0; i < 40; i++)
		{
			IIC_Buffer[i] = 0;
		}
	}
	else
	{
		I2C_Error();
	}
	IIC2_Config();  //每次数据传送完后,重新配置I2C,下次才能正确接收数据; 去掉IO配置
}
	

/**
  * @brief  IIC中断从机发送地址函数函数.
	* @discrib 进入中断后从机发送地址匹配，同时在里面发送了数据帧帧头
  * @param  
  * @retval Check 被更新为0;
  */
void IIC_EV_SALVE_TRANS_ADDR(void) //
{
	I2C_SendData(I2C2,0xfe);
	Check = 0;
}
unsigned char float2byte[4];
/**
  * @brief  IIC中断从机发送数据函数函数.
	* @discrib 再发送过程中通过Count自减来计数已经发送的数据
  * @param  
  * @retval 
  */
void IIC_EV3_SALVE_TRANS(void)
{

	if (Count == 1)
	{
		I2C_SendData(I2C2,0xfa);
		Count--;
	}
	
	if (Count == 2)
	{
		I2C_SendData(I2C2,Check);
		Count--;
	}
	
	if (Count > 2)
	{
				I2C_SendData(I2C2,Bottom_Data[Start_Add]);
				Check=checkCRC(Check,Bottom_Data[Start_Add]);
				Count--;

				Start_Add++;
	}
	if (Count == 0)
	{
		IIC_Reg_Flag = FLAG_RECV_REG_ADDR;
		Start_Add = 0;
	}
}
/***************************************************IIC通讯程序结束*************************************************/
//#define IMUDATASIZE 24
//unsigned char Sensor_imudata[IMUDATASIZE];
//void IMUParameterGet(struct Sensor_Parameter para, u8 *addr)
//{
//    IICreadBytes(para.devID, para.index, para.num, addr);
//}



/***************************************************传感器数据串口发送至上位机***************************************/
/*
*函数名称：SensorData2Raspi
*上传协议: 0xca 0xac num index data ... data ... crc 0x0b
*协议说明: 帧头      
*     reg: 0x00-IMU 0x01-GPS 0X02-I 0X03-V
*/
void SensorData2Raspi(struct Sensor_Parameter para, unsigned char *box)
{
    unsigned char i;
    unsigned char sum;
    
    USART2_SendByte('c');
    USART2_SendByte('a');
    para.num = 8;
    USART2_SendByte(para.num + 2);
    USART2_SendByte(para.index);
    for (i = 0; i < para.num; i++)
    {
        USART2_SendByte(box[i]);
        sum += box[i];
    }
    USART2_SendByte(0xaa);
    USART2_SendByte('b');
}


/***************************************************传感器数据串口发送至上位机***************************************/
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

signed short OutData[4]; 
void OutPut_Data(void)
{
    int temp[4] = {0};
    unsigned int temp1[4] = {0};
    unsigned char databuf[10] = {0};
    unsigned char i;
    unsigned short CRC16 = 0;
    for(i=0;i<4;i++)
    {
        temp[i]  = (int)OutData[i];
        temp1[i] = (unsigned int)temp[i];
    }

    for(i=0;i<4;i++)
    {
        databuf[i*2]   = (unsigned char)(temp1[i]%256);
        databuf[i*2+1] = (unsigned char)(temp1[i]/256);
    }

    CRC16 = CRC_CHECK(databuf,8);
    databuf[8] = CRC16%256;
    databuf[9] = CRC16/256;

    for(i=0;i<10;i++)        
    {
        USART2_SendByte((char)databuf[i]);
    }
}

/**
  * @brief  步进电机正反转控制
	* @discrib
* @param  
  * @retval 
  */ 
void Step_Go(signed int passive, signed int negtive)
{

}

/**
    * @brief    水泵控制板控制命令发送
    * @discrib  
    * @param    输入参数length为中心调节步进电机往复运动距离
    * @retval 
  */
void Commond2Drift(signed int volume)
{
    unsigned char num;
    unsigned char index = 0x0f;
    unsigned char sum = 0x00;
    
    UART4_SendByte('c');
    UART4_SendByte('a');
    UART4_SendByte('1');
    UART4_SendByte('0');
    UART4_SendByte('0');
    UART4_SendByte('f');
    
    num = volume / 10;
    UART4_SendByte('0' + num);
//    num = volume % 100 / 10;
//    UART4_SendByte('0' + num);
    num = volume % 10;
    UART4_SendByte('0' + num);
    
    UART4_SendByte('0');
    UART4_SendByte('0');
    UART4_SendByte('0');
    UART4_SendByte('b');
}

/**
    * @brief    滑翔机运动模式
    * @discrib  
    * @param    输入参数length为中心调节步进电机往复运动距离，time为吸水排水控制时间
    * @retval 
  */
void MotionMode(signed int length, unsigned int time)
{

}

/**
    * @brief    滑翔机运动模式
    * @discrib  
    * @param   输入编号为运动模式 
    * @retval 
  */

void GliderMotion(void)
{
    unsigned char i;
    switch(ModeIndex)
    {
        case 1:
            MotionMode(1600, 10000);
            break;
        case 2:
            MotionMode(2500, 10000);
            break;
        case 3:
            MotionMode(3300, 10000);
            break;
        case 4:
            MotionMode(4000, 10000);
            break;
        case 5:
            MotionMode(4500, 10000);
            break;
        case 6:
            MotionMode(5000, 10000);
            break;
        default:

            ModeIndex = 0;
            break;
    }
}

//struct GliderDataStruct 
//	
//void SendPara2Glider(void)
//{
//	USART1_SendByte(0xca);
//	USART1_SendByte(0xac);
//	USART1_SendByte(2+2*7+2);
//	USART1_SendByte(0x03);
//	
//	
//}





