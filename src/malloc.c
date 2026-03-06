#include "libft_malloc.h"

t_malloc_data g_malloc = {NULL, NULL, NULL};

void *malloc(size_t size) {
    int zone_type = get_zone_type(size);
    t_zone *zone = NULL;

    if (zone_type == TINY)
        zone = g_malloc.tiny;
    else if (zone_type == SMALL)
        zone = g_malloc.small;
    else
        return malloc_large(size);

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

    t_zone *new_zone = zoneset((zone_type == TINY ? TINY_MAX : SMALL_MAX), BLOCKS_PER_ZONE);
    if (!new_zone)
        return NULL;

    if (!zone) {
        if (size <= TINY_MAX)
            g_malloc.tiny = new_zone;
        else
            g_malloc.small = new_zone;
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
