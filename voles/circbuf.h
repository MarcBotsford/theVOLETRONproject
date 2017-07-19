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
    CB_NOERROR = 0,
    CB_NULLPTR,
    CB_EMPTY,
    CB_FULL,
    CB_MALLOC_FAIL,
} CB_Status;

typedef struct buf{
    cb_item * head;             // pointer to newest item
    cb_item * tail;             //pointer to oldest item
    cb_item * buffer;           //pointer to begining of the struct
    size_t len;                 //total length of the buffer
    uint8_t item_size;          //size of each item
    size_t cnt;                 //number of items currently in the buffer

}buf_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void CIRCBUF_init(buf_t* buf, uint8_t len, uint8_t size);
void CIRCBUF_push(buf_t* buf, cb_item * data);
void* CIRCBUF_pop(buf_t* buf);
CB_Status CIRCBUF_read(buf_t* buf, cb_item * data);
void CIRCBUF_delete(buf_t* buf);


#endif /* CIRCBUF_H_ */
