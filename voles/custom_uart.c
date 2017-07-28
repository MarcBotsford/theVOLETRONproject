/*
 * custom_uart.c
 *
 *  Created on: Jul 28, 2017
 *      Author: Marc
 */
#include "custom_uart.h"



uarterr_t UART_init(uartchanel_t chanel){
    if(!(chanel == UART_c0 || chanel == UART_c1 || chanel == UART_c2 || chanel == UART_c3)){
        return requested_EUSCI_module_buisy;
    }

    const eUSCI_UART_Config std_uart_config = {EUSCI_A_UART_CLOCKSOURCE_SMCLK, 26, 1, 1, EUSCI_A_UART_NO_PARITY, EUSCI_A_UART_LSB_FIRST, EUSCI_A_UART_ONE_STOP_BIT, EUSCI_A_UART_MODE, EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION};

    UART_initModule(chanel, &std_uart_config);

}




