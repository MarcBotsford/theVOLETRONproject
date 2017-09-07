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

    buf ->buffer = (cb_item8*) malloc(len * sizeof(cb_item8));
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
    Interrupt_disableMaster();
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

    if(buf->head == buf->buffer + (buf->len * buf->item_size)){
        buf -> head = buf -> buffer;
    }

     *(buf->head) = data;


    buf -> cnt++;

    Interrupt_enableMaster();
    return cb_no_error;
}

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
        return 0x00;
    }
    Interrupt_disableMaster();
    data = *(buf->tail);
    if(buf->cnt != 1){
        buf->tail ++;
    }
    if(buf->tail == buf->buffer + (buf->len * buf -> item_size)){
        buf-> tail = buf -> buffer;
    }

    buf->cnt--;
    Interrupt_enableMaster();

    return data;
}

cbStatus_t CIRCBUF_delete(buf_t* buf){
    if (! buf){
        /* handle error if buf is not declared, NULL */
        return cb_null_pointer;
    }
    free((void *)buf->buffer);

    return cb_no_error;
}

cbStatus_t CIRCBUF_read(buf_t* buf, void * data){

    if (! buf){
        /* handle error if buf is not declared, NULL */
       return cb_null_pointer;
    }
    Interrupt_disableMaster();

    memcpy(data, buf->head, buf->item_size);
    Interrupt_enableMaster();
    return cb_no_error;
}



