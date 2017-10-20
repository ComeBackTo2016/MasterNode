#include "init.h"
#include <stdio.h>
#include <string.h>
//********************************************************************************  
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

static void IIC2_NVIC_Config(unsigned char Pre_EV, unsigned char Pre_ER);

void UART_INIT(void)				
{
  UART1_PA09_PA10_Config();
  UART2_PA02_PA03_Config();
  //UART4_PC10_PC11_Config();
  //UART5_PC12_PD02_Config();
  //UART3_PB10_PB11_Config();
}

void NVIC_of_All(void)
{
    /* ����NVIC������2,��ռ���ȼ�0-1 ��Ӧ���ȼ�0-7 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
	/*�ж����ȼ�������Ҫ���ݳ������������������*/
//	IIC2_NVIC_Config(0, 0);
	UART1_NVIC_Config(0, 1);
    UART2_NVIC_Config(0, 4);
//	Timer4_NVIC_Config(0, 2);
}

void PWM_INIT(void)					
{
	/*��ʼ��TIM��Ӧ����ΪPWMģʽ����ʼ����Ӧ���ż��ж�����;T = 2000000/frequency - 1*/
	TIM3_PWM_PA6_PA7_PB0_PB1_Config(20000, 72);//enable 1 2 3 ch       output:10K   range:0-100
//	TIM5_PWM_PA0_PA1_PA2_PA3_Config(100, 72);//enable 1 2 ch
//	TIM2_PWM_PA0_PA1_PA2_PA3_Config(20000, 72);//enable 1 2 ch  		 output:1K   range:0-1000 liner change
//    TIM8_PWM_PC6_PC7_PC8_PC9_Config(20000, 72);//enable 234ch
//    TIM1_PWM_PA8_PA9_PA10_PA11_Config(20000, 72);//enable 14ch
}

void ENCODE_INIT(void)		
{
	TIM1_EncoderMode_PA8_PA9_Config();
	TIM4_EncoderMode_PD12_PD13_Config();
	TIM8_EncoderMode_PC6_PC7_Config();
}

void TIMER_INIT(void)				
{
	/*��ʱʱ�䣺72M/72*20000us=20ms*/
	Timer4_Config(1000, 72);		//10ms
}
/* Time:2017-01-06 */
void IIC1_Config(void)
{
	I2C_InitTypeDef I2C_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
	// I2C���踴λ.
	RCC_APB1PeriphResetCmd( RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB1PeriphResetCmd( RCC_APB1Periph_I2C1, DISABLE);
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	/*����I2C2�豸������Ϊ���ÿ�©���*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;    																							 //Ϊ������������п����𻵶˿ڣ�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	// I2C����.
	I2C_DeInit(I2C1);
	// I2C2 configuration ---------------------------------------------
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x70;      
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 200000;//400000;

	I2C_Cmd(I2C1, ENABLE );

	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_GeneralCallCmd(I2C1,ENABLE);

	I2C_ITConfig( I2C1, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR, ENABLE );
}
void IIC2_Config(void)
{
	I2C_InitTypeDef I2C_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
	// I2C���踴λ.
	RCC_APB1PeriphResetCmd( RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB1PeriphResetCmd( RCC_APB1Periph_I2C2, DISABLE);
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	/*����I2C2�豸������Ϊ���ÿ�©���*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;    																							 //Ϊ������������п����𻵶˿ڣ�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	// I2C����.
	I2C_DeInit( I2C2 );
	// I2C2 configuration ---------------------------------------------
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x70;      
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 200000;//400000;

	I2C_Cmd(I2C2, ENABLE );

	I2C_Init(I2C2, &I2C_InitStructure);
	I2C_GeneralCallCmd(I2C2,ENABLE);

	I2C_ITConfig( I2C2, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR, ENABLE );
}
/* TIME:2017-01-06 */
void IIC1_NVIC_Config(unsigned char Pre_EV, unsigned char Pre_ER)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	 	
	NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Pre_EV;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Pre_ER;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//some question
void IIC2_NVIC_Config(unsigned char Pre_EV, unsigned char Pre_ER)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	 	
	NVIC_InitStructure.NVIC_IRQChannel = I2C2_EV_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Pre_EV;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = I2C2_ER_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Pre_ER;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*IIC1��ʼ������*/
void IIC1_INIT(void)
{
	IIC1_Config();
    IIC1_NVIC_Config(0, 0);
}
/*IIC��ʼ������*/
void IIC2_INIT(void)
{
	IIC2_Config();
    IIC2_NVIC_Config(0, 0);
}



/* LED��ʼ������ */
void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);					
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                        																								 //Ϊ������������п����𻵶˿ڣ�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
}

void Exit_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* config the extiline() clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
												  
    /* ����P[A|B|C|D|E]13Ϊ�ж�Դ */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* EXTI line gpio config() */	
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 |GPIO_Pin_13;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // ��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* EXTI line() mode config */
    GPIO_EXTILineConfig(RCC_APB2Periph_GPIOB, GPIO_PinSource12); 
    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); 
}


void Common_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
    /* IO��ʱ�ӳ�ʼ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);
    /* ����JTAG�ӿ�������ͨIO���� */        
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    
    /* �������IO��ʼ�� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                        																								 //Ϊ������������п����𻵶˿ڣ�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;      
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* �̵������� IO��ʼ�� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14;      
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

