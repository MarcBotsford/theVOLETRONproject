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

debounceData_t current_task_data;




debounceerr_t DEBOUNCE_clear_data(debounceData_t data){
    data.id = dbUND;
    data.pin = DB_UNDEFINED;
    data.port = DB_UNDEFINED;

    return debounce_no_error;
}

void DEBOUNCE_callback(void){
    static uint16_t shift_reg;
    shift_reg = (shift_reg << 1)|(!(GPIO_getInputPinValue(current_task_data.port, current_task_data.pin)))|(0xE000);

    if(shift_reg == 0xF000){
        current_task_data.pending = db_pending;
        DEBOUNCE_clear_data(current_task_data);
    }
}

debounceerr_t DEBOUNCE_request(uint8_t port, uint8_t pin, edgetype_t edgetype, debounceData_t task_data_struct, void (*callback)(void)){
    /*find available flag slot*/
    if(task_data_struct.id != dbUND){
        return debounce_buisy;
    }

    task_data_struct.port = port;
    task_data_struct.pin = pin;
    task_data_struct.id = db0;
    task_data_struct.callback = callback;

    TIMER_request(5, &DEBOUNCE_callback);
    return debounce_no_error;
}
debounceerr_t DEBOUNCE_repeater(void){
    if(current_task_data.pending){
        /*
         * This is the part that does stuff based on the flag.
         */
        (*current_task_data.callback)();
        current_task_data.pending = db_not_pending;
    }
}

