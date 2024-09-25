#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "swap.h"

void uswap(void * el1, void * el2, size_t el_size)
{
    int64_t buf8 = 0;
    int32_t buf4 = 0;
    int16_t buf2 = 0;
    int8_t buf1 = 0;

    for (el_size; el_size >= 8; el_size -= 8)
        hswap(el1, el2, &buf8, 8);
        // printf("swapped 8 bytes\n");
        el1 += el_size;
        el2 += el_size;

    size_t start = 4;

    while(start != 0)
    {
        buf8 = 0;
        if (el_size >= start)
        {
            printf("%lu bytes needed to swap, we swap %lu bytes.\n", el_size, start);
            hswap(el1, el2, &buf8, start);
            el1 += el_size;
            el2 += el_size;
            el_size -= start;
        }
        start /= 2;
    }

}

void dswap(void * el1, void * el2, size_t el_size)                  // default swap
{
    // printf("default swap");
    char * buf = (char*) calloc(el_size, sizeof(char));
    memcpy(buf, el1, el_size);
    memcpy(el1, el2, el_size);
    memcpy(el2, buf, el_size);
    free(buf);
}

void hswap(void * el1, void * el2, void * buf, size_t el_size)      // help swap (used only in uswap)
{
    // printf("____HSWAP____\n");
    // printf("el1 = %s\n", *((char**) el1));
    // printf("el2 = %s\n", *((char**) el2));

    // printf("__COPYING TO BUF__\n");
    memcpy(buf, el1, el_size);
    // printf("el1 = %s\n", *((char**) el1));
    // printf("el2 = %s\n", *((char**) el2));
    // printf("buf = %s\n", *((char**) buf));

    // printf("SWAPPING EL1 with EL2\n");
    memcpy(el1, el2, el_size);
    // printf("el1 = %s\n", *((char**) el1));
    // printf("el2 = %s\n", *((char**) el2));
    // printf("buf = %s\n", *((char**) buf));

    // printf("SWAPPING BUF WITH EL2\n");
    memcpy(el2, buf, el_size);
    // printf("el1 = %s\n", *((char**) el1));
    // printf("el2 = %s\n", *((char**) el2));
    // printf("buf = %s\n", *((char**) buf));

    // printf("FINAL RESULT\n");
    // printf("el1 = %s\n", *((char**) el1));
    // printf("el2 = %s\n", *((char**) el2));
    // printf("buf = %s\n", *((char**) buf));

}
