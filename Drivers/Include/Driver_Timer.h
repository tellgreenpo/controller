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
				*				@Note -> Fonction � lancer syst�matiquement avant d'aller plus en d�tail dans les
								conf plus fines (PWM,codeurs inc...)
*/

void MyTimer_Base_Init( MyTimer_Struct_TypeDef * MyTimer ) ;


/*
*************************************************************************
				* @brief
				*				@param -> - TIM_TypeDef * Timer : Timer concerne
													- char Prio : de 0 a 15
				*				@Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
*/

void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio);

#define MyTimer_Base_Start(Timer) (Timer->TimId->CR1 |= 0x1)
#define MyTimer_Base_Stop(Timer)	(Timer->TimId->CR1 |= 0x0)

// TIM1 Update interrupt postition 25
#define TIM1_UPDATE_INTERRUPT_POS 25;
// TIM2 interrupt general position 28
#define TIM2_GENERAL_INTERRUPT_POS 28;
// TIM3 interrupt general position 29
#define TIM3_GENERAL_INTERRUPT_POS 29;
// TIM4 interrupt general position 30
#define TIM4_GENERAL_INTERRUPT_POS 30;

#endif
