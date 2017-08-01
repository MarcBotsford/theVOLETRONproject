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
    void beep(void);

    extern debounceData_t current_task_data[MAX_DEBOUNCE_THREADS];
    extern portisrDebounceDataLink_t port4_linkers;
    uint32_t k = 0;
    uint8_t uca_soft_ifg = 0;

    timerTaskid_t prelim_beep;

void main(void){

//    UART_initModule(EUSCI_A0_BASE, &test);
    uint32_t x = 0;

    WDTCTL = WDTPW | WDTHOLD;
    TIMER_init();
    /*                                                      |
     * uart stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   v
     */


    UART_init(EUSCI_A0_BASE);

    P1DIR |= BIT7;
    P1OUT &= ~BIT7;

    P2DIR &= ~(BIT5 | BIT7);
    P2REN &= ~BIT5;
    P2REN |= BIT7;
    P2OUT |= BIT7;
    P2IE |= BIT5 | BIT7;
    P2IFG = 0;
    Interrupt_enableInterrupt(INT_PORT2);

    P2DIR |= BIT1;

    Interrupt_enableMaster();




    while(1){

        DEBOUNCE_repeater();

    }
}



void EUSCIA0_IRQHandler(){
    if(UCA0IFG & UCTXIFG){
        UCA0IFG = 0;
        uca_soft_ifg = 1;

    }
    UCA0IFG = 0;

}



void test_callback(void){
    P1OUT ^= BIT0;

}
void test_callback1(void){
    P2OUT ^= BIT0;
}
void test_callback2(){
//    P2OUT ^= BIT1;
    UART_transmitData(EUSCI_A0_BASE, 'b');
    while(uca_soft_ifg = 0);
    uca_soft_ifg = 0;
    UART_transmitData(EUSCI_A0_BASE, 'o');
    while(uca_soft_ifg = 0);
    uca_soft_ifg = 0;
    UART_transmitData(EUSCI_A0_BASE, 'o');
    while(uca_soft_ifg = 0);
    uca_soft_ifg = 0;
    UART_transmitData(EUSCI_A0_BASE, 'p');
    uca_soft_ifg = 0;
    UART_transmitData(EUSCI_A0_BASE, 0x0D);

    if(!(P1OUT & BIT7))
    P1OUT |= BIT7;
    prelim_beep = TIMER_request(500, &beep);
}
void test_callback3(void){
    P2OUT ^= BIT1;
    UART_transmitData(EUSCI_A0_BASE, 'c');
    while(uca_soft_ifg = 0);
    uca_soft_ifg = 0;
    UART_transmitData(EUSCI_A0_BASE, 'l');
    while(uca_soft_ifg = 0);
    uca_soft_ifg = 0;
    UART_transmitData(EUSCI_A0_BASE, 'i');
    while(uca_soft_ifg = 0);
    uca_soft_ifg = 0;
    UART_transmitData(EUSCI_A0_BASE, 'c');
    while(uca_soft_ifg = 0);
    uca_soft_ifg = 0;
    UART_transmitData(EUSCI_A0_BASE, 'k');
    while(uca_soft_ifg = 0);
    uca_soft_ifg = 0;
    UART_transmitData(EUSCI_A0_BASE, 0x0D);

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
void PORT2_IRQHandler(void){
    if(P2IFG & BIT5
            && !(port4_linkers.flag & BIT5)){
        DEBOUNCE_request(2,BIT5,DB_RISING,&current_task_data, &port4_linkers, &test_callback2);
        P2IFG = 0;
    }
    if(P2IFG & BIT7
            && !(port4_linkers.flag & BIT7)){
        DEBOUNCE_request(2,BIT7,DB_RISING,&current_task_data,&port4_linkers, &test_callback3);
        P2IFG = 0;
    }
    P2IFG = 0;
}


void beep(void){
    P1OUT &=~(BIT7);
    TIMER_kill(prelim_beep);
//    TIMER_pause
}





















