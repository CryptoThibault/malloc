#include "libft_malloc.h"

void free(void *ptr) {
    if (!ptr)
        return;
    
    t_block *b = (t_block *)((char *)ptr - sizeof(t_block));
    b->free = 1;
}
