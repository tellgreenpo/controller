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

  // Check this tutorial : https://deepbluembedded.com/stm32-pwm-example-timer-pwm-mode-tutorial/

 void MyTimer_PWM(TIM_TypeDef * Timer, char Channel){
    // Creating mask
    uint8_t mask;
    /*
    * bit 0 1
    * This bit-field defines the direction of the channel (input/output) as well as the used input.
    * 00: CC1 channel is configured as output
    */
    mask = 0U ;
    /*
    * bit 2 - OC1FE
    * An active edge on the trigger input acts like a compare match on CC1 output. Then, OC
    * is set to the compare level independently from the result of the comparison. Delay to sample
    * the trigger input and to activate CC1 output is reduced to 3 clock cycles. OCFE acts only if
    * the channel is configured in PWM1 or PWM2 mode.
    */
    mask |= 0x01 << 2;
    /*
    * bit 3
    * Output compare 1 preload NVIC_EnableIR
    * The PWM mode can be used without validating the preload register only in one-pulse mode
    * (OPM bit set in TIMx_CR1 register). Else the behavior is not guaranteed.
    */
    mask |= 0x01 << 3;
    /*
    *  4 5 6 bit
    * 110 : PWM mode 1 ==> In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
    * 111 PWM mode 2 ==> In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active.
    *  Active ==> OC1REF = '1'
    */
    mask |= ((0x01 << 2) | (0x01 << 1) | 0x0) <<4 ;
    /*
    * bit 7
    * On laisse a 0 parce que jsp on verra
    */

    // Selon ST auto reload preload enable in ARPE bit in CR1
    Timer->CR1 |= 0x01 << 7;

    // Init all UG bit in EGR register
    Timer->EGR |= 0x1;

    // Enable output and polarity config
    // CCER bit 0 ==> output signal to output pin
    // CCER bit 1 ==> output polarity {0 : active high}

    // Enable capture/compare interrupts? TIMx_DIER register bit 1-4 for channels? ==> No DIER is for interrupt
    if (Channel == 1){
      Timer->CCER |= 0x01;
      Timer->CCMR1 |= mask;
    }else if(Channel == 2){
      Timer->CCER |= 0x01 << 4;
      Timer->CCMR1 |= mask<<8;
    }else if (Channel == 3){
      Timer->CCER |= 0x01 << 8;
      Timer->CCMR2 |= mask;
    }else if(Channel == 4){
      Timer->CCER |= 0x01 << 12;
      Timer->CCMR2 |= mask<<8;
    }

    /*
    Indication de la part de ST :}
    OCxM ==> PWM mode
    OCxPE ==> enable
    auto reload preload register ==> ARPE bit set in TIMx_CR1
    Init all UG bit in EGR registers
    Output enable:
      CCxE
      CCxNE
      MOE
      OSSI
      OSSR
      in TOMx_CCER and TIMx_BDTR

    Problem ==> BDTR register only foor advanced timers wich are independent from Gerenal Purpose Timers
    so how do we do this?
    */

  }

  // Update CCRx

	void setCycle_PWM(TIM_TypeDef * Timer, char Channel, int cycle) {

		if (Channel == 1) {
			Timer->CCR1 = (Timer->ARR + 1) * (Timer->PSC + 1) *(1-cycle/100) ;
		} else if (Channel==2) {
			Timer->CCR2 = (Timer->ARR + 1) * (Timer->PSC + 1) *(1-cycle/100) ;  ;
		} else if (Channel==3) {
			Timer->CCR3 = (Timer->ARR + 1) * (Timer->PSC + 1) *(1-cycle/100) ;  ;
		} else if (Channel==4) {
			Timer->CCR4 = (Timer->ARR + 1) * (Timer->PSC + 1) *(1-cycle/100) ;  ;
		}
}
