/*
 * debounce.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

#include "msp.h"
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum debounce_error{
    debounce_no_error,
    debounce_too_many_tasks,
    debounce_buisy
} debounceerr_t;

typedef enum edge_type{
    DB_RISING,
    DB_FALLING
} edgetype_t;

typedef enum{
    db0 = 0,
    db1,
    db2,
    db3,
    dbUND
}dbId_t;

typedef enum{
    db_not_pending = 0,
    db_pending
}pend_t;


typedef struct{
    uint8_t port;
    uint8_t pin;
    dbId_t id;
    pend_t pending;
    void (*callback)(void);
}debounceData_t;

#define DB_UNDEFINED (11)


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//debounceerr_t DEBOUNCE_init(uint8_t port, uint8_t pin, edgetype_t edgetype, uint8_t interval, uint8_t event_flg, uint8_t msk);
debounceerr_t DEBOUNCE_request(uint8_t port, uint8_t pin, edgetype_t edgetype, debounceData_t task_data_struct,void (*callback)(void));
void DEBOUNCE_callback(void);
debounceerr_t DEBOUNCE_clear_data(debounceData_t data);
debounceerr_t DEBOUNCE_repeater(void);

#endif /* DEBOUNCE_H_ */
