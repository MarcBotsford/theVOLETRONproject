/*
 * rfid.h
 *
 *  Created on: Jul 7, 2017
 *      Author: Marc
 */

#ifndef RFID_H_
#define RFID_H_

#include "voles/custom_uart.h"
#include "msp.h"
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *preprocessor constants
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void RFID_ping(uartchanel_t uart_rfid_chanel);
void RFID_config_max_power_4to1mod(uartchanel_t uart_rfid_chanel);
void RFID_config_enable_internal_antenna(uartchanel_t uart_rfid_chanel);
void RFID_config_the_example(uartchanel_t uart_rfid_chanel);
void RFID_ssir(uartchanel_t uart_rfid_chanel);
void RFID_xsir(uartchanel_t uart_rfid_chanel);
void RFID_config_1_out_of_156_ppm(uartchanel_t uart_rfid_chanel);
void RFID_config_agc_toggle(uartchanel_t uart_rfid_chanel);
void RFID_config_ampm_toggle(uartchanel_t uart_rfid_chanel);
#endif /* RFID_H_ */
