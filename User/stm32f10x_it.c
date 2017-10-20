

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "init.h"
#include "stdio.h"
#include "cpg.h"
#include "conmunication.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern float theta[3];
extern float Pectoral_Theta[2];
extern void TimingDelay_Decrement(void);
extern signed short OutData[4]; 
extern __IO uint32_t flag;
extern CanRxMsg RxMessage;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();	
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @brief  This function handles TIM6 interrupt request.
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void)// 中断时间100ms
{	

	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
		{	
/*****************MY_APP_CODE*******************/

/********************OVER***********************/
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update); 
		}
}

//#define Tailout1 TIM8->CCR2
//#define Tailout2 TIM8->CCR3
//#define Tailout3 TIM8->CCR4

//#define Pectout1 TIM1->CCR1
//#define Pectout2 TIM1->CCR4

/**
  * @brief  This function handles TIM6 interrupt request.
  * @param  None
  * @retval None
  */
//unsigned int cnt = 0;
void TIM4_IRQHandler(void)// 中断时间1ms
{	
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		{	
//            cnt++;
//            if (cnt > 2000)
//            {
//                LED_Ligth(1);
//            }
//            else
//            {
//                LED_Ligth(0);
//            }
//            if (cnt == 4000) cnt = 0;
/*****************MY_APP_CODE*******************/
        /* 躯干CPG计算及输出 */
        //PBout(9) =0;
		cpg_run();
		PWMoutput1 = (uint16_t)(1500 + (2000*theta[0])/3.1415);
		PWMoutput2 = (uint16_t)(1500 + (2000*theta[1])/3.1415);
		PWMoutput3 = (uint16_t)(1500 + (2000*theta[2])/3.1415);
		/* 胸鳍CPG计算及跟新(使用PWM通道TIM2-1 TIM2-2) */
        //PBout(9) =1;    
		Pectoral_CPG_Calculate();
        PWMoutput5 = (uint16_t)(1500 + (2000*Pectoral_Theta[0])/3.1415);
        PWMoutput6 = (uint16_t)(1500 + (2000*Pectoral_Theta[1])/3.1415);
        /* 仿真波形打印 */    
//		OutData[0] = (int)((Pectoral_Theta[0] / 3.1415) * 180);
//		OutData[1] = (int)((Pectoral_Theta[1] / 3.1415) * 180);
//		OutData[2] = 0;//(int)((theta[2] / 3.1415) * 180);
//		OutData[3] = 0;    
/********************OVER***********************/
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
		}
}


/**************************************************************************
函数功能:定时器1编码中断函数
入口参数:无
返 回 值:无
作    者:何宇帆(2016-01-25)
**************************************************************************/
void TIM1_IRQHandler()
{
	u16 tsr;
	tsr=TIM1->SR;	
	if(tsr&0X0001)
	{
																				
	}				   
	TIM1->SR&=~(1<<0);
}

//int32_t CNT_ENC1_TIM1 = 0;
//int32_t CNT_ENC2_TIM4 = 0;
//int32_t CNT_ENC3_TIM8 = 0;

/**************************************************************************
函数功能:定时器4编码中断函数
入口参数:无
返 回 值:无
作    者:何宇帆(2016-01-25)
**************************************************************************/
//void TIM4_IRQHandler()
//{
//	u16 tsr;
//	tsr=TIM4->SR;	
//	if(tsr&0X0001)
//	{
//																				
//	}				   
//	TIM4->SR&=~(1<<0);
//}
/**************************************************************************
函数功能:定时器8编码中断函数
入口参数:无
返 回 值:无
作    者:何宇帆(2016-01-25)
**************************************************************************/
void TIM8_IRQHandler()
{
	u16 tsr;
	tsr=TIM8->SR;	
	if(tsr&0X0001)
	{
																				
	}				   
	TIM8->SR&=~(1<<0);
}
/**************************************************************************
函数功能:串口读取IMU数据包
入口参数:无
返 回 值:无
作    者:何宇帆(2016-01-25)
**************************************************************************/
void USART1_IRQHandler(void)
{
	uint8_t ch;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
			ch = USART_ReceiveData(USART1);
//		USART2_SendByte(ch);
			FrameGet(ch);
//			USART1_SendByte(ch);
	} 
}	

