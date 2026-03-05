#include "libft_malloc.h"

t_zone *tiny = NULL;
t_zone *small = NULL;
t_block *large = NULL;

void *malloc(size_t size) {
    t_zone *zone = NULL;
    size_t size_zone;

    if (size <= TINY_MAX) {
        zone = tiny;
        size_zone = TINY_MAX;
    } else if (size <= SMALL_MAX) {
        zone = small;
        size_zone = SMALL_MAX;
    } else {
        return malloc_large(size);
    }

    t_zone *z = zone;
    while (z) {
        t_block *b = z->blocks;
        while (b) {
            if (b->free) {
                b->free = 0;
                return (void *)((char *)b + sizeof(t_block));
            }
            b = b->next;
        }
        z = z->next;
    }

    t_zone *new_zone = zoneset(size_zone, BLOCKS_PER_ZONE);
    if (!new_zone)
        return NULL;

    if (!zone) {
        if (size <= TINY_MAX)
            tiny = new_zone;
        else
            small = new_zone;
    } else {
        t_zone *last = zone;
        while (last->next)
            last = last->next;
        last->next = new_zone;
    }

    t_block *block = new_zone->blocks;
    block->free = 0;

    return (void *)((char *)block + sizeof(t_block));
}
