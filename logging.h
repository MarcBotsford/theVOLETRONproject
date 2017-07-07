/*
 * logging.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */

#ifndef LOGGING_H_
#define LOGGING_H_

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type deffinitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct log{
    /*
     *
     *The struct will specify the type of event it is logging (a door state chage, a breakpoint
     * reached, a regular poll, etc), plus any interesting data about the event
     *
     */
}log_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void LOG_push(log_t data);


#endif /* LOGGING_H_ */
