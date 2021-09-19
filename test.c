#include "MYGPIO_H"

MyGPIO_struct_TypeDef * GPIOStructPtr;


int setup(MyGPIO_struct_TypeDef * GPIOStructPtr, char pin, char conf){
  GPIOStructPtr->GPIO_Pin = pin;
  GPIOStructPtr->GPIO_Conf = conf;
  return 0;
}


int main(void){

  setup(GPIOStructPtr,1,In_Floating);
  MyGPIO_Init(GPIOStructPtr);
  MyGPIO_Set(GPIOStructPtr->GPIO,1);
  MyGPIO_Reset(GPIOStructPtr->GPIO,1);
  While(int i=0 < 5){
    MyGPIO_Toggle(GPIOStructPtr->GPIO,1);
    sleep(1);
  }

}
