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
}debounce_error_t;

typedef enum edge_type{
    rising,
    falling
}edgetype_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

debounce_error_t DEBOUNCE_init(uint8_t port, uint8_t pin,edgetype_t edgetype, uint8_t interval);
void DEBOUNCE_isr(void);


#endif /* DEBOUNCE_H_ */
