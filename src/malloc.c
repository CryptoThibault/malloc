#include "libft_malloc.h"

t_malloc_data g_malloc = {NULL, NULL, NULL};

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void *_malloc(size_t size) {
    void *ptr = NULL;

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
                b->size = size;
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
    block->size = size;
    ptr = (void *)((char *)block + sizeof(t_block));

    return ptr;
}

void *malloc(size_t size) {
    void *ptr;

    pthread_mutex_lock(&g_malloc_mutex);
    ptr = _malloc(size);
    pthread_mutex_unlock(&g_malloc_mutex);

    return ptr;
}
