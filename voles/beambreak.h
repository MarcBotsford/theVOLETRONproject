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

/* Don't forget to add documentation */
bbmsk8_t BBREAK_check(bbmsk8_t msk);

void BBREAK_debounce(bbmsk8_t msk);

void BBREAK_init(uint8_t port, uint8_t pin, bbmsk8_t msk, void (*callback)(void) );

#endif /* BEAMBREAK_H_ */
