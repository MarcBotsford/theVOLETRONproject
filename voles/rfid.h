/*
 * rfid.h
 *
 *drivers to interract with ISO15693 RFID reader modules
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
/*
 * ping the rfid reader tied to the specified UART channel
 * */
void RFID_ping(uartchanel_t uart_rfid_chanel);
/*
 * configure the reader module on the given uart chanel to operate in 4 to 1 modulation mode with max power
 */
void RFID_config_max_power_4to1mod(uartchanel_t uart_rfid_chanel);
/*
 * for the DLP RFID2, enable the internal testing antenna
 */
void RFID_config_enable_internal_antenna(uartchanel_t uart_rfid_chanel);
/*
 * for the DLP RFID2, enable the external antenna
 */
void RFID_config_enable_external_antenna(uartchanel_t uart_rfid_chanel);
/*
 * configure the module with ISO1563 mode, pm mode, and agc enabled
 */
void RFID_config_the_example(uartchanel_t uart_rfid_chanel);
/*
 * single slot id string request
 */
void RFID_ssir(uartchanel_t uart_rfid_chanel);
/*
 * multi slot id string request
 */
void RFID_xsir(uartchanel_t uart_rfid_chanel);
/*
 * 1 to 156 modulation
 */
void RFID_config_1_out_of_156_ppm(uartchanel_t uart_rfid_chanel);
/*
 * toggle (not set) agc mode
 */
void RFID_config_agc_toggle(uartchanel_t uart_rfid_chanel);
/*
 * togle am/pm mode
 */
void RFID_config_ampm_toggle(uartchanel_t uart_rfid_chanel);
/*
 * initialize the system to accept RFID reads
 */
void RFID_init(void);
/*
 * push to the RFID_preasent_tags matrix, the most recently read tag ID. Doing so automatically clears the most recently red tag ID register.
 */
void RFID_parse(uint8_t uart_rfid_chaneln);
#endif /* RFID_H_ */
