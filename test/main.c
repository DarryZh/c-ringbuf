#include <stdio.h>
#include "ringbuf.h"

int main(int argc, void **args)
{
    ringbuf_t ringbuf = ringbuf_new(10);
    size_t size = ringbuf_buffer_size(ringbuf);
    size_t cap = ringbuf_capacity(ringbuf);
    size_t free = ringbuf_bytes_free(ringbuf);
    size_t used = ringbuf_bytes_used(ringbuf);
    printf("buf size : %ld  capacity size : %ld  free : %ld  used: %ld \r\n", size, cap, free, used);

    int ret;
    ret = ringbuf_is_full(ringbuf);
    printf("full : %d\r\n", ret);
    ret = ringbuf_is_empty(ringbuf);
    printf("empty : %d\r\n", ret);

    const void *tail = ringbuf_tail(ringbuf);
    const void *head = ringbuf_head(ringbuf);
    printf("tail : %p  head : %p\r\n", tail, head);

    ringbuf_reset(ringbuf);
    ringbuf_free(&ringbuf);
}
