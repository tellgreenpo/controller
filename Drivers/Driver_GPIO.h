#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

typedef struct{
  GPIO_TypeDef * GPIO;
  char GPIO_Pin; //1->15
  char GPIO_Conf; // voir ci-dessous
} MyGPIO_Struct_TypeDef;

#define In_Floating 0x4
#define In_PullDown 0x8 // ODR?
#define In_PullUp 0x8 // ODR?
#define In_Analog 0x0
#define Out_Ppull 0x1
#define Out_OD 0x5
#define AltOut_Ppull 0x9
#define AltOut_OD 0xD
void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) ;
int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ) ; // renvoie 0 ou autre chose d i f f e r e n t de 0
void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;

#endif
