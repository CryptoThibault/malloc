#include "libft_malloc.h"

t_malloc_data g_malloc = {NULL, NULL, NULL};

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void *_malloc(size_t size)
{
    int zone_type = get_zone_type(size);
    t_zone *zone;

    if (zone_type == TINY)
        zone = g_malloc.tiny;
    else if (zone_type == SMALL)
        zone = g_malloc.small;
    else
        return malloc_large(size);

    size_t block_size = (zone_type == TINY ? TINY_MAX : SMALL_MAX);

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

        if (z->block_count < BLOCKS_PER_ZONE) {
            t_block *new_block = create_block(z, size, block_size);
            return (void *)((char *)new_block + sizeof(t_block));
        }

        z = z->next;
    }

    t_zone *new_zone = create_zone(block_size, BLOCKS_PER_ZONE);
    if (!new_zone)
        return NULL;

    new_zone->block_count = 0;

    if (!zone) {
        if (zone_type == TINY)
            g_malloc.tiny = new_zone;
        else
            g_malloc.small = new_zone;
    } else {
        t_zone *last = zone;
        while (last->next)
            last = last->next;
        last->next = new_zone;
    }

    t_block *block = create_block(new_zone, size, block_size);
    return (void *)((char *)block + sizeof(t_block));
}

void *malloc(size_t size)
{
    void *ptr;

    pthread_mutex_lock(&g_malloc_mutex);
    ptr = _malloc(size);
    pthread_mutex_unlock(&g_malloc_mutex);

    return ptr;
}
