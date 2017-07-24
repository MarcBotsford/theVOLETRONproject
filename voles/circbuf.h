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

typedef uint8_t cb_item;

typedef enum {
    cb_no_error = 0,
    cb_null_pointer,
    cb_empty,
    cb_full,
    cb_malloc_failure,
} cbStatus_t;

typedef struct buf{
    void * head;             // pointer to newest item
    void * tail;             //pointer to oldest item
    void * buffer;           //pointer to begining of the struct
    uint8_t len;                 //total length of the buffer
    uint8_t item_size;          //size of each item
    uint8_t cnt;                 //number of items currently in the buffer

}buf_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

cbStatus_t CIRCBUF_init(buf_t* buf, uint8_t len, uint8_t size);
cbStatus_t CIRCBUF_push(buf_t* buf, void * data);
void* CIRCBUF_pop(buf_t* buf);
cbStatus_t CIRCBUF_read(buf_t* buf, void * data);
cbStatus_t CIRCBUF_delete(buf_t* buf);


#endif /* CIRCBUF_H_ */
