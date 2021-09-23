#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

typedef struct{
	TIM_TypeDef * TimId; // TIM1 a TIM4
	unsigned short ARR;
	unsigned short PSC;
}MyTimer_Struct_TypeDef;

/*
*************************************************************************
				* @brief
				*				@param -> Parametre sous forme d'une structure (son adresse) contenant les
								informations de base
				*				@Note -> Fonction à lancer systématiquement avant d'aller plus en détail dans les
								conf plus fines (PWM,codeurs inc...)
*/

void MyTimer_Base_Init( MyTimer_Struct_TypeDef * MyTimer ) ;

#define MyTimer_Base_Start(Timer) (Timer->TimId->CR1 |= 0x1)
#define MyTimer_Base_Stop(Timer)	(Timer->TimId->CR1 |= 0x0)
#endif