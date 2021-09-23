#include "stm32f10x.h"
#include "MYTIMER_H"

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer){
  if      (Timer->TimId == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->ARR = Timer->ARR;
    TIM1->PSC = Timer->PSC;
	}else if (Timer->TimId == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->ARR = Timer->ARR;
    TIM2->PSC = Timer->PSC;
  }else if (Timer->TimId == TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->ARR = Timer->ARR;
    TIM3->PSC = Timer->PSC;
	}else if (Timer->TimId == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    TIM4->ARR = Timer->ARR;
    TIM4->PSC = Timer->PSC;
	};
}
