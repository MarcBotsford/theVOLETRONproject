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
    uint8_t cnt;                 //number of items currently in the buffer

}buf_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *function definitions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/* Note, these functions can handle 8 bit data only*/
cbStatus_t CIRCBUF_init(buf_t* buf, uint8_t len);
cbStatus_t CIRCBUF_push(buf_t* buf, cb_item8  data);
cb_item8 CIRCBUF_pop(buf_t* buf);
cbStatus_t CIRCBUF_read(buf_t* buf, void * data);
cbStatus_t CIRCBUF_delete(buf_t* buf);

//NVIC_SetPriority()
#ifdef MARC_DEBUG
__attribute__((always_inline))
static inline cb_item8 CIRCBUF_pop(buf_t* buf){
    cb_item8 data;

    if (! buf){
        /* handle error if buf is not declared, NULL */
        /* placeholder error, remember to make a better one*/
        while(1);
    }
    if(buf->cnt == 0){
        /* empty buffers cannot be popped from*/
        /* placeholder error, remember to make a better one*/
//        while(1);
        return 0xFF;
    }
    Interrupt_disableMaster();
    data = *(buf->tail);
    if(buf->cnt != 1){
        buf->tail ++;
    }
    if(buf->tail == buf->buffer){
        buf-> tail = buf -> buffer;
    }

    buf->cnt--;
    Interrupt_enableMaster();

    return data;
}
#endif


#endif /* CIRCBUF_H_ */
