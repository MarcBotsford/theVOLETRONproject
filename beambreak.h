/*
 * beambreak.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */

#ifndef BEAMBREAK_H_
#define BEAMBREAK_H_

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *prepocessor constants
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define BROKEN (0x01)
#define UNBROKEN (0x00)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum beambreak_id{
    bbreak_0,
    bbreak_1,
    bbreak_2,
    bbreak_3
}bbreakid_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint8_t BBREAK_check(bbreakid_t id);
uint8_t BBREAK_debounce(bbreakid_t id, uint8_t interval);
void BBREAK_init(uint8_t port, uint8_t pin, bbreakid_t given_id);


#endif /* BEAMBREAK_H_ */
