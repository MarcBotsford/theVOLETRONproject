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


// note to self, smclk frequency is 4MHz

#ifndef TIMER_H_
#define TIMER_H_

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * includes
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "math.h"




#define TIM_TAxCLK (0x0000)
#define TIM_ACLK   (0x0100)
#define TIM_SMCLK  (0x0200)
#define TIM_INCLK  (0x0300)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * type definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum timer_chanels{          //used mostly for internal functions to identify timers.
    TA0 = (TIMER_A0_BASE + 0),
    TA1 = (TIMER_A1_BASE + 1),
    TA2 = (TIMER_A2_BASE + 2),
    TA3 = (TIMER_A3_BASE + 3)
}tim_t;

typedef enum tim_err{
    timer_no_error = 0,
    began_uninitialized_clock,
    pause_uninitialized_clodk,
    began_running_clock,
    pause_paused_clock,
    timer_invalid_devider,
    timer_invalid_chanel,
    timer_invalid_ccr_chanel,
    timer_ccr_chanel_buisy,
    timer_clk_unavailable
}timerr_t;

typedef enum tim_id{
    all_timers_buisy,
    task0,
    task1,
    task2
}timid_t;

typedef struct{
    tim_t clock_chanel;
    uint8_t ccr_chanel;
}timerTaskid_t;

typedef struct _clk_data{
    uint8_t devider;
    uint16_t CCR;
    uint32_t trig_cnt;
}clkData_t;

typedef enum {
    cc_unused = 0,
    cc_pwm,
    cc_permanent,
    cc_instance_task,
    cc_repeated_task
}ccrStatus_t;

typedef enum{
    cs_unused = 0,
    cs_up,
    cs_continuous
}clkStatus_t;


//typedef

//typedef volatile uint16_t* hreg16_t;

#define TIMER_DEV_8 (0x03)
#define TIMER_DEV_4 (0x02)
#define TIMER_DEV_2 (0x01)
#define TIMER_DEV_1 (0x00)

#define TIMER_DEV_5 (5)
#define TIMER_DEV_7 (7)
#define TIMER_DEV_10 (10)
#define TIMER_DEV_16 (16)
#define TIMER_DEV_32 (32)
#define TIMER_DEV_40 (40)
#define TIMER_DEV_64 (64)

typedef void (*cb_func_t) (void);

#define CLK_CHANEL_H (clk_chanel & 0xFFFFFFF0)
#define CLK_CHANEL_S (clk_chanel & 0x00000003)

typedef struct {
    uint32_t trigger_cnt;
    uint32_t cnt;
    cb_func_t callback;
    ccrStatus_t use_state;

} alarm_t;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * preprocessor macros
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define CNT_PRD_MS (557/*.056*/)

#define DEV_1MS (TIMER_DEV_40)
#define CCR_1MS (300)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_config_raw(uint16_t ccr, uint8_t devider,tim_t clk_chanel, uint8_t ccr_chanel);
timerr_t TIMER_config_l(uint32_t period, tim_t clk_chanel,uint8_t ccr_chanel);
timerr_t TIMER_config(uint32_t period, tim_t clk_chanel, uint8_t ccr_chanel);
timerr_t TIMER_config_ccr_raw_cnt(uint16_t ccr, tim_t clk_chanel, uint8_t ccr_chanel, uint32_t cnt_gl);
timerr_t TIMER_begin(tim_t clk_chanel);
timerr_t TIMER_pause(tim_t chanel);
timerr_t TIMER_reset_raw(tim_t chanel, uint32_t ccr, uint8_t devider, uint8_t ccr_chanel);
timerr_t TIMER_set_callback(tim_t clk_chanel,uint8_t ccr_chanel, void (*callback)(void));
timerTaskid_t TIMER_request(uint32_t period, void(*callback)(void));
timerTaskid_t TIMER_request_repeat(uint32_t period, void(*callback), uint32_t reps);
timerr_t TIMER_kill(timerTaskid_t taskid);
timerr_t TIMER_kill_raw(tim_t clk_chanel, uint8_t ccr_Chanel);
timerr_t TIMER_init(void);

timerr_t TIMER_config_cnt_raw(uint16_t ccr, uint8_t devider,tim_t clk_chanel, uint8_t ccr_chanel, uint32_t cnt_gl);
clkData_t TIMER_calculate_deviders_l(uint32_t period);

void TA0_N_IRQHandler(void);
void TA1_N_IRQHandler(void);
void TA2_N_IRQHandler(void);
void TA3_N_IRQHandler(void);
void TIMER_default_callback(void);


clkData_t TIMER_calculate_deviders(uint32_t period);
clkData_t TIMER_calculate_deviders_s(uint32_t period, tim_t clk_chanel);
#endif /* TIMER_H_ */
