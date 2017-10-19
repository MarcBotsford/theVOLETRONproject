/*
 * circbuf.c
 *
 *  Created on: Jul 18, 2017
 *      Author: Marc
 */
#include "circbuf.h"
#include <stdlib.h>
#include "interrupt.h"

cbStatus_t CIRCBUF_init(buf_t* buf, uint8_t len) {

    if (! buf){
        /* handle error if buf is not declared, NULL */
        return cb_null_pointer;
    }

    cb_item8 *temp = (cb_item8*) malloc(len * sizeof(cb_item8));
    buf->buffer = temp;
    if(! buf -> buffer){
        return cb_malloc_failure;
    }

    buf->len = len;
    buf->cnt = 0;
    buf->head = buf->buffer;
    buf->tail = buf->buffer;

    return cb_no_error;
}

cbStatus_t CIRCBUF_push(buf_t* buf, cb_item8  data){
    if (! buf){
        /* handle error if buf is not declared, NULL */
        return cb_null_pointer;
    }

    if(buf->cnt == buf->len){
        return cb_full;
    }
//    Interrupt_disableMaster();


    if(buf->cnt != 0){
    buf->head++;
    }

    if(buf->head == buf->buffer){
        buf -> head = buf -> buffer;
    }

     *(buf->head) = data;


    buf -> cnt++;

    return cb_no_error;
}

#define FOS_DEBUG
#ifdef FOS_DEBUG
cb_item8 CIRCBUF_pop(buf_t* buf){
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

    data = *(buf->tail);
    if(buf->cnt != 1){
        buf->tail ++;
    }
    if(buf->tail == buf->buffer){
        buf-> tail = buf -> buffer;
    }

    buf->cnt--;


    return data;
}
#endif

cbStatus_t CIRCBUF_delete(buf_t* buf){
    if (! buf){
        /* handle error if buf is not declared, NULL */
        return cb_null_pointer;
    }
    free((void *)buf->buffer);

    return cb_no_error;
}


/*
 * note, this currently dosn't work
 */
cbStatus_t CIRCBUF_read(buf_t* buf, void * data){

    if (! buf){
        /* handle error if buf is not declared, NULL */
       return cb_null_pointer;
    }
    Interrupt_disableMaster();

//    memcpy(data, buf->head, buf->item_size);
    Interrupt_enableMaster();
    return cb_no_error;
}



