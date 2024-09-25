#ifndef SWAP_H
#define SWAP_H

void uswap(void * el1, void * el2, size_t el_size);
void dswap(void * el1, void * el2, size_t el_size);
void hswap(void * el1, void * el2, void * buf, size_t el_size);

#endif
