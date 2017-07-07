/*
 * doors.h
 *
 *  Created on: Jun 30, 2017
 *      Author: Marc
 */

#ifndef DOORS_H_
#define DOORS_H_

//#include "msp.h"

#define DOOR_CNT 2            //static, corresponds to the number of doors in the application.


uint8_t door_state[DOOR_CNT];

typedef uint8_t doorid_t;
#define DOOR0 0
#define DOOR1 1

typedef uint8_t doorstt_t;
#define OPEN 0
#define CLOSED 1
#define OPENING 2
#define CLOSEING 3
#define JAMMED 4

doorstt_t DOOR_get_state(doorid_t id);
void      DOOR_init(doorid_t id);
doorstt_t DOOR_unjam(doorid_t id);
doorstt_t DOOR_open(doorid_t id);
doorstt_t DOOR_close(doorid_t id);
void      DOOR_init_mate_timer(doorid_t id, uint8_t time);
void      DOOR_init_litter_timer(doorid_t id, uint8_t time);


static uint32_t doors_allocated;

#define DOOR_AVAILABLE (0x0)
#define DOOR_RESERVED (0x1)

TID_t allocate_door(){
   for(){
   if (tempdoor % 2 ==  DOOR_AVAILABLe)
   {

   }
   tempdoor= doors_allocate >> 1;
   }
   // i which timer availble
   }
}

#endif /* DOORS_H_ */
