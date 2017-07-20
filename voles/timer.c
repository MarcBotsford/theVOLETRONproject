/*
 * timer.c
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */
#include "msp.h"
#include "timer.h"




#if 0
void (*callback_A0[7]) (void);
void (*callback_A1[7]) (void);
void (*callback_A2[7]) (void);
void (*callback_A3[7]) (void);

uint32_t cnt_A0[7];
uint32_t cnt_A1[7];
uint32_t cnt_A2[7];
uint32_t cnt_A3[7];

uint32_t cnt_trg_0[7];
uint32_t cnt_trg_1[7];
uint32_t cnt_trg_2[7];
uint32_t cnt_trg_3[7];
#endif


volatile alarm_t TA [4][7];

volatile clkStatus_t TA_status[4];



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Internal function deffinitions
 *
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_load_devider(uint8_t devider, tim_t clk_chanel);

    //higher max precision
clkData_t TIMER_calculate_deviders_s(uint32_t period, tim_t clk_chanel);
    //max precision is garbage ( ~= .5 seconds)
clkData_t TIMER_calculate_deviders_l(uint32_t period);


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *
 *
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef enum {
    CCR_CHANNEL_0 = 0,
    CCR_CHANNEL_1,
    CCR_CHANNEL_2,
}CCR_Ch_t;



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *Functions
 *
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timerr_t TIMER_config_raw(uint16_t ccr, uint8_t devider, tim_t clk_chanel, uint8_t ccr_chanel){
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
    TIMER_AG(CLK_CHANEL_H)->CCR[ccr_chanel] = ccr;
        //use smclk and enable interrupts
    TIMER_AG(CLK_CHANEL_H)->CTL &= ~(TIMER_A_CTL_SSEL_MASK);
    TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_IE;
        //enable interrupts
    TIMER_AG(CLK_CHANEL_H)->CCTL[ccr_chanel] |= TIMER_A_CCTLN_CCIE;




    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_config_l(uint32_t period, tim_t clk_chanel, uint8_t ccr_chanel){
        //typechecking
    if(ccr_chanel > 6){
        return timer_invalid_ccr_chanel;
    }
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    timerr_t a;
    clkData_t data;

    data = TIMER_calculate_deviders_s(period, clk_chanel);


    a = TIMER_config_raw(data.CCR, data.devider, clk_chanel, ccr_chanel);


#if 0
    switch(clk_chanel){
    case TA0:
        cnt_trg_0[ccr_chanel] = data.trig_cnt;
        break;
    case TA1:
        cnt_trg_1[ccr_chanel] = data.trig_cnt;
        break;
    case TA2:
        cnt_trg_2[ccr_chanel] = data.trig_cnt;
        break;
    case TA3:
        cnt_trg_3[ccr_chanel] = data.trig_cnt;
        break;
    }
#endif

    TA[CLK_CHANEL_S][ccr_chanel].trigger_cnt = data.trig_cnt;

    return a;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_config(uint32_t period, tim_t clk_chanel, uint8_t ccr_chanel){
    /*
     * parameter checking
     */
    if(ccr_chanel > 6){
        return timer_invalid_ccr_chanel;
    }
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }
    if(TA[CLK_CHANEL_S][ccr_chanel].use_state != cc_unused){
        return timer_clk_unavailable;
    }

    clkData_t dat;
    dat = TIMER_calculate_deviders_s(period, clk_chanel);
    timerr_t err;
    clkStatus_t state = TA_status[CLK_CHANEL_S];

    if(state == cs_unused){
        err = TIMER_config_cnt_raw(dat.CCR , dat.devider, clk_chanel, ccr_chanel, dat.trig_cnt);
        TA_status[CLK_CHANEL_S] = cs_continuous;
    }
    else if(state == cs_continuous){
        err =TIMER_config_ccr_raw_cnt(dat.CCR, clk_chanel, ccr_chanel, dat.trig_cnt);
    }
    else{
        return timer_ccr_chanel_buisy;
    }

    return err;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

clkData_t TIMER_calculate_deviders_s(uint32_t period, tim_t clk_chanel){
    clkData_t dat;
    dat.devider = DEV_1MS;
    period = (period *CCR_1MS) + TIMER_AG(CLK_CHANEL_H)->R;
    dat.trig_cnt = 0;
    while(period > 0xFFFF){
        dat.trig_cnt ++;
        period -= 0xFFFF;
    }
    dat.CCR = period;

    return dat;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

clkData_t TIMER_calculate_deviders_l(uint32_t period){
    clkData_t dat;

          dat.trig_cnt = period / CNT_PRD_MS;
          dat.CCR = 0xFFFF;
          dat.devider = TIMER_DEV_64;

    return dat;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_config_ccr_raw_cnt(uint16_t ccr, tim_t clk_chanel, uint8_t ccr_chanel, uint32_t cnt_gl){
        //type checking
    if(ccr_chanel > 6){
        return timer_invalid_ccr_chanel;
    }
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    TA[CLK_CHANEL_S][ccr_chanel].trigger_cnt = cnt_gl;
    TIMER_AG(CLK_CHANEL_H)->CCTL[ccr_chanel] |= TIMER_A_CCTLN_CCIE;
    TIMER_AG(CLK_CHANEL_H)->CCR[ccr_chanel] = ccr;


    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_load_devider(uint8_t devider, tim_t clk_chanel){

    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    if(devider <= 3 ){
        TIMER_AG(CLK_CHANEL_H)->CTL |= (devider << 6);
        return timer_no_error;
    }

    switch(devider){
    case TIMER_DEV_5:
        TIMER_AG(CLK_CHANEL_H)->CTL &= ~(TIMER_A_CTL_ID_MASK);
        TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_ID__1;

        TIMER_AG(CLK_CHANEL_H)->EX0 = 0x0004;
        return timer_no_error;
    case TIMER_DEV_7:
        TIMER_AG(CLK_CHANEL_H)->CTL &= ~(TIMER_A_CTL_ID_MASK);
        TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_ID__1;

        TIMER_AG(CLK_CHANEL_H)->EX0 = 0x0006;
        return timer_no_error;
    case TIMER_DEV_10:
        TIMER_AG(CLK_CHANEL_H)->CTL &= ~(TIMER_A_CTL_ID_MASK);
        TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_ID__2;

        TIMER_AG(CLK_CHANEL_H)->EX0 = 0x0004;
        return timer_no_error;
    case TIMER_DEV_16:
        TIMER_AG(CLK_CHANEL_H)->CTL &= ~(TIMER_A_CTL_ID_MASK);
        TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_ID__4;

        TIMER_AG(CLK_CHANEL_H)->EX0 = 0x0003;
        return timer_no_error;
    case TIMER_DEV_32:
        TIMER_AG(CLK_CHANEL_H)->CTL &= ~(TIMER_A_CTL_ID_MASK);
        TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_ID__8;

        TIMER_AG(CLK_CHANEL_H)->EX0 = 0x0003;
        return timer_no_error;
    case TIMER_DEV_40:
        TIMER_AG(CLK_CHANEL_H)->CTL &= ~(TIMER_A_CTL_ID_MASK);
        TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_ID__8;

        TIMER_AG(CLK_CHANEL_H)->EX0 = 0x0004;
    case TIMER_DEV_64:
        TIMER_AG(CLK_CHANEL_H)->CTL &=~(TIMER_A_CTL_ID_MASK);
        TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_ID__8;

        TIMER_AG(CLK_CHANEL_H)->EX0 = 0x0007;
        return timer_no_error;
    default:
        return timer_invalid_devider;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_begin(tim_t clk_chanel){
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    TIMER_AG(CLK_CHANEL_H)->CTL &= ~(TIMER_A_CTL_MC_MASK);
    TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_MC__UP;


    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timerr_t TIMER_pause(tim_t clk_chanel){

    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    TIMER_AG(CLK_CHANEL_H)->CTL &= ~(TIMER_A_CTL_MC_MASK);
    TIMER_AG(CLK_CHANEL_H)->CTL |= TIMER_A_CTL_MC__STOP;

    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timerr_t TIMER_reset_raw(tim_t clk_chanel, uint32_t ccr, uint8_t devider, uint8_t ccr_chanel){
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    TIMER_AG(CLK_CHANEL_H)->CTL |= TACLR;

    TIMER_config_raw(ccr, devider, clk_chanel, ccr_chanel);


    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timerr_t TIMER_set_callback(tim_t clk_chanel,uint8_t ccr_chanel, void (*callback)(void)){
        //type checking
    if(!(clk_chanel == TA0 || clk_chanel == TA1 || clk_chanel == TA2 || clk_chanel == TA3)){
        return timer_invalid_chanel;
    }

    if(ccr_chanel > 6){
        return timer_invalid_ccr_chanel;
    }

#if 0
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
#endif

    TA[CLK_CHANEL_S][ccr_chanel].callback = callback;



    return timer_no_error;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


timid_t TIMER_request(uint32_t period, void(*callback)){

    return task0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timid_t TIMER_request_repeat(uint32_t period, void(*callback), uint32_t reps){

    return task0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_kill(uint8_t taskid){

    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

timerr_t TIMER_config_cnt_raw(uint16_t ccr, uint8_t devider,tim_t clk_chanel, uint8_t ccr_chanel, uint32_t cnt_gl){
    timerr_t e;
    e = TIMER_config_raw(ccr,devider,clk_chanel,ccr_chanel);
    if(e)
        return e;
#if 0
    switch(clk_chanel){
    case TA0:
        cnt_trg_0[clk_chanel] = cnt_gl;
        break;
    case TA1:
        cnt_trg_1[clk_chanel] = cnt_gl;
        break;
    case TA2:
        cnt_trg_2[clk_chanel] = cnt_gl;
        break;
    case TA3:
        cnt_trg_3[clk_chanel] = cnt_gl;
        break;
    }
#endif

    TA[CLK_CHANEL_S][ccr_chanel].trigger_cnt = cnt_gl;

    return timer_no_error;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void TA1_N_IRQHandler(void){
    uint8_t i;
    TIMER_A1 -> CTL &= ~(TAIFG);
    for(i = 0; i<=6;i++){
        if(TIMER_A1->CCTL[i] & CCIFG && TIMER_A1->CCTL[i] & CCIE){
            TIMER_A1->CCTL[i] &= ~(CCIFG);


            if(TA[1][i].cnt == TA[1][i].trigger_cnt){
                TA[1][i].cnt = 0;
                (*TA[1][i].callback)();
            }
            TA[1][i].cnt++;
        }
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void TA0_N_IRQHandler(void){
    uint8_t i;
    TIMER_A0 -> CTL &= ~(TAIFG);
    for(i = 0; i<=6;i++){
        if(TIMER_A0->CCTL[i] & CCIFG && TIMER_A0->CCTL[i] & CCIE){
            TIMER_A0->CCTL[i] &= ~(CCIFG);


            if(TA[0][i].cnt == TA[0][i].trigger_cnt){
                TA[0][i].cnt = 0;
                (*TA[0][i].callback)();
            }
            TA[0][i].cnt++;
        }
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void TA2_N_IRQHandler(void){
    uint8_t i;
    TIMER_A2 -> CTL &= ~(TAIFG);
    for(i = 0; i<=6;i++){
        if(TIMER_A2->CCTL[i] & CCIFG && TIMER_A2->CCTL[i] & CCIE){
            TIMER_A2->CCTL[i] &= ~(CCIFG);


            if(TA[2][i].cnt == TA[2][i].trigger_cnt){
                TA[2][i].cnt = 0;
                (*TA[2][i].callback)();
            }
            TA[2][i].cnt ++;
        }
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void TA3_N_IRQHandler(void){
    uint8_t i;
    TIMER_A3 -> CTL &= ~(TAIFG);
    for(i = 0; i<=6;i++){
        if(TIMER_A3->CCTL[i] & CCIFG && TIMER_A3->CCTL[i] & CCIE){
            TIMER_A3->CCTL[i] &= ~(CCIFG);

            if(TA[3][i].cnt == TA[3][i].trigger_cnt){
                TA[3][i].cnt = 0;
//                (*callback_A3[i])();
                (*TA[3][i].callback)();
            }
            TA[3][i].cnt ++;
        }
    }
}
