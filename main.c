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

    extern debounceData_t current_task_data[MAX_DEBOUNCE_THREADS];
    extern portisrDebounceDataLink_t port4_linkers;

void main(void){

    eUSCI_UART_Config test;
    test.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;


//    UART_initModule(EUSCI_A0_BASE, &test);
    uint32_t x = 0;

    WDTCTL = WDTPW | WDTHOLD;

    Interrupt_enableMaster();

    TIMER_init();

    UART_init(EUSCI_A0_BASE);

    while(1){
    }
	
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


void PORT1_IRQHandler(void){
    if(P1IFG & BIT1
            && !(port4_linkers.flag & BIT1)){
        (P1IFG &= ~(BIT1));
        DEBOUNCE_request(1, 0x02, DB_RISING, &current_task_data, &port4_linkers, &test_callback);
    }
    if(P1IFG & BIT4
            && !(port4_linkers.flag & BIT4)){
        P1IFG &= ~(BIT4);
        DEBOUNCE_request(1,BIT4,DB_RISING,&current_task_data, &port4_linkers, &test_callback1);
    }

    if(P1IFG & BIT5
            && !(port4_linkers.flag & BIT5)){
        P1IFG &=~(BIT5);
        DEBOUNCE_request(1,BIT5,DB_RISING,&current_task_data, &port4_linkers, &test_callback2);

    }
    P1IFG = 0;

}
