/*
 * timer.c
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */
#include "msp.h"
#include "timer.h"

timerr_t TIMER_config_raw(uint16_t ccr, uint8_t devider, uint32_t clk_chanel, uint8_t ccr_chanel){
    timerr_t dev_err;

    if(ccr_chanel > 6){
        return timer_invalid_ccr_chanel;
    }


        //set clock devider
    dev_err = TIMER_load_devider(devider, clk_chanel);

    if (dev_err != timer_no_error){
        return dev_err;
    }
        //set ccr value
    TIMER_AG(clk_chanel)->CCR[ccr_chanel] = ccr;
        //use smclk and enable interrupts
    TIMER_AG(clk_chanel)->CTL &= ~(TIMER_A_CTL_SSEL_MASK);
    TIMER_AG(clk_chanel)->CTL |= TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_IE;
        //enable interrupts
    TIMER_AG(clk_chanel)->CCTL[ccr_chanel] |= TIMER_A_CCTLN_CCIE;




    return timer_no_error;
}

timerr_t TIMER_config(uint32_t period, uint32_t chanel, uint8_t ccr_chanel){
        //typechecking
    if(ccr_chanel > 6){
        return timer_invalid_ccr_chanel;
    }
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }




    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_load_devider(uint8_t devider, uint32_t clk_chanel){

    if(!(devider == TIMER_DEV_1 || devider == TIMER_DEV_2 || devider == TIMER_DEV_4 || devider == TIMER_DEV_8)){
        return timer_invalid_devider;
    }
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }


    TIMER_AG(clk_chanel)->CTL |= (devider << 6);

    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timerr_t TIMER_begin(tim_t clk_chanel){
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    TIMER_AG(clk_chanel)->CTL &= ~(TIMER_A_CTL_MC_MASK);
    TIMER_AG(clk_chanel)->CTL |= TIMER_A_CTL_MC__UP;


    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timerr_t TIMER_pause(tim_t clk_chanel){

    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    TIMER_AG(clk_chanel)->CTL &= ~(TIMER_A_CTL_MC_MASK);
    TIMER_AG(clk_chanel)->CTL |= TIMER_A_CTL_MC__STOP;

    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timerr_t TIMER_reset_raw(tim_t chanel, uint32_t ccr, uint8_t devider, uint8_t ccr_chanel){

    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timerr_t TIMER_set_callback(tim_t clk_chanel,uint8_t ccr_chanel, void(*callback)){
        //type checking
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    if(ccr_chanel > 6){
        return timer_invalid_ccr_chanel;
    }


    switch(clk_chanel){
    case TA0:
        callback_A0[ccr_chanel] = callback;
        break;
    case TA1:
        callback_A1[ccr_chanel] = callback;
        break;
    case TA2:
        callback_A2[ccr_chanel] = callback;
        break;
    case TA3:
        callback_A3[ccr_chanel] = callback;
        break;
    }

    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timid_t TIMER_request(uint32_t period, void(*callback)){

    return task0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timid_t TIMER_request_repeat(uint32_t period, void(*callback), uint32_t reps){

    return task0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_kill(uint8_t taskid){

    return timer_no_error;
}
