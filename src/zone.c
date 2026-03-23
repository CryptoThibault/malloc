#include "libft_malloc.h"

int get_zone_type(size_t size) {
    if (size <= TINY_MAX)
        return TINY;
    else if (size <= SMALL_MAX)
        return SMALL;
    return LARGE;
}

t_zone *zoneset(size_t size, size_t n) {
    size_t total_size = (sizeof(t_block) + size) * n;
    size_t pagesize = sysconf(_SC_PAGESIZE);
    if (total_size % pagesize != 0)
        total_size = ((total_size / pagesize) + 1) * pagesize;
    void *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED)
        return NULL;
    
    t_zone *zone = (t_zone *)ptr;
    zone->size = total_size;
    zone->blocks = NULL;
    zone->next = NULL;

    t_block *current = NULL;
    for (size_t i = 0; i < n; i++) {
        t_block *block = (t_block *)((char *)ptr + sizeof(t_zone) + i * (sizeof(t_block) + size));
        block->size = 0;
        block->free = 1;
        block->next = NULL;
        if (!zone->blocks)
            zone->blocks = block;
        else
            current->next = block;
        current = block;
    }

    return zone;
}
