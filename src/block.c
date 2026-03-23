#include "libft_malloc.h"

t_block *create_block(t_zone *z, size_t size, size_t block_size)
{
    size_t stride = (sizeof(t_block) + block_size + 15) & ~15;

    char *base = (char *)z + sizeof(t_zone);
    base = (char *)(((size_t)base + 15) & ~15);

    char *addr = base + z->block_count * stride;

    t_block *b = (t_block *)addr;

    b->size = size;
    b->free = 0;
    b->next = NULL;

    if (!z->blocks)
        z->blocks = b;
    else {
        t_block *tmp = z->blocks;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = b;
    }

    z->block_count++;

    return b;
}