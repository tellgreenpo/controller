#include "MYGPIO_H"

void GPIO_Init_Input_ODR(MyGPIO_struct_TypeDef * GPIOStructPtr){
  if(GPIOStructPtr->GPIO_Conf == In_PullDown){
    GPIOStructPtr->GPIO->ODR &= 0x0 << GPIOStructPtr->GPIO_Pin;
    GPIOStructPtr->GPIO_Conf = 0x8;
  }else if (GPIOStructPtr->GPIO_Conf == In_PullUp){
    GPIOStructPtr->GPIO->ODR &= 0x0 << GPIOStructPtr->GPIO_Pin;
    GPIOStructPtr->GPIO->ODR |= 0x1 << GPIOStructPtr->GPIO_Pin;
    GPIOStructPtr->GPIO_Conf = 0x8;
  }
}

void MyGPIO_Init (MyGPIO_struct_TypeDef * GPIOStructPtr){
  // enable GPIO A B C
  // GPIO_BSRR ??
  RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4);
  // if Pin 1-7
  if (GPIOStructPtr->GPIO_Pin < 8){
    // CRL modify with mode in struct
    // Care for input difference with ODR to modify
    GPIO_Init_Input_ODR(GPIOStructPtr);
    GPIOStructPtr->GPIO->CLR &= ~(0xF << 4*GPIOStructPtr->GPIO_Pin);
    GPIOStructPtr->GPIO->CLR |= GPIOStructPtr->GPIO_Conf << 4*GPIOStructPtr->GPIO_Pin;
  }else{
    // CRH modify ith mode in struct
    GPIO_Init_Input_ODR(GPIOStructPtr);
    GPIOStructPtr->GPIO->CHR &= ~(0xF << 4*GPIOStructPtr->GPIO_Pin);
    GPIOStructPtr->GPIO->CHR |= GPIOStructPtr->GPIO_Conf << 4*GPIOStructPtr->GPIO_Pin;
  }
}

int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ){
  int res = 0;
  res = GPIO -> IDR & 0x01<<GPIO_Pin;
  return res;
}

void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ){
  GPIO->ODR |= 0x01 << GPIO_Pin;
}

void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ){
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ){
}
