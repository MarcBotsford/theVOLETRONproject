/*
 * custom_uart.c
 *
 *  Created on: Jul 28, 2017
 *      Author: Marc
 */
#include "custom_uart.h"
#include "interrupt.h"
#include "driverlib.h"
#include "voles/timer.h"

volatile buf_t uart_rx_buf[4];
volatile buf_t uart_tx_buf[4];
volatile uint8_t tx_array_size[4];
volatile uint8_t tx_progress[4];
volatile UART_recieve_flg_t recieve_flg_rfid = 0;     /*used for timeout functions when sending commands to perepherals over UART*/
volatile timerTaskid_t uart_timeout_id;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * internal function deffenitions
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * functions
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uarterr_t VUART_init(uartchanel_t chanel){
    if(!(chanel == UART_c0 || chanel == UART_c1 || chanel == UART_c2 || chanel == UART_c3)){
        return requested_EUSCI_module_buisy;
    }

    const eUSCI_UART_Config std_uart_config = {
              /*115200 baud, 12MHz clock*/
                                               EUSCI_A_UART_CLOCKSOURCE_SMCLK,
                                               6,
                                               8,
                                               0x11,
                                               EUSCI_A_UART_NO_PARITY,
                                               EUSCI_A_UART_LSB_FIRST,
                                               EUSCI_A_UART_ONE_STOP_BIT,
                                               EUSCI_A_UART_MODE,
                                               EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
    };

    UART_disableModule(chanel);
    UART_initModule(chanel, &std_uart_config);
    UART_enableModule(chanel);
    switch(chanel){
        case UART_c0:{
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
            Interrupt_enableInterrupt(INT_EUSCIA0);
            UCA0IFG = 0;
//            CIRCBUF_init(&uart_rx_buf[0], UART_BUF_SIZE_RX);
            CIRCBUF_init(&uart_tx_buf[0],UART_BUF_SIZE_TX_LOG);
            break;
        }
        case UART_c1:{
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN3,GPIO_PRIMARY_MODULE_FUNCTION);
            Interrupt_enableInterrupt(INT_EUSCIA1);
            UCA0IFG = 0;
            CIRCBUF_init(&uart_rx_buf[1], UART_BUF_SIZE_RX);
            CIRCBUF_init(&uart_tx_buf[1], UART_BUF_SIZE_TX);
            break;
        }
        case UART_c2:{
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,GPIO_PIN3 | GPIO_PIN2,GPIO_PRIMARY_MODULE_FUNCTION);
            Interrupt_enableInterrupt(INT_EUSCIA2);
            UCA2IFG = 0;
            CIRCBUF_init(&uart_rx_buf[2], UART_BUF_SIZE_RX);
            CIRCBUF_init(&uart_tx_buf[2],UART_BUF_SIZE_TX);

            break;
        }
        case UART_c3:{
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
            Interrupt_enableInterrupt(INT_EUSCIA2);
            UCA3IFG = 0;
            CIRCBUF_init(&uart_rx_buf[3], UART_BUF_SIZE_RX);
            CIRCBUF_init(&uart_tx_buf[3],UART_BUF_SIZE_TX);

            break;
        }
        default :{
            return uart_unfinished_module;
        }
    }
    UART_enableInterrupt(chanel, EUSCI_A_UART_TRANSMIT_INTERRUPT | EUSCI_A_UART_RECEIVE_INTERRUPT);
//    UART_enableModule(chanel);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    return uart_no_error;
}

uarterr_t VUART_tx_byte( uartchanel_t chanel, uint8_t write_byte){
    if(!(chanel == UART_c0 || chanel == UART_c2 || chanel == UART_c3)){
            return requested_EUSCI_module_buisy;
        }

    UART_transmitData(chanel, write_byte);
    return uart_no_error;
}

uarterr_t VUART_tx_string(uartchanel_t chanel, uint8_t* write_string, uint8_t length){

    uint_fast8_t soft_chanel;
    uint_fast8_t j = 0;
    if(!write_string){
        /*null write string error*/
        while (1);
    }


    switch(chanel){
        case UART_c0:{
            soft_chanel = 0;
            break;
        }
        case UART_c1:{
            soft_chanel = 1;
        }
        case UART_c2:{
            soft_chanel = 2;
            break;
        }
        case UART_c3:{
            soft_chanel = 3;
            break;
        }
        default:{
            return transmit_failure;
        }
    }
    if(!uart_tx_buf[soft_chanel].buffer){
        /*error, there is no transmit buffer*/
        while(!uart_tx_buf[soft_chanel].buffer){

        }
    }
    while(uart_tx_buf[soft_chanel].cnt){
        /*error, somethings aready being tansmitted.*/
//        while(1);
    }

    tx_array_size[soft_chanel] = length;
    while(j <= UART_BUF_SIZE_TX){
        if(j == length){
            /*done*/

            CIRCBUF_push(&uart_tx_buf[soft_chanel],write_string[j]);
            UART_transmitData(chanel, CIRCBUF_pop(&uart_tx_buf[soft_chanel]));

//            UART_transmitData(chanel, 'a');
            return uart_no_error;
        }
        CIRCBUF_push(&uart_tx_buf[soft_chanel], write_string[j]);
        j++;
    }
    return uart_write_string_exeeds_buffer_length;

}

