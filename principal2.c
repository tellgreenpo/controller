#include "stm32f10x.h"
#include "Driver_Timer.h"
#include "Driver_GPIO.h"

MyGPIO_Struct_TypeDef GPIO_Struct ;

void callback(void) {
	GPIO_Struct.GPIO = GPIOC ;
	GPIO_Struct.GPIO_Pin = 10 ;
	GPIO_Struct.GPIO_Conf = Out_Ppull ;

	MyGPIO_Init(& GPIO_Struct) ;

	MyGPIO_Toggle(GPIO_Struct.GPIO, GPIO_Struct.GPIO_Pin) ;

}


int main (void)
{

	// Test périodicité du timer TIM1
	MyTimer_Struct_TypeDef TimerTest ;
	TimerTest.TimId = TIM1 ;
	TimerTest.ARR = 6000-1 ;
	TimerTest.PSC = 6000-1 ;

	MyTimer_Base_Init(& TimerTest) ;

	MyTimer_Base_Start(TimerTest.TimId) ;
	

	MyTimer_ActiveIT(TimerTest.TimId, 3, callback) ;


	while(1) ;

}
