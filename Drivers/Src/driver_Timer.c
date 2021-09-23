#include "stm32f10x.h"
#include "MYTIMER_H"

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
  Timer->Timid->PSC = Timer->PSC;
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

  void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio){
    // enable IT Timer overflow
    Timer->TimId->DIER |= 0x1;
    // les codes IRQ negatifs sont pour le systeme interne du processeur
    // les codes IRQ positifs sont pour ce qui est externe
    // NVIC_EnableIRQ(...) function in startup
    // NVIC_SetPriority(...) function in startup
    if(Timer->TimId == TIM1){
  		NVIC_EnableIRQ(TIM1_UPDATE_INTERRUPT_POS);
      NVIC_SetPriority(TIM1_UPDATE_INTERRUPT_POS,Prio);
  	}else if (Timer->TimId == TIM2){
  		NVIC_EnableIRQ(TIM2_GENERAL_INTERRUPT_POS);
      NVIC_SetPriority(TIM2_GENERAL_INTERRUPT_POS,Prio);
    }else if (Timer->TimId == TIM3) {
  		NVIC_EnableIRQ(TIM3_GENERAL_INTERRUPT_POS);
      NVIC_SetPriority(TIM3_GENERAL_INTERRUPT_POS,Prio);
  	}else if (Timer->TimId == TIM4){
  		NVIC_EnableIRQ(TIM4_GENERAL_INTERRUPT_POS);
      NVIC_SetPriority(TIM4_GENERAL_INTERRUPT_POS,Prio);
  	};
  }

  // Create the handlers for each IT
  // redefine handlers from the startup file
  // handler is void->void
  // _Vectors table already exists
  void TIM1_IRQHandler(void){
    /*TODO*/
    // reset bit to close the interrupt request
    TIM1->DIER &= 0x0 << 8;
  };

  void TIM2_IRQHandler(void){
    /*TODO*/
    // reset bit to close the interrupt request
    TIM2->DIER &= 0x0 << 8;
  };

  void TIM3_IRQHandler(void){
    /*TODO*/
    // reset bit to close the interrupt request
    TIM3->DIER &= 0x0 << 8;
  };

  void TIM4_IRQHandler(void){
    /*TODO*/
    TIM4->DIER &= 0x0 <<8;
  };
}
