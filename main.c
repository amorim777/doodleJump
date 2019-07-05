#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/uart.h"
#include "driverlib/systick.h"
#include "utils/uartstdio.h"
#include "driverlib/timer.h"


#include "utils/ustdlib.h"
#include "driverlib/hibernate.h"

#include "Nokia5110.h"
#include "jogo.h"
#include "botoes.h"

void HandlerSysTick(void){
    background();
}

void main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysTickEnable ();
    SysTickIntEnable();
    SysTickPeriodSet (37000);//40000


    Nokia5110_Init();
    Nokia5110_Clear();
    Nokia5110_SetCursor(0 , 0);
    config_buttons();
    loading(2); //2 pulos no loading
    while(menu()){} //menu de selecao

    while(1)
    {

        start_game();
    }
}
