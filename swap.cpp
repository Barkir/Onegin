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

    if (el_size != 0)
    {
        switch(el_size)
        {
            case 7:
                hswap(el1, el2, &buf4, 4);
                hswap(el1, el2, &buf2, 2);
                hswap(el1, el2, &buf1, 1);
                // printf("swapped 7 bytes\n");
                break;
            case 6:
                hswap(el1, el2, &buf4, 4);
                hswap(el1, el2, &buf2, 2);
                // printf("swapped 6 bytes\n");
                break;
            case 5:
                hswap(el1, el2, &buf4, 4);
                hswap(el1, el2, &buf1, 1);
                // printf("swapped 5 bytes\n");
                break;
            case 4:
                hswap(el1, el2, &buf4, 4);
                // printf("swapped 4 bytes\n");
                break;
            case 3:
                hswap(el1, el2, &buf2, 2);
                hswap(el1, el2, &buf1, 1);
                // printf("swapped 3 bytes\n");
                break;
            case 2:
                hswap(el1, el2, &buf2, 2);
                // printf("swapped 2 bytes\n");
                break;
            case 1:
                hswap(el1, el2, &buf1, 1);
                // printf("swapped 1 byte\n");
                break;
            default:
                fprintf(stderr, "uswap error!");
                break;
        }
    }

}


void swap8(void * el1, void * el2)
{
    printf("swapped 1 byte\n");
    int8_t buf = 0;
    buf = *(int8_t *) el2;
    *(int8_t * ) el2 = *(int8_t *) el1;
    *(int8_t *) el1 = buf;
}

void swap16(void * el1, void * el2)
{
    // printf("swapped 2 byte\n");
    int16_t buf = 0;
    buf = *(int16_t *) el2;
    *(int16_t * ) el2 = *(int16_t *) el1;
    *(int16_t *) el1 = buf;
}

void swap32(void * el1, void  * el2)
{
    // printf("swapped 4 bytes\n");
    int32_t buf = 0;
    buf = *(int32_t *) el2;
    *(int32_t * ) el2 = *(int32_t *) el1;
    *(int32_t *) el1 = buf;
}

void swap64(void * el1, void * el2)
{
    // printf("swapped 8 bytes\n");
    int64_t buf = 0;
    buf = *(int64_t *) el2;
    *(int64_t *) el2 = *(int64_t *) el1;
    *(int64_t *) el1 = buf;
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
    memcpy(buf, el1, el_size);
    memcpy(el1, el2, el_size);
    memcpy(el2, buf, el_size);
    el1 += el_size;
    el2 += el_size;
}
