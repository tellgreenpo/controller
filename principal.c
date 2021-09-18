#include "stm32f10x.h"

int main(void){
  RCC->APB2ENR |= (0x01 <<2) | (0x01 << 3) | (0x01 << 4);
  // PC8 en pull up input
  GPIOC->CRH &= ~(0xF);
  GPIOC->CRH |= 0x8;
  GPIO->ODR |= 0x1 << 8;
  // PC10 en pulldown output
  GPIOC->CRH &= ~(0xF00);
  GPIOC->CRH |= 0x1 << 8;

  do
  {
    // PC8 IDR 0 ==> PC10 ODR 1
    // Compare IDR register with 0x0100 to check if the 8th bit is 1
    if(GPIO->IDR & GPIO_IDR_IDR8){
    }else{
      // Set the 10th bot of ODR to 1
      GPIO->ODR |= 0x1 << 10;
    }
  }while(1);
}
