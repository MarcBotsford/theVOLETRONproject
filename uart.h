/*
 * uart.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */

#ifndef UART_H_
#define UART_H_


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type deffinitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef enum uart_err{
    no_error,
    transmit_failure,
    recieve_failure
}uarterr_t;

typedef enum uart_chanel{
    UART_c0,
    UART_c1,
    UARt_c2
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




#endif /* UART_H_ */
