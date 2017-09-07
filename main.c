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
    extern buf_t uart_rx_buf[4];


    uint32_t k = 0;
    uint8_t uca_soft_ifg = 0;

    timerTaskid_t prelim_beep;

        void main(void){

    uint32_t x = 0;

    WDTCTL = WDTPW | WDTHOLD;
    TIMER_init();

     UCA0IE |= UCTXIE | UCSTTIE;

    VUART_init(UART_c2);
    VUART_init(UART_c0);

    P1DIR |= BIT7;
    P1OUT &= ~BIT7;

    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;
    P1IE |= BIT1;

    P2DIR &= ~(BIT5 | BIT7);
    P2REN &= ~BIT5;
    P2REN |= BIT7;
    P2OUT |= BIT7;
    P2IE |= BIT5 | BIT7;
    P2IFG = 0;
    Interrupt_enableInterrupt(INT_PORT2);
    Interrupt_enableInterrupt(INT_PORT1);

    P2DIR |= BIT1;

    P6DIR |= BIT0;
    P6OUT |= BIT0;

    Interrupt_enableMaster();

    buf_t testbuf;
    CIRCBUF_init(&testbuf, 5);
    CIRCBUF_push(&testbuf, '0');
    CIRCBUF_push(&testbuf, '0');
    CIRCBUF_push(&testbuf, '0');
    CIRCBUF_push(&testbuf, '0');

//    RFID_ping(UART_c2);
//    for(x=0;x<0x0000FFFF;x++);
//    RFID_config_enable_internal_antenna(UART_c2);
//    for(x=0;x<0x0000FFFF;x++);
    RFID_config_the_example(UART_c2);
    for(x=0;x<0x0000FFFF;x++);



    while(1){

//        RFID_ssir(UART_c2);
//        for(x=0;x<0xFFFF;x++){

//        }
        DEBOUNCE_repeater();
        if(uart_rx_buf[2].cnt!= 0){
            VUART_tx_byte(UART_c0,CIRCBUF_pop(&uart_rx_buf[2]));
        }
    }
}







void test_callback(void){
    RFID_xsir(UART_c2);
}
void test_callback1(void){

}
void test_callback2(){

}
void test_callback3(void){

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
