/*
 * debounce.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

#include "msp.h"
#include "timer.h"
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
    dbUND = 0,
    db0,
    db1,
    db2,
    db3,

}dbId_t;

typedef enum{
    db_not_pending = 0,
    db_pending
}pend_t;

typedef struct{
    uint8_t flag;

}portisrDebounceDataLink_t;

typedef struct{
    uint8_t port;
    uint8_t pin;
    dbId_t id;
    pend_t pending;
    timerTaskid_t debounced_timer_task;
    void (*callback)(void);
    uint16_t shift_reg;
    portisrDebounceDataLink_t* linked_portisr;

}debounceData_t;



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *preprocessor constants
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
 * debounce port flag macros
 */
#define DEBOUNCE_PIN0 (0x01)
#define DEBOUNCE_PIN1 (0x02)
#define DEBOUNCE_PIN2 (0x04)
#define DEBOUNCE_PIN3 (0x08)
#define DEBOUNCE_PIN4 (0x10)
#define DEBOUNCE_PIN5 (0x20)
#define DEBOUNCE_PIN6 (0x40)
#define DEBOUNCE_PIN7 (0x80)

#define DB_UNDEFINED (11)
#define MAX_DEBOUNCE_THREADS (4)


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//debounceerr_t DEBOUNCE_init(uint8_t port, uint8_t pin, edgetype_t edgetype, uint8_t interval, uint8_t event_flg, uint8_t msk);
debounceerr_t DEBOUNCE_request(uint8_t port, uint8_t pin, edgetype_t edgetype, debounceData_t task_data_struct[],portisrDebounceDataLink_t* data_linker, void (*callback)(void));
void DEBOUNCE_callback(void);
debounceerr_t DEBOUNCE_clear_data(debounceData_t* data, portisrDebounceDataLink_t* linker_data);
void DEBOUNCE_repeater(void);

#endif /* DEBOUNCE_H_ */
