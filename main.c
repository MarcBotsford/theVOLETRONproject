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


    P1DIR |= BIT0;
    P2DIR |= BIT0 | BIT1 | BIT2;






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
