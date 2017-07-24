//*****************************************************************************
//
// Botsford
//
//          o   o
//            |
//        \_______/
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
    void test_callback1(void);
    void test_callback2();
    void test_callback3(void);

void main(void){

    uint32_t x = 0;

    WDTCTL = WDTPW | WDTHOLD;

    Interrupt_enableMaster();
    Interrupt_enableInterrupt(INT_TA0_N);
    Interrupt_enableInterrupt(INT_TA1_N);
    Interrupt_enableInterrupt(INT_TA2_N);
    Interrupt_enableInterrupt(INT_TA3_N);

    P1DIR |= BIT0;
    P2DIR |= BIT0 | BIT1 | BIT2;



//    TIMER_calculate_deviders_s(100, TA1);
    TIMER_request(500,test_callback);
    TIMER_request(50, &test_callback1);
    TIMER_request(100, &test_callback2);
    TIMER_request(1000,&test_callback3);

    while(1);
	
}


void test_callback(void){
    P1OUT ^= BIT0;

}
void test_callback1(void){
    P2OUT ^= BIT0;
}
void test_callback2(){
    P2OUT ^= BIT1;
}
void test_callback3(void){
    P2OUT ^= BIT2;
}
