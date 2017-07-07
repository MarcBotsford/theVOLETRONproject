/*
 * VI.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Marc
 */

#ifndef VI_H_
#define VI_H_

uint8_t lever_state_raw;
uint8_t nosepoke_state_raw;
uint8_t lever_state;
uint8_t nosepoke_state;
uint8_t chalenge_rating;
uint8_t breakpoint;

typedef uint8_t inputid_t;          // the id of a particular VI input device. assigned upon initialization of the device.
#define input0 0                    //names will be updated with more descriptive ones.
#define input1 1
#define input2 2
#define input3 3


void VI_lever_init(uint8_t port, uint8_t pin, uint8_t period, uint8_t* lever_state_raw, void(*callback)(void));
void VI_nosepoke_init(uint8_t port, uint8_t pin, uint8_t period, uint8_t* nosepoke_state_raw, void(*callback)(void));
uint8_t VI_get_state_raw(inputid_t id);
uint8_t VI_get_state(inputid_t id);
void VI_set_challange(uint8_t new_rating, uint8_t* chalenge_rating);
void VI_increment_challange(uint8_t incrementor, inputid_t id);
uint8_t VI_get_breakpoint(void);
void VI_set_mandatory_minimum_sentence(uint16_t time);                   // time is in seconds



#endif /* VI_H_ */
