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
#include <string.h>
#include <stdlib.h>



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

    volatile uint8_t cb_ctr_debug_deboucne = 0;
    timerTaskid_t prelim_beep;

    volatile uint8_t test_cnt;

           void main(void){

    uint32_t x = 0;
    uint8_t test_incrementer = 0;
    extern volatile UART_recieve_flg_t recieve_flg_rfid;

    WDTCTL = WDTPW | WDTHOLD;
    TIMER_init();
    RFID_init();
    VUART_init(UART_c0);
    VUART_init(UART_c2);

    UCA0IE |= UCTXIE | UCSTTIE;


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

    while(1){
//        VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
        RFID_config_1_out_of_156_ppm(UART_c2);
        test_incrementer++;
        VUART_tx_byte(UART_c0, test_incrementer);
    }



    uint32_t k;

    RFID_config_the_example(UART_c2);
//    for(x=0;x<0x0FFFE;x++);
    RFID_config_enable_external_antenna(UART_c2);

    TIMER_request(500, &test_callback1);

    while(1){

        DEBOUNCE_repeater();
        RFID_parse(2);
    }
}







void test_callback(void){
    RFID_xsir(UART_c2);
    cb_ctr_debug_deboucne++;
}
void test_callback1(void){
    RFID_xsir(UART_c2);
    test_cnt++;

}
void test_callback2(){

}
void test_callback3(void){

}


void PORT1_IRQHandler(void){
    Interrupt_disableMaster();
    uint8_t temp = P1IFG;
    P1IFG = 0;
    if(temp & BIT1){
//            && !(port4_linkers.flag & BIT1)){
//        (temp &= ~(BIT1));
//        DEBOUNCE_request(1, BIT1, DB_RISING, &current_task_data, &port4_linkers, &test_callback);
        RFID_xsir(UART_c2);
    }
    if(temp & BIT4
            && !(port4_linkers.flag & BIT4)){
        temp &= ~(BIT4);
        DEBOUNCE_request(1,BIT4,DB_RISING,&current_task_data, &port4_linkers, &test_callback1);
    }

    if(temp & BIT5
            && !(port4_linkers.flag & BIT5)){
        temp &=~(BIT5);
        DEBOUNCE_request(1,BIT5,DB_RISING,&current_task_data, &port4_linkers, &test_callback2);

    }
    P1IFG = 0;
    Interrupt_enableMaster();
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
