/**
 * @file timer.h
 * @a module to handle timer resources
 *
 * This module can be used to configure and allocate timers.It has functions used to either statically
 * or dynamically allocate timer resources.
 * Functions to statically allocate resources take the timer that the user wants to
 * use as an argument.
 * When using the dynamically allocated version the user does not specify a timer.
 * Instead the system automatically chooses an unused one.
 *
 * @author Nelson Botsford
 * @date April 2, 2017
 *
 */

#ifndef TIMER_H_
#define TIMER_H_

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * arrays of pointers to callback functions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#if 0

void* callback_A[6];
void* callback_32;

#endif

#define TIM_TAxCLK (0x0000)
#define TIM_ACLK   (0x0100)
#define TIM_SMCLK  (0x0200)
#define TIM_INCLK  (0x0300)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * custom data types
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum timer_chanels{          //used mostly for internal functions to identify timers.
    TA0,
    TA1,
    TA2,
    TA3,
    TA4,
    TA5,
    TA6,
    T32
}tim_t;

typedef enum tim_err{
    timer_no_error,
    began_uninitialized_clock,
    pause_uninitialized_clodk,
    began_running_clock,
    pause_paused_clock,
    timer_invalid_devider
}timerr_t;

typedef enum tim_id{
    all_timers_buisy,
    task0,
    task1,
    task2
}timid_t;

typedef volatile uint16_t* hreg16_t;

#if 0

uint8_t timer_available = 0;

#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_init_raw(uint32_t ccr, uint8_t devider,tim_t clk_chanel);
timerr_t TIMER_init(uint32_t time, tim_t clk_chanel);
timerr_t TIMER_begin(tim_t clk_chanel);
timerr_t TIMER_pause(tim_t chanel);
timerr_t TIMER_reset_raw(tim_t chanel, uint32_t ccr);
timerr_t TIMER_set_callback(tim_t chanel, void(*callback));                     //note to self: figure out if this syntax is even close to correct
timid_t TIMER_request(uint32_t period, void(*callback));
timid_t TIMER_request_repeat(uint32_t period, void(*callback), uint32_t reps);
timerr_t TIMER_kill(uint8_t taskid);




#endif /* TIMER_H_ */