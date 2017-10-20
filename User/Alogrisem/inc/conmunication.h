#ifndef __CONMUNICATION_H
#define	__CONMUNICATION_H

#include "stm32f10x.h"
#include "stm32f10x_can.h"

#define FrameID_W_DriverWrite 0x1300
#define FrameID_R_DriverMotion 0x1301
#define FrameID_R_DriverCapcity 0x1302
#define FrameID_R_WQSRead 0x1321
#define FrameID_W_GliderWrite	0x1330
#define FrameID_R_GliderRead	0x1331
#define FrameID_Deepth	0x1332
#define FrameID_W_Tail	0x1333
#define FrameID_R_Tail	0x1334

union float2char
{
	float num;
	unsigned char byte[4];
};
union int2char
{
	int num;
	unsigned char byte[2];
};

typedef enum
{
    Volt_12 = 12,
    Volt_24 = 24,
}VoltageClass;

typedef enum
{
		DriverFrameWrite = FrameID_W_DriverWrite,
    DriverFrameMotion = FrameID_R_DriverMotion,
    DriverFrameCapacity = FrameID_R_DriverCapcity,
}DriverFrameID;

struct DriverDataStruct
{
	VoltageClass Volt;
	DriverFrameID Dfi;
	int Volocity;
	float Kp;
	float Ki;
	unsigned char Tc;
};

typedef enum
{
		WQSFrameWrite = 0x1320,
    WQSFrameRead  = 0x1321,
}WQSFrameID;

typedef enum
{
		WQSPH = 0X01,
    WQSORP  = 0X02,
		WQSEC = 0X04, //0000 0100
		WQSTUR = 0X08,//0000 1000
		WQSALL = 0X00
}WQSDataCH;

struct WQSDataStruct
{
	WQSFrameID WQSFi;
	WQSDataCH WQSchannel;
	int iPH;
	float fPH;
	int iORP;
	float fORP;
	int iEC;
	float fEC;
	int iTurbity;
	float fTurbity;
	float Tempreture;
	int iSampling;
};

typedef enum
{
		GliderFrameWrite = 0x1330,//*
    GliderFrameRead  = 0x1331,
}GliderFrameID;
typedef enum
{
		GliderAng = 0x01,
    GliderTim  = 0X02,
		GliderDeep = 0X04,
		GliderTurbine = 0x08,//*
		
}GliderDataCH;
struct GliderDataStruct
{
	GliderFrameID GLIDERFi;
	GliderDataCH Gliderchannel;
	int16_t angSink;
	int16_t angFloat;
	int16_t timSink;
	int16_t timFloat;
	int16_t deepInit;
	int16_t deepEnd;
	int16_t keepFloat;
	int16_t keepSink;
	int16_t leftTurbine;
	int16_t rightTurbine;
	int16_t angRudder;
};

typedef enum 
{
	TailFrameWrite = 0x1333,
	TailFrameRead  = 0x1334
}TailFrameID;
typedef enum
{
		TailAng = 0x00,
}TailDataCH;
struct Tail_Rudder
{
	TailFrameID TAILFi;
	TailDataCH Tailchannel;
	float AngTail;
};

struct MCU2Raspi
{
	unsigned char FrameHeadI;
	unsigned char FrameHeadII;
	unsigned char FrameIDI;
	unsigned char FrameIDII;
	unsigned char FrameTail;
	unsigned char DataSum;
	unsigned char DataLength;
};

unsigned char DriverReadWriteData(struct DriverDataStruct *DriverSendData);
unsigned char WQSReadWriteData(struct WQSDataStruct *WQSSendData);
unsigned char GliderReadWriteData(struct GliderDataStruct *GliderSendData);
unsigned char TailReadWriteData(struct Tail_Rudder *TailData);
void MatserHandler(void);
void DriverSalveHander(void);
void GliderSalveHander(void);
void WQS2RaspberryPi(void);
void Glider2RaspberryPi();

#endif