/**************************************************************************
函数功能:串口读取数据包
入口参数:无
返 回 值:无
作    者:何宇帆(2016-01-26)
**************************************************************************/
void USART2_IRQHandler(void)
{
	uint8_t ch;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{ 	
		ch = USART_ReceiveData(USART2);
//		USART2_SendByte(ch);
        FrameGet(ch);
		
	} 
}

/**************************************************************************
函数功能:串口读取数据包
入口参数:无
返 回 值:无
作    者:何宇帆(2016-01-26)
**************************************************************************/
void I2C2_EV_IRQHandler(void)
{
	unsigned char iic_buffer;
//	unsigned char i = 0;
	static unsigned char count = 0;
	static unsigned char iic_read_flag = 0;
	static unsigned char iic_reg = 0;
	static unsigned char iic_reg_flag = 0;
	
	switch(I2C_GetLastEvent(I2C2))
	{
		case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED:
			/*主机起始信号触发中断，不进行操作*/
			break;
		case I2C_EVENT_SLAVE_BYTE_RECEIVED:
			IIC_EV_SALVE_RECV(iic_buffer);
			break;
		case I2C_EVENT_SLAVE_STOP_DETECTED:
			I2C_ClearFlag(I2C2 , I2C_FLAG_STOPF);
			I2C_ITConfig( I2C2, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR, DISABLE );
			IIC_EV_SALVE_STOP();
			break;
		case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED:
			IIC_EV_SALVE_TRANS_ADDR();
			break;
		case I2C_EVENT_SLAVE_BYTE_TRANSMITTING:
			IIC_EV3_SALVE_TRANS();
			break;
		default:
			IIC2_Config();
		break;
	}
}

void I2C2_ER_IRQHandler(void)
{
    switch (I2C_GetLastEvent(I2C2))
    {   	
        case I2C_EVENT_SLAVE_ACK_FAILURE:
             IIC2_INIT();
        break;
        default:
        break;
	}
}

/**************************************************************************
函数功能:事件函数均为IIC2事件函数,IIC1事件函数还未更新
入口参数:无
返 回 值:无
作    者:何宇帆(2016-01-26)
**************************************************************************/
void I2C1_EV_IRQHandler(void)
{
	unsigned char iic_buffer;
//	unsigned char i = 0;
	static unsigned char count = 0;
	static unsigned char iic_read_flag = 0;
	static unsigned char iic_reg = 0;
	static unsigned char iic_reg_flag = 0;
	
	switch(I2C_GetLastEvent(I2C1))
	{
		case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED:
			/*主机起始信号触发中断，不进行操作*/
			break;
		case I2C_EVENT_SLAVE_BYTE_RECEIVED:
			IIC_EV_SALVE_RECV(iic_buffer);
			break;
		case I2C_EVENT_SLAVE_STOP_DETECTED:
			I2C_ClearFlag(I2C1 , I2C_FLAG_STOPF);
			I2C_ITConfig( I2C1, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR, DISABLE );
			IIC_EV_SALVE_STOP();
			break;
		case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED:
			IIC_EV_SALVE_TRANS_ADDR();
			break;
		case I2C_EVENT_SLAVE_BYTE_TRANSMITTING:
			IIC_EV3_SALVE_TRANS();
			break;
		default:
			IIC1_Config();
		break;
	}
}

void I2C1_ER_IRQHandler(void)
{
    switch (I2C_GetLastEvent(I2C1))
    {   	
        case I2C_EVENT_SLAVE_ACK_FAILURE:
             IIC1_INIT();
        break;
        default:
        break;
		}
}

/**
  * @}
  */ 
void USB_LP_CAN1_RX0_IRQHandler(void)
{
		MatserHandler();
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
