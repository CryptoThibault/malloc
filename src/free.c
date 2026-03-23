#include "libft_malloc.h"

static t_block *find_prev_block(t_zone *zone, t_block *block) {
    if (!zone || !zone->blocks)
        return NULL;
    t_block *current = zone->blocks;
    while (current && current->next != block) {
        current = current->next;
    }
    return current;
}

void _free(void *ptr) {
    if (!ptr)
        return;

    t_block *block = (t_block *)((char *)ptr - sizeof(t_block));

    if (get_zone_type(block->size) == LARGE) {
        t_block *current = g_malloc.large;
        t_block *prev = NULL;

        while (current && current != block) {
            prev = current;
            current = current->next;
        }
        if (!current)
            return;

        if (!prev)
            g_malloc.large = current->next;
        else
            prev->next = current->next;

        size_t total_size = block->size + sizeof(t_block);
        size_t pagesize = sysconf(_SC_PAGESIZE);
        if (total_size % pagesize != 0)
            total_size = ((total_size / pagesize) + 1) * pagesize;

        munmap(block, total_size);
        return;
    }

    block->free = 1;

    t_zone *zone = (get_zone_type(block->size) == TINY) ? g_malloc.tiny : g_malloc.small;
    t_block *prev = find_prev_block(zone, block);

    if (block->next && block->next->free) {
        block->size += sizeof(t_block) + block->next->size;
        block->next = block->next->next;
    }

    if (prev && prev->free) {
        prev->size += sizeof(t_block) + block->size;
        prev->next = block->next;
    }
}

void free(void *ptr) {
    pthread_mutex_lock(&g_malloc_mutex);
    _free(ptr);
    pthread_mutex_unlock(&g_malloc_mutex);
}
