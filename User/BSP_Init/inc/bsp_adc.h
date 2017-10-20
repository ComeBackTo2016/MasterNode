#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

#define BOARD_CURRENT 7
#define BOARD_VOLTAGE 6
#define BOARD_IR1	  0
#define BOARD_IR2     1
#define BOARD_FORCE1  2
#define BOARD_FORCE2  3
#define BOARD_FORCE3  4
#define BOARD_FORCE4  5

void ADC1_Init(void);
void ADC_Fliter(void);



#endif /* __ADC_H */

