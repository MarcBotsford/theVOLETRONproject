//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "voles/voles.h"


void (*callback_A0[6]);
void (*callback_A1[6]);
void (*callback_A2[6]);
void (*callback_A3[6]);

void main(void)
{
    timerr_t a;
    timerr_t b;
    timerr_t c;
    timerr_t d;
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    a = TIMER_load_devider(TIMER_DEV_4,TA3);

    while(1);
	
}
