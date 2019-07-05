#include "botoes.h"


void destrava_pino(uint32_t portal_base){
    ESC_REG(portal_base + GPIO_O_LOCK) |= GPIO_LOCK_KEY;
    ESC_REG(portal_base + GPIO_O_CR) |= 0x01;
    ESC_REG(portal_base + GPIO_O_LOCK) |= 0;
}

void config_buttons(void){
    //BOTOES
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
   destrava_pino(GPIO_PORTF_BASE);
   GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
   GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
   GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5);
   GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
   GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4 , GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


}

int start_buttons(void){

    //enviando sinal 0 para coluna 1
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3, 0xFF);

    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) != GPIO_PIN_4){ //SW1 pressionado
            return 1;
        }

        if(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0) != GPIO_PIN_0){ //SW5 pressionado
            return 2;
        }

        if(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_1) != GPIO_PIN_1){ //SW9 pressionado
            return 3;
        }

        if(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_5) != GPIO_PIN_5){ //SW13 pressionado
            return 4;
        }
        return 0;

}



