/*
 * circbuf.c
 *
 *  Created on: Jul 18, 2017
 *      Author: Marc
 */
#include "circbuf.h"
#include <stdlib.h>

void CIRCBUF_init(buf_t* buf, uint8_t len, uint8_t size) {

    if (! buf){
        /* handle error if buf is not declared, NULL */
        return CB_NULLPTR;
    }

    buf ->buffer = (cb_item*) malloc(len * sizeof(cb_item));

    buf->len = len;
    buf->cnt = 0;

    buf->head = buf->buffer;
    buf->tail = buf->buffer;
}

void CIRCBUF_push(buf_t* buf, void* data){
    if (! buf){
        /* handle error if buf is not declared, NULL */
        return CB_NULLPTR;
    }

    if(buf->cnt == buf->len){
        return CB_FULL;
    }
//    *data = *(buf->head);
    memcpy(buf->head, data, buf->item_size);

    buf->head++;
    //buf->head = buf->head + buf->item_size;
    if(buf->head == buf->buffer + (buf->len * buf->item_size)){
        buf -> head = buf -> buffer;
    }
    buf -> cnt++;

    return CB_NOERROR;
}

void* CIRCBUF_pop(buf_t* buf){

    void* data;

    if (! buf){
        /* handle error if buf is not declared, NULL */
        return CB_NULLPTR;
    }

    if(buf->cnt == 0){
        //unerflow
    }
    memcpy(data,buf->head,buf->item_size);
    buf ->tail = buf -> tail + buf ->item_size;
    if(buf->tail == buf->buffer + (buf->len * buf -> item_size)){
        buf-> tail = buf -> buffer;
    }
    buf->cnt--;

    return data;
}

void CIRCBUF_delete(buf_t* buf){
    if (! buf){
        /* handle error if buf is not declared, NULL */
        return CB_NULLPTR;
    }
    free((void *)buf->buffer);
}

CB_Status CIRCBUF_read(buf_t* buf, void * data){

    if (! buf){
        /* handle error if buf is not declared, NULL */
       return CB_NULLPTR;
    }

    memcpy(data, buf->head, buf->item_size);
    return CB_NOERROR;
}



