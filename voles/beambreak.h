/*
 * beambreak.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */

#ifndef BEAMBREAK_H_
#define BEAMBREAK_H_

#include <stdint.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *prepocessor constants
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define BROKEN (0x01)
#define UNBROKEN (0x00)

/* All Time units in msecsonds */
#define BBREAK_DEBOUNCE_INTERVAL (50)
#define BBMSK0 (0x01)
#define BBMSK1 (0x02)
#define BBMSK2 (0x04)
#define BBMSK3 (0x08)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {
    bbreak_0,
    bbreak_1,
    bbreak_2,
    bbreak_3
} bbreakid_t;

typedef uint8_t bbmsk8_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


bbmsk8_t BBREAK_check(bbmsk8_t msk);

/*
 * parameters: msk: the unique mask that corresponds to the beam break mask being debounced. this mask is set in software and defined by the programmer
 */

void BBREAK_debounce(bbmsk8_t msk);


/*
 *parameters: port: port on which the beambreak is attached
 *parameters: pin: pin on which the beambreak is attached:
 *parameters: msk: a beam break mask. a unique one should be assigned to each beam break module.
 *parameters: callback: a void callback function to be called when the beam is broken.
 *
 * initializes and starts the beambreak module on the specified pin with the specified callback function
 */
void BBREAK_init(uint8_t port, uint8_t pin, bbmsk8_t msk, void (*callback)(void) );

#endif /* BEAMBREAK_H_ */
