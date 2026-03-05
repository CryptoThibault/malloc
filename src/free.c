#include "libft_malloc.h"

void free(void *ptr) {
    if (!ptr)
        return;

    t_block *block = (t_block *)((char *)ptr - sizeof(t_block));

    if (block->size <= SMALL_MAX) {
        block->free = 1;
        return;
    }

    t_block *current = large;
    t_block *prev = NULL;

    while (current && current != block) {
        prev = current;
        current = current->next;
    }
    if (!current)
        return;

    if (!prev)
        large = current->next;
    else
        prev->next = current->next;

    size_t total_size = block->size + sizeof(t_block);
    size_t pagesize = sysconf(_SC_PAGESIZE);
    if (total_size % pagesize != 0)
        total_size = ((total_size / pagesize) + 1) * pagesize;

    munmap(block, total_size);
}
