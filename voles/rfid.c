/*
 * rfid.c
 *
 *  Created on: Aug 7, 2017
 *      Author: Marc
 */
#include "rfid.h"
#include "custom_uart.h"
#include "circbuf.h"
#include <stdlib.h>

#define RPD_BUFF_LEN 100

extern buf_t uart_rx_buf[4];
extern UART_recieve_flg_t recieve_flg_rfid;

uint64_t rfid_preasent_tags[4][1] = {{0},{0},{0},{0}};   /*for the moment this name is a misnomer. it's actually the most recently read tag*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * internal function definitions
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * command sending functions. in the final version all will return full error messages.
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


void RFID_ping(uartchanel_t uart_rfid_chanel){

    VUART_tx_string(uart_rfid_chanel, "0108000304FF0000", 16);
    VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}
void RFID_config_max_power_4to1mod(uartchanel_t uart_rfid_chanel){

    VUART_tx_string(uart_rfid_chanel, "010C00030410003101010000", sizeof("010C00030410003101010000")-1);
    VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}


void RFID_config_enable_internal_antenna(uartchanel_t uart_rfid_chanel){
    VUART_tx_string(uart_rfid_chanel, "01080003042A0000",16);
    VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}

void RFID_config_enable_external_antenna(uartchanel_t uart_rfid_chanel){

    VUART_tx_string(uart_rfid_chanel, "01080003042B0000",16);
    VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}

void RFID_config_the_example(uartchanel_t uart_rfid_chanel){
    uint16_t x;
    VUART_tx_string(uart_rfid_chanel, "010C00030410003101010000", sizeof("010C00030410003101010000")-1); //ISO15693 mode (1-out-of-156 pulse position modulation.)
        VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
    VUART_tx_string(uart_rfid_chanel, "0109000604F0000000", sizeof("0109000604F0000000")-1);            //agc toggle
        VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
    VUART_tx_string(uart_rfid_chanel, "0109000304F1FF0000", sizeof("0109000304F1FF0000")-1);           //am/pm toggle
        VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
//    VUART_tx_string(uart_rfid_chanel, "01080003042B0000",16);
//        VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}

void RFID_config_1_out_of_156_ppm(uartchanel_t uart_rfid_chanel){
    VUART_tx_string(uart_rfid_chanel, "010C00030410003101010000", sizeof("010C00030410003101010000")-1); //ISO15693 mode (1-out-of-156 pulse position modulation.)
    VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}

void RFID_config_agc_toggle(uartchanel_t uart_rfid_chanel){
    VUART_tx_string(uart_rfid_chanel, "0109000604F0000000", sizeof("0109000604F0000000")-1);            //agc toggle
    VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}
void RFID_config_ampm_toggle(uartchanel_t uart_rfid_chanel){
    VUART_tx_string(uart_rfid_chanel, "0109000304F1FF0000", sizeof("0109000304F1FF0000")-1);           //am/pm toggle
    VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}

void RFID_ssir(uartchanel_t uart_rfid_chanel){
    VUART_tx_string(uart_rfid_chanel, "010B000304142401000000",sizeof("010B000304142401000000")-1);
    VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}

void RFID_xsir(uartchanel_t uart_rfid_chanel){
    VUART_tx_string(uart_rfid_chanel, "010B000304140401000000", sizeof("010B000304140401000000")-1);
//    VUART_peripheral_response_timeout(15,& recieve_flg_rfid,CH2_RECIEVE_FLG);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * manipulation of the buffers
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void RFID_parse(uint8_t uart_rfid_chaneln){
    if(uart_rfid_chaneln >3){
        /*
         * return error
         */
    }
    uint8_t i = 0;
    cb_item8 post_pop;
    uint64_t temp_RFID = 0;
    char id_array[17] = {}; /*17 because each tag has a 16 nybble code, plus there's a zero at the end to make strtoull work*/
    id_array[16] = 0;

    while(uart_rx_buf[uart_rfid_chaneln].cnt){
        if(CIRCBUF_pop(&uart_rx_buf[uart_rfid_chaneln]) == '['){
            while(post_pop != ','){
                /*
                 * load uid into tags buffer (buffer which contains the uid of all tags in the corresponding read field.
                 */
                post_pop = CIRCBUF_pop(&uart_rx_buf[uart_rfid_chaneln]);
                if(post_pop != 0xFF && post_pop != ','){
                    id_array[i] = post_pop;
                    ++i;
                    if(i == 16){
                        rfid_preasent_tags[2][0] = strtoull(id_array,NULL,16);
                    }
                }
            }
        }
        /*
         *  my proposed changes:
         *      I need this to detect the absence of a perticular tag, not only th epresence of some arbitrary tag;
         *      I will start by parsing the string to find the beginning of the ISO15693 standard formatted tag thingy.
         *      it'll check each slot noting the UID of tags as it finds them. then it'll compare the list to those
         *      already in the RFID_PREASENT_TAGS buffer, to see what should be added removed or remain the same.
         * */
    }

    /*
     * return success message eventually
     */
}

void RFID_init(void){
    uint8_t i;
    for(i=0; i<4; i++){
        CIRCBUF_init(&rfid_preasent_tags[i], RPD_BUFF_LEN);
    }
}


