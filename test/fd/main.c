#include <stdio.h>
#include <string.h>
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

    ringbuf_memset(ringbuf, 'A', 255);
    int offset = ringbuf_findchr(ringbuf, 'A', 5);
    printf("offset : %d\r\n", offset);

    char array[10];
    memset(array, 'B', 10);
    ringbuf_memcpy_into(ringbuf, array, 10);
    offset = ringbuf_findchr(ringbuf, 'B', 6);
    printf("offset : %d\r\n", offset);

    char array2[11] = {0};
    ringbuf_memcpy_from(array2, ringbuf, 10);
    printf("%s\r\n", array2);

    ringbuf_reset(ringbuf);
    ringbuf_free(&ringbuf);
}
