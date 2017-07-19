/*
 * circbuf.c
 *
 *  Created on: Jul 18, 2017
 *      Author: Marc
 */
#include "circbuf.h"

void CIRCBUF_init(buf_t* buf, uint8_t len, uint8_t size){
    buf ->buffer = malloc(len * size);


    buf ->len = len;
    buf ->cnt = 0;
    buf ->item_size = size;
    buf ->head = buf -> buffer;
    buf ->tail = buf -> buffer;
}

void CIRCBUF_push(buf_t* buf, void* data){
    if(buf->cnt == buf -> len){
        // bad news bears
            //more specifically, an overflow.
    }

    memcpy(buf->head,data,buf->item_size);
    buf->head = buf->head + buf->item_size;
    if(buf->head == buf->buffer + (buf->len * buf->item_size)){
        buf -> head = buf -> buffer;
    }
    buf -> cnt++;

}

void* CIRCBUF_pop(buf_t* buf){

    void* data;
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
    free(buf->buffer);
}

void* CIRCBUF_read(buf_t* buf){
    void* data;

    memcpy(data,buf->head,buf->item_size);
    return data;
}



