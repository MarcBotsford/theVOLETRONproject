/*
 * circbuf.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Marc
 */

#ifndef CIRCBUF_H_
#define CIRCBUF_H_

#include "msp.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *type definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef uint8_t cb_item8;

typedef enum {
    cb_no_error = 0,
    cb_null_pointer,
    cb_empty,
    cb_full,
    cb_malloc_failure,
} cbStatus_t;

typedef struct buf{
    cb_item8 * head;             // pointer to newest item
    cb_item8 * tail;             //pointer to oldest item
    cb_item8 * buffer;           //pointer to begining of the struct
    uint8_t len;                 //total length of the buffer
    uint8_t item_size;          //size of each item
    uint8_t cnt;                 //number of items currently in the buffer

}buf_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/* Note, these functions can handle 8 bit data only*/
cbStatus_t CIRCBUF_init(buf_t* buf, uint8_t len, uint8_t size);
cbStatus_t CIRCBUF_push(buf_t* buf, cb_item8  data);
cb_item8 CIRCBUF_pop(buf_t* buf);
cbStatus_t CIRCBUF_read(buf_t* buf, void * data);
cbStatus_t CIRCBUF_delete(buf_t* buf);


#endif /* CIRCBUF_H_ */
