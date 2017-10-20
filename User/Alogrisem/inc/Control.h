#ifndef _CONTROL_H__
#define _CONTROL_H__

//include your Headerfiles
#include "stm32f10x.h"
/* ����������Ĵ�����ַ */


/* �����������ϴ������������ʶ */

//include your Macro definitions

//#define IMUARRAYSIZE 26
//#define SENSORARRAYSIZE 100

//struct IMU_Parameter{
//    unsigned char devID;
//    unsigned char index;
//    unsigned char num;
//    unsigned char imuArray[IMUARRAYSIZE];
//};

struct Sensor_Parameter{
    /* ��������IIC��ַ */
    unsigned char devID;
    /* Ҫ��ȡ�����ݼĴ�����ַ */
    unsigned char index;
    /* Ҫ��ȡ�����ݳ��� */
    unsigned char num;
};

struct SerCommunication_Protocol{
    char headFrame;
    char secFrame;
    unsigned char dataLength;
    char index;
    char dataSum;
    char tailFrame;
};

union FLOAT2CHAR
{
	float num;
	unsigned char byte[4];
};

union SHORT2CHAR
{
	short int num;
	unsigned char byte[2];
};


void FrameCharGet(unsigned char data);
void FrameGet(unsigned char data);
void CommondProcess(void);
short CharToShort(unsigned char cData[]);

//void CharDataProcess(void);
void IOIIC_IMU_GPS_GET(struct Sensor_Parameter para);
void SensorData2Raspi(struct Sensor_Parameter para, unsigned char *box);

void IIC_EV_SALVE_RECV(unsigned char receive_data);
void IIC_EV_SALVE_STOP();
void IIC_EV_SALVE_TRANS_ADDR();
void IIC_EV3_SALVE_TRANS();

void GliderMotion(void);
void Step_Go(signed int passive, signed int negtive);
void Commond2Drift(signed int volume);
void OutPut_Data(void);
//include your externvariable

#endif
