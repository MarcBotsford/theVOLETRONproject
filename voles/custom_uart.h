/*
 * custom_uart.h
 *
 *  Created on: Jul 28, 2017
 *      Author: Marc
 */

#ifndef CUSTOM_UART_H_
#define CUSTOM_UART_H_

#include "uart.h"
#include "msp.h"
#include "circbuf.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type deffinitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef enum uart_err{
    uart_no_error,
    transmit_failure,
    recieve_failure,
    requested_EUSCI_module_buisy,
    uart_unfinished_module,
    uart_unusable_module,
    uart_write_string_exeeds_buffer_length
}uarterr_t;

typedef enum uart_chanel{
    UART_c0 = EUSCI_A0_BASE,
    UART_c1 = EUSCI_A1_BASE,
    UART_c2 = EUSCI_A2_BASE,
    UART_c3 = EUSCI_A3_BASE
}uartchanel_t;

#define UART_BUF_SIZE (200)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *preprocessor
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define STR_ELEMENT_COUNT(x) (sizeof(x))

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function deffinitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uarterr_t VUART_tx_byte( uartchanel_t chanel, uint8_t write_byte);
uarterr_t VUART_tx_byte_n(uint8_t* write_bytes, uartchanel_t chanel, uint8_t byte_count);
uarterr_t VUART_rx_byte (uartchanel_t chanel);
uarterr_t VUART_init(uartchanel_t chanel);
uarterr_t VUART_tx_string(uartchanel_t chanel, uint8_t* write_string, uint8_t length);
uarterr_t VUART_tx_buf(uartchanel_t chanel, buf_t* write_buf, uint8_t length);

void EUSCIA0_IRQHandler(void);



#endif /* CUSTOM_UART_H_ */
