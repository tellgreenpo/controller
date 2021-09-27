#include "stm32f10x.h" 
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

MyGPIO_Struct_TypeDef GPIO_Struct ; 
MyTimer_Struct_TypeDef TimerTest ;

void callback(void) {
	
	MyGPIO_Toggle(GPIO_Struct.GPIO, GPIO_Struct.GPIO_Pin) ; 
	
}


int main (void) 
{
	/*
	// Configuration LED
	GPIO_Struct.GPIO = GPIOC ; 
	GPIO_Struct.GPIO_Pin = 10 ;
	GPIO_Struct.GPIO_Conf = Out_Ppull ; 
	
	MyGPIO_Init(& GPIO_Struct) ; 
	

	// Test périodicité du timer TIM2
	TimerTest.TimId = TIM2 ; 
	TimerTest.ARR = 6000-1 ; 
	TimerTest.PSC = 6000-1 ; 
	MyTimer_Base_Init(& TimerTest) ; 
	
	MyTimer_Base_Start(TimerTest.TimId) ; 
	
	MyTimer_ActiveIT(TimerTest.TimId, 3, callback) ; */ 
		
	// Test PWM // 
	TimerTest.TimId = TIM2 ; 
	TimerTest.ARR = 36-1 ; 
	TimerTest.PSC = 20-1 ; 
	MyTimer_Base_Init(& TimerTest) ; 
	
	
	// Configuration Sortie
	GPIO_Struct.GPIO = GPIOA ; 
	GPIO_Struct.GPIO_Pin = 1 ;
	GPIO_Struct.GPIO_Conf = AltOut_Ppull ; 
	MyGPIO_Init(& GPIO_Struct) ;
	
	MyTimer_PWM(TimerTest.TimId, 3) ; 
	
	setCycle_PWM(TimerTest.TimId, 3, 50) ;
	
	MyTimer_Base_Start(TimerTest.TimId) ;
	
	
	while(1) ;
	
}

