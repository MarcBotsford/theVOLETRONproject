/*
 * custom_uart.c
 *
 *  Created on: Jul 28, 2017
 *      Author: Marc
 */
#include "custom_uart.h"
#include "driverlib.h"



uarterr_t UART_init(uartchanel_t chanel){
    if(!(chanel == UART_c0 || chanel == UART_c1 || chanel == UART_c2 || chanel == UART_c3)){
        return requested_EUSCI_module_buisy;
    }

    const eUSCI_UART_Config std_uart_config = {
                                               EUSCI_A_UART_CLOCKSOURCE_SMCLK,
                                               78,
                                               2,
                                               0x00,
                                               EUSCI_A_UART_NO_PARITY,
                                               EUSCI_A_UART_LSB_FIRST,
                                               EUSCI_A_UART_ONE_STOP_BIT,
                                               EUSCI_A_UART_MODE,
                                               EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
    };

    UART_disableModule(chanel);
    UART_initModule(chanel, &std_uart_config);
    UART_enableInterrupt(chanel, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    switch(chanel){
        case UART_c0:{
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
            Interrupt_enableInterrupt(INT_EUSCIA0);
            UCA0IFG = 0;
            break;
        }
        default :{
            return uart_unfinished_module;
        }
    }
    UART_enableModule(chanel);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    return uart_no_error;
}




