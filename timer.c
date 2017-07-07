/*
 * timer.c
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */
#include "msp.h"
#include "timer.h"

timerr_t TIMER_init_raw(uint32_t ccr, uint8_t devider,tim_t clk_chanel){

    return no_error;
}

timerr_t TIMER_begin(tim_t clk_chanel){

    return no_error;
}

timerr_t TIMER_pause(tim_t chanel){

    return no_error;
}

timerr_t TIMER_reset_raw(tim_t chanel, uint32_t ccr){

    return no_error;
}

timerr_t TIMER_set_callback(tim_t chanel, void(*callback)){

    return no_error;
}

timid_t TIMER_request(uint32_t period, void(*callback)){

    return task0;
}

timid_t TIMER_request_repeat(uint32_t period, void(*callback), uint32_t reps){

    return task0;
}

timerr_t TIMER_kill(uint8_t taskid){

    return no_err;
}























