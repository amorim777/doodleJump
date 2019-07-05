#ifndef BOTOES_H
#define BOTOES_H


#define ESC_REG(x)                  (*((volatile uint32_t *)(x)))
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"

void config_buttons(void);
int start_buttons(void);
void destrava_pino(uint32_t);
#endif
