#include "MYGPIO_H"


int setup(MyGPIO_struct_TypeDef * GPIOStructPtr, char pin, char conf){
  GPIOStructPtr->GPIO_Pin = pin;
  GPIOStructPtr->GPIO_Conf = conf;
  return 0;
}



int main(void){

  MyGPIO_Init(MyGPIO_struct_TypeDef * GPIOStructPtr);


}