uarterr_t VUART_tx_buf(uartchanel_t chanel, buf_t* write_buf, uint8_t length){

    uint_fast8_t soft_chanel;
    uint_fast8_t j = 0;


    if(!write_buf->buffer){
        /*null buffer error*/
        while(1);
    }
    switch(chanel){
        case UART_c0:{
            soft_chanel = 0;
            break;
        }
        case UART_c1:{
            soft_chanel = 1;
        }
        case UART_c2:{
            soft_chanel = 2;
            break;
        }
        case UART_c3:{
            soft_chanel = 3;
            break;
        }
        default:{
            return transmit_failure;
        }
    }
    if(!uart_tx_buf[soft_chanel].buffer){
        /*error, there is no transmit buffer*/
        while(1);
    }
    if(uart_tx_buf[soft_chanel].cnt){
        /*error, somethings aready being tansmitted.*/
        while(1);
    }
    while(j <= UART_BUF_SIZE_TX){
        if(!write_buf->cnt){
            /*done*/
            UART_transmitData(chanel, CIRCBUF_pop(&uart_tx_buf[soft_chanel]));
            return uart_no_error;
        }
        CIRCBUF_push(&uart_tx_buf[soft_chanel], CIRCBUF_pop(write_buf));
        j++;
    }
    return uart_write_string_exeeds_buffer_length;
}

void EUSCIA0_IRQHandler(void){
    uint_fast8_t flags = UCA0IFG;
    uint_fast8_t data;
    UCA0IFG = 0;
    if(flags & UCTXIFG){
        data = CIRCBUF_pop(&uart_tx_buf[0]);
        tx_progress[0]++;
        if(/*tx_progress[0] <= tx_array_size[0]*/ uart_tx_buf[0].cnt){
            UART_transmitData(EUSCI_A0_BASE, data);
        }
        else{
            tx_progress[0] = 0;
        }
    }
    if(flags & UCRXIFG){
        recieve_flg_rfid |= CH0_RECIEVE_FLG;
        CIRCBUF_push(&uart_rx_buf[0], UART_receiveData(EUSCI_A0_BASE));
    }
}
void EUSCIA1_IRQHandler(){
    uint_fast8_t flags = UCA1IFG;
    uint_fast8_t data;
    UCA1IFG = 0;
    if(flags & UCTXIFG){
        data = CIRCBUF_pop(&uart_tx_buf[1]);
        if(uart_tx_buf[1].cnt){
            UART_transmitData(EUSCI_A1_BASE, data);
        }
    }
    if(flags & UCRXIFG){
        recieve_flg_rfid |= CH1_RECIEVE_FLG;
        CIRCBUF_push(&uart_rx_buf[1], UART_receiveData(EUSCI_A1_BASE));
    }

}
void EUSCIA2_IRQHandler(){
    uint_fast8_t flags = UCA2IFG;
    uint_fast8_t data;
    UCA2IFG = 0;
    if(flags & UCTXIFG){
        data = CIRCBUF_pop(&uart_tx_buf[2]);
        if(uart_tx_buf[2].cnt){
            UART_transmitData(EUSCI_A2_BASE, data);
        }
    }
    if(flags & UCRXIFG){
        recieve_flg_rfid |= CH2_RECIEVE_FLG;
        CIRCBUF_push(&uart_rx_buf[2], UART_receiveData(EUSCI_A2_BASE));
    }

}
void EUSCIA3_IRQHandler(){
    uint_fast8_t flags = UCA3IFG;
    uint_fast8_t data;
    UCA2IFG = 0;
    if(flags & UCTXIFG){
        data = CIRCBUF_pop(&uart_tx_buf[3]);
        if(uart_tx_buf[3].cnt){
            UART_transmitData(EUSCI_A3_BASE,data);
        }
    }
    if(flags & UCRXIFG){
        recieve_flg_rfid |= CH3_RECIEVE_FLG;
        CIRCBUF_push(&uart_rx_buf[3], UART_receiveData(EUSCI_A3_BASE));
    }
}

uartTimeout_t VUART_peripheral_response_timeout(uint16_t timeout_ms, UART_recieve_flg_t *flag_set, UART_recieve_flg_t msk){
    *flag_set &= ~(msk | msk<<4);
    uart_timeout_id = TIMER_request(15, &VUART_timeout_callback);

    while(!(*flag_set & msk) && !(*flag_set & (msk << 4))){
        /* do nothing and wait */
    }
    TIMER_kill(uart_timeout_id);
    if(!(*flag_set & msk)){
        *flag_set &= ~msk<<4;
        return uart_timeout;
    }
    if(!(*flag_set & (msk << 4))){
        *flag_set &= ~(msk);
        return uart_no_timeout;
    }
}

void VUART_timeout_callback(void){
    recieve_flg_rfid |= 0xF0;
    TIMER_kill(uart_timeout_id);
}


