#include "stm32f10x.h"
#include "Driver_Timer.h"


// 4 pointeurs pour les 4 timers
void (* pFuncTIM1) (void);
void (* pFuncTIM2) (void);
void (* pFuncTIM3) (void);
void (* pFuncTIM4) (void);


void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer){
  if(Timer->TimId == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}else if (Timer->TimId == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  }else if (Timer->TimId == TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}else if (Timer->TimId == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	};
  Timer->TimId->ARR = Timer->ARR;
  Timer->TimId->PSC = Timer->PSC;
}


  // vector table for IT

  // NVIC register to modify in order to enable
  // ISER ICER
  // ICPR IABR
  // IPR modify the first 4 bits to modify priority

  // TIM->DMA TIMx_DIER to notify interrupt
  // bits from 0 to 5 and 6 to enable interrupt request

  // bits from 8 to 12 and 14 go too 1 when corresponding interrupt happens


  /*
  Process to follow:
  Analyserle periph et reperer l'evenement a prendre en compte
  Trouver le numero et donc le vecteur associe de l'interruption  concernee
  Configurerles registres du periph pour valider en local l'envoi d'une demande d'interruption
  Fixer dans le NVIC la priorite de l'interruption
  Trouver le nom du Handler de l'interruption et ecrire une routine avec le meme prototype
  Effacer le bit du periph qui provoque le declenchement pendant cette routine
  */

  void MyTimer_ActiveIT(TIM_TypeDef * TimId, char Prio, void (*IT_function)(void)){
    // enable IT Timer overflow
    TimId->DIER |= 0x1;
    // les codes IRQ negatifs sont pour le systeme interne du processeur
    // les codes IRQ positifs sont pour ce qui est externe
    // NVIC_EnableIRQ(...) function in startup
    // NVIC_SetPriority(...) function in startup
    if(TimId == TIM1){
  		NVIC_EnableIRQ(TIM1_UP_IRQn);
      NVIC_SetPriority(TIM1_UP_IRQn,Prio);
      pFuncTIM1 = IT_function;
  	} else if (TimId == TIM2){
  		NVIC_EnableIRQ(TIM2_IRQn);
      NVIC_SetPriority(TIM2_IRQn,Prio);
      pFuncTIM2 = IT_function;
    } else if (TimId == TIM3) {
  		NVIC_EnableIRQ(TIM3_IRQn);
      NVIC_SetPriority(TIM3_IRQn,Prio);
      pFuncTIM3 = IT_function;
  	} else if (TimId == TIM4){
  		NVIC_EnableIRQ(TIM4_IRQn);
      NVIC_SetPriority(TIM4_IRQn,Prio);
      pFuncTIM4 = IT_function;
  	};
  }

	
	
	
	
	
  // Create the handlers for each IT
  // redefine handlers from the startup file
  // handler is void->void
  // _Vectors table already exists so just need to redefine
	
	
	
	  void TIM1_UP_IRQHandler(void){
    // reset bit to close the interrupt request
    TIM1->SR &= ~TIM_SR_UIF ; 
    if(pFuncTIM1 != 0){
      (*pFuncTIM1)();
    }
  }

	
	
	  void TIM2_IRQHandler(void){
    // reset bit to close the interrupt request
    TIM2->SR &= ~TIM_SR_UIF ;
    if(pFuncTIM2 != 0){
      (*pFuncTIM2)();
    }
  }
		
	


  void TIM3_IRQHandler(void){
    // reset bit to close the interrupt request
    TIM3->SR &= ~TIM_SR_UIF ;
    if(pFuncTIM3 != 0){
      (*pFuncTIM3)();
    }
  }

  void TIM4_IRQHandler(void){
    TIM4->SR &= ~TIM_SR_UIF ;
    if(pFuncTIM4 != 0){
      (*pFuncTIM4)();
    }
  }

