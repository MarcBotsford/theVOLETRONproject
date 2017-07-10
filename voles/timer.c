/*
 * timer.c
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */
#include "msp.h"
#include "timer.h"

timerr_t TIMER_init_raw(uint32_t ccr, uint8_t devider,tim_t clk_chanel){
    hreg16_t taCTL   = 0x40000000;

    hreg16_t taCCTL0 = 0x40000002;
    hreg16_t taCCTL1 = 0x40000004;
    hreg16_t taCCTL2 = 0x40000006;
    hreg16_t taCCTL3 = 0x40000008;
    hreg16_t taCCTL4 = 0x4000000A;
    hreg16_t taCCTL5 = 0x4000000C;
    hreg16_t taCCTL6 = 0x4000000E;

    hreg16_t taCCR0 = 0x40000012;
    hreg16_t taCCR1 = 0x40000014;
    hreg16_t taCCR2 = 0x40000016;
    hreg16_t taCCR3 = 0x40000018;
    hreg16_t taCCR4 = 0x4000001A;
    hreg16_t taCCR5 = 0x4000001C;
    hreg16_t taCCR6 = 0x4000001E;



    uint8_t i;

    for(i=0; i < clk_chanel; i++){
        taCTL += 0x00000200;

        taCCTL0 += 0x00000200;
        taCCTL1 += 0x00000200;
        taCCTL2 += 0x00000200;
        taCCTL3 += 0x00000200;
        taCCTL4 += 0x00000200;
        taCCTL5 += 0x00000200;
        taCCTL6 += 0x00000200;

        taCCR0 += 0x00000200;
        taCCR1 += 0x00000200;
        taCCR2 += 0x00000200;
        taCCR3 += 0x00000200;
        taCCR4 += 0x00000200;
        taCCR5 += 0x00000200;
        taCCR6 += 0x00000200;
    }

    //set the clock source to SM clock
*taCTL |= TIM_SMCLK;
    if(!(devider == 1 || devider ==2 || devider == 4 || devider == 8)){
        return timer_invalid_devider;
    }


    return timer_no_error;
}

timerr_t TIMER_begin(tim_t clk_chanel){

    return timer_no_error;
}

timerr_t TIMER_pause(tim_t chanel){

    return timer_no_error;
}

timerr_t TIMER_reset_raw(tim_t chanel, uint32_t ccr){

    return timer_no_error;
}

timerr_t TIMER_set_callback(tim_t chanel, void(*callback)){

    return timer_no_error;
}

timid_t TIMER_request(uint32_t period, void(*callback)){

    return task0;
}

timid_t TIMER_request_repeat(uint32_t period, void(*callback), uint32_t reps){

    return task0;
}

timerr_t TIMER_kill(uint8_t taskid){

    return timer_no_error;
}
