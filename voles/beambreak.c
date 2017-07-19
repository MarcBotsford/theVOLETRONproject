/*
 * beambreak.c
 *
 *  Created on: Jul 19, 2017
 *      Author: Marc
 */


#include <stdint.h>
#include "beambreak.h"
#include "debouce.h"

uint8_t bbreak_flg;

void (*callback_np[4]) (void);


void BBREAK_init(uint8_t port, uint8_t pin, bbmsk8_t msk, void (*callback)(void)){

    if (! callback)
    {
        /* check to make sure the function pointer is valid */
    }

    if(port > 10 || pin > 8){
        //bad news bears-
        //error, invalid pin/port combo
    }

    DEBOUNCE_init(port, pin, DB_RISING, BBREAK_DEBOUNCE_INTERVAL, bbreak_flg, msk);

    if(msk == BBMSK0){
        (callback_np[0]) = callback;
    }
    else if(msk == BBMSK1){
        (callback_np[1]) = callback;
    }
    else if(msk == BBMSK2){
        (callback_np[2]) = callback;
    }
    else if(msk == BBMSK3){
        (callback_np[3]) = callback;
    }
    else {
        /* Create a default error callback */
    }
}

void BBREAK_debounce(bbmsk8_t msk){
    if(msk & BBMSK0){
        (*callback_np[0])();
    }
    if(msk & BBMSK1){
        (*callback_np[1])();
    }
    if(msk & BBMSK2){
        (*callback_np[2])();
    }
    if(msk & BBMSK3){
        (*callback_np[3]);
    }

    bbreak_flg = 0;
}

bbmsk8_t BBREAK_check(bbmsk8_t msk){
    return bbreak_flg;
}
