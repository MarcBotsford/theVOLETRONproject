//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "voles/voles.h"

void main(void)
{
    timerr_t a;
    timerr_t b;
    timerr_t c;
    timerr_t d;
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    a = TIMER_init_raw(0,0,TA3);
    b = TIMER_init_raw(0,1,TA3);
    c = TIMER_init_raw(0,10,TA3);
    d = TIMER_init_raw(0,6,TA3);

    while(1);
	
}
