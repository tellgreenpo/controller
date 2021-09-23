#include "stm32f10x.h"
#include "MYTIMER_H"

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer){
  if      (Timer->TimId == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}else if (Timer->TimId == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  }else if (Timer->TimId == TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	}else if (Timer->TimId == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	};
	Timer->TimId->PSC = 0x176F; // 5999
	Timer->TimId->ARR = 0x176F; // 5999
}