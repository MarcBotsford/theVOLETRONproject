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
    uint32_t k = 0;

void main(void){




//    UART_initModule(EUSCI_A0_BASE, &test);
    uint32_t x = 0;

    WDTCTL = WDTPW | WDTHOLD;
    TIMER_init();
    /*                                                      |
     * uart stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   v
     */

    UART_disableModule (EUSCI_A0_BASE);
    UART_init(EUSCI_A0_BASE);
    UART_enableModule(EUSCI_A0_BASE);

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    Interrupt_enableInterrupt(INT_EUSCIA0);
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    UCA0IFG = 0;
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
    /*
     * uart stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    ^
     *                                                      |
     */

    P2DIR &= ~(BIT5);
    P2REN &= ~BIT5;
//    P1OUT &= ~(BIT5);
    P2IE |= BIT5;
    P2IFG = 0;
    Interrupt_enableInterrupt(INT_PORT2);

    P2DIR |= BIT1;

    Interrupt_enableMaster();


//    UART_transmitData(EUSCI_A0_BASE, 0xAA);


    while(1){
//        UART_transmitData(EUSCI_A0_BASE, 0xFF);

        DEBOUNCE_repeater();

    }
}



void EUSCIA0_IRQHandler(){
    if(UCA0IFG & UCTXIFG){
        UCA0IFG = 0;

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
    P2OUT ^= BIT1;
    UART_transmitData(EUSCI_A0_BASE, 'A');
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
void PORT2_IRQHandler(void){
    if(P2IFG & BIT5
            && !(port4_linkers.flag & BIT5)){
        DEBOUNCE_request(2,BIT5,DB_RISING,&current_task_data, &port4_linkers, &test_callback2);
        P2IFG = 0;
        k++;

    }
    P2IFG = 0;
}
























