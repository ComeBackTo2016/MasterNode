#ifndef __INIT_H
#define	__INIT_H

#include <stdio.h>
#include <string.h>

#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_spi_flash.h"
#include "bsp_adc.h"
#include "bsp_led.h" 
#include "timer.h"
#include "uart.h"
#include "encode.h"
#include "IOI2C.h"
#include "CPG.h"
#include "IMU.h"
#include "Control.h"
#include "AHRSREG.h"
#include "can.h"

#include "sdio_sdcard.h"
#include "ff.h"			/* Declarations of FatFs API */
#include "diskio.h"		/* Declarations of disk I/O functions */


#define JDQ_Tail_SW(n) PBout(15) = n
#define JDQ_Pec_SW(n) PBout(14) = n
#define Power_Switch(n) PAout(15) = n
#define u8 unsigned char
extern float IMUData[];
extern float TempWQS[4], TempGlider[9];

extern FATFS fs;       //SD���ļ�ϵͳ����
extern FRESULT res;  
extern FIL file;                       
extern UINT br,bw;
extern u8 fatbufr[4096];//SD�������ݻ�����

void UART_INIT(void);

void NVIC_of_All(void);

void PWM_INIT(void);
void ENCODE_INIT(void);
void TIMER_INIT(void);


void IIC2_INIT(void);
void IIC2_Config(void);
void IIC2_NVIC_Config(unsigned char Pre_EV, unsigned char Pre_ER);
void IIC1_INIT(void);
void IIC1_Config(void);
void IIC1_NVIC_Config(unsigned char Pre_EV, unsigned char Pre_ER);

void LED_Config(void);
void Common_GPIO_Config(void);
void Exit_Config(void);
void STEP_MOTOR_INIT(void);
//void IIC2_Config(void);

//����Ϊ��ຯ��
void WFI_SET(void);		//ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(u32 addr);	//���ö�ջ��ַ





#endif /* __INIT_H */
