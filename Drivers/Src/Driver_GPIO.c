#include "Driver_GPIO.h"
#include "stm32f10x.h"


void GPIO_Init_Input_ODR(MyGPIO_Struct_TypeDef * GPIOStructPtr){
  if(GPIOStructPtr->GPIO_Conf == In_PullDown){
    GPIOStructPtr->GPIO->ODR &= 0x0 << GPIOStructPtr->GPIO_Pin;
    GPIOStructPtr->GPIO_Conf = 0x8;
  }else if (GPIOStructPtr->GPIO_Conf == In_PullUp){
    GPIOStructPtr->GPIO->ODR &= 0x0 << GPIOStructPtr->GPIO_Pin;
    GPIOStructPtr->GPIO->ODR |= 0x1 << GPIOStructPtr->GPIO_Pin;
    GPIOStructPtr->GPIO_Conf = 0x8;
  }
}


////////// FONCTION D'INITIALISATION //////////
void MyGPIO_Init (MyGPIO_Struct_TypeDef * GPIOStructPtr){
	
	// A MODIFIER !!!! //
  RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) | (0x01<<5);
	
  // Les pins 0 à 7 sont contrôlées par le registre CRL
  if (GPIOStructPtr->GPIO_Pin < 8){
    GPIO_Init_Input_ODR(GPIOStructPtr);
    GPIOStructPtr->GPIO->CRL &= ~(0xF << 4*GPIOStructPtr->GPIO_Pin);
    GPIOStructPtr->GPIO->CRL |= GPIOStructPtr->GPIO_Conf << 4*GPIOStructPtr->GPIO_Pin;
	// Les pins 8 à 15 sont contrôlées par le registre CRH
  }else{
    GPIO_Init_Input_ODR(GPIOStructPtr);
    GPIOStructPtr->GPIO->CRH &= ~(0xF << 4*(GPIOStructPtr->GPIO_Pin-8));
    GPIOStructPtr->GPIO->CRH |= GPIOStructPtr->GPIO_Conf << 4*(GPIOStructPtr->GPIO_Pin-8);
  }
}






////////// LECTURE DU REGISTRE IDR //////////
int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ){
  int res = 0;
  res = GPIO -> IDR & 0x01<<GPIO_Pin;
  return res;
}






////////// ECRITURE SUR LE REGISTRE ODR //////////
void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ){
	// Mettre à 1 le bit de l'ODR correspondant la pin GPIO_Pin
  GPIO->ODR |= 0x01 << GPIO_Pin;
}

void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ){
	// Mettre à 0 le bit de l'ODR correspondant la pin GPIO_Pin
  GPIO->ODR &= ~(0x01 << GPIO_Pin);
}






///////// INVERSION DE L'ETAT  //////////
void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ){
  // Créer masque
  char idrPin = 0x01 << GPIO_Pin;
  // mettre le contraire sur le ODR
  if (GPIO->IDR & idrPin) {
    MyGPIO_Reset(GPIO , GPIO_Pin );
  }else{
    MyGPIO_Set(GPIO ,GPIO_Pin);
  }
}
