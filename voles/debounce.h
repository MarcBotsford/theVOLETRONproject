/*
 * debounce.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum debounce_error{
    no_error,
    error
}debounceerr_t;

typedef enum edge_type{
    DB_RISING,
    DB_FALLING
}edgetype_t;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

debounceerr_t DEBOUNCE_init(uint8_t port, uint8_t pin,edgetype_t edgetype, uint8_t interval,uint8_t event_flg, uint8_t msk);
void DEBOUNCE_isr(void);


#endif /* DEBOUNCE_H_ */
