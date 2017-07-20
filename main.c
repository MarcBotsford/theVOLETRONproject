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


    buf_t testbuf;
    uint8_t testdata = 5;
    uint8_t* testptr = &testdata;

//    TIMER_calculate_deviders_s(100000);


    Interrupt_enableMaster();
    Interrupt_enableInterrupt(INT_TA1_N);


    TIMER_calculate_deviders_l(10000);

    while(1);
	
}


void test_callback(void){
    a++;

}
