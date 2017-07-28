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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type deffinitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef enum uart_err{
    uart_no_error,
    transmit_failure,
    recieve_failure,
    requested_EUSCI_module_buisy
}uarterr_t;

typedef enum uart_chanel{
    UART_c0 = EUSCI_A0_BASE,
    UART_c1 = EUSCI_A1_BASE,
    UART_c2 = EUSCI_A2_BASE,
    UART_c3 = EUSCI_A3_BASE
}uartchanel_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function deffinitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uarterr_t UART_tx_byte(uint8_t write_byte, uartchanel_t chanel);
uarterr_t UART_tx_byte_n(uint8_t* write_bytes, uartchanel_t chanel, uint8_t byte_count);
uarterr_t UART_rx_byte (uartchanel_t chanel);
uarterr_t UART_set_baud(uint32_t baud, uartchanel_t chanel);
uarterr_t UART_init(uartchanel_t chanel);




#endif /* CUSTOM_UART_H_ */
