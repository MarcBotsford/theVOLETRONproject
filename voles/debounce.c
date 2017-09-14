/*
 * debounce.c
 *
 *  Created on: Jul 20, 2017
 *      Author: Marc
 */

#include "debounce.h"
#include <stdlib.h>
#include "gpio.h"
#include "timer.h"

debounceData_t current_task_data[MAX_DEBOUNCE_THREADS];
/*
portisrDebounceDataLink_t port0_linkers;
portisrDebounceDataLink_t port1_linkers;
portisrDebounceDataLink_t port2_linkers;
portisrDebounceDataLink_t port3_linkers;
*/
portisrDebounceDataLink_t port4_linkers;
/*
portisrDebounceDataLink_t port5_linkers;
portisrDebounceDataLink_t port6_linkers;
portisrDebounceDataLink_t port7_linkers;
portisrDebounceDataLink_t port8_linkers;
*/





debounceerr_t DEBOUNCE_clear_data(debounceData_t* data, portisrDebounceDataLink_t* linker_data){
    linker_data->flag &= ~(data->pin);
    data->id = dbUND;
    data->pin = DB_UNDEFINED;
    data->port = DB_UNDEFINED;
    data->linked_portisr = NULL;
//    linker_data->data_struct = NULL;

    return debounce_no_error;
}

void DEBOUNCE_callback(void){
    if(current_task_data[0].id != dbUND){
        current_task_data[0].shift_reg = ((current_task_data[0].shift_reg << 1)|!GPIO_getInputPinValue(current_task_data[0].port,current_task_data[0].pin)|(0xE000));
        if(current_task_data[0].shift_reg == 0xF000){
            current_task_data[0].pending  = db_pending;
            DEBOUNCE_clear_data(&current_task_data[0], current_task_data[0].linked_portisr);
        }

    }
    if(current_task_data[1].id != dbUND){
         current_task_data[1].shift_reg = (current_task_data[1].shift_reg << 1)|(GPIO_getInputPinValue(current_task_data[1].port,current_task_data[1].pin)|(0xE000));
         if(current_task_data[1].shift_reg == 0xF000){
             current_task_data[1].pending  = db_pending;
             DEBOUNCE_clear_data(&current_task_data[1], current_task_data[1].linked_portisr);
         }

     }
    if(current_task_data[2].id != dbUND){
         current_task_data[2].shift_reg = (current_task_data[2].shift_reg << 1)|(GPIO_getInputPinValue(current_task_data[2].port,current_task_data[2].pin)|(0xE000));
         if(current_task_data[2].shift_reg == 0xF000){
             current_task_data[2].pending  = db_pending;
             DEBOUNCE_clear_data(&current_task_data[2], current_task_data[2].linked_portisr);
         }

     }
    if(current_task_data[3].id != dbUND){
         current_task_data[3].shift_reg = (current_task_data[3].shift_reg << 1)|(GPIO_getInputPinValue(current_task_data[3].port,current_task_data[3].pin)|(0xE000));
         if(current_task_data[3].shift_reg == 0xF000){
             current_task_data[3].pending  = db_pending;
             DEBOUNCE_clear_data(&current_task_data[3], current_task_data[3].linked_portisr);
         }
     }
}

debounceerr_t DEBOUNCE_request(uint8_t port, uint8_t pin, edgetype_t edgetype, debounceData_t task_data_struct[],portisrDebounceDataLink_t* data_linker, void (*callback)(void)){
    /*find available flag slot*/
    uint8_t i;
    for(i = 0; i < MAX_DEBOUNCE_THREADS; i++){
        if(task_data_struct[i].id == dbUND){
            break;
        }
//        return debounce_too_many_tasks;
    }
    /*
     * populate the struct containing data on this debounce task
     */
    task_data_struct[i].port = port;
    task_data_struct[i].pin = pin;
    task_data_struct[i].id = db2;
    task_data_struct[i].callback = callback;
    task_data_struct[i].debounced_timer_task = TIMER_request(1, &DEBOUNCE_callback);
    /*
     * link some stuff and fire a flag to stop repeated interrupts
     */
    data_linker->flag |= pin;
//    data_linker->data_struct = task_data_struct[i];
    task_data_struct[i].linked_portisr = data_linker;
    return debounce_no_error;
}

void DEBOUNCE_repeater(void){
    uint8_t i;

    for(i = 0; i < MAX_DEBOUNCE_THREADS; i++){
        if(current_task_data[i].pending == db_pending){
            /*
             * This is the part that does stuff based .n the flag.
             */
            (*current_task_data[i].callback)();
            current_task_data[i].pending = db_not_pending;
            current_task_data[i].id = dbUND;
            TIMER_kill(current_task_data[i].debounced_timer_task);
        }
    }
}
