//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//*****************************************************************************

#include "msp.h"
#include "voles/voles.h"
#include "driverlib.h"


    uint32_t a;
    timerr_t b;
    timerr_t c;
    timerr_t d;

    void test_callback(void);

void main(void){


    WDTCTL = WDTPW | WDTHOLD;

    clkData_t datat;
    b = TIMER_config_raw(0xFFFF, TIMER_DEV_1, TA1, 0);


    b = TIMER_set_callback(TA1,0, &test_callback);
    TIMER_begin(TA1);

    Interrupt_enableMaster();
    Interrupt_enableInterrupt(INT_TA1_N);


    TIMER_calculate_deviders_l(1000);

    while(1);
	
}


void test_callback(void){
    a++;

}
