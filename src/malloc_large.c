#include "libft_malloc.h"

void *malloc_large(size_t size) {
    t_block *current = large;
    t_block *last = NULL;
    while (current) {
        last = current;
        if (current->free == 1 && current->size >= size) {
            current->free = 0;
            return (void *)((char *)current + sizeof(t_block));
        }
        current = current->next;
    }

    size_t total_size = size + sizeof(t_block);
    size_t pagesize = sysconf(_SC_PAGESIZE);
    if (total_size % pagesize != 0)
        total_size = ((total_size / pagesize) + 1) * pagesize;
    void *ptr = mmap(
        NULL,
        total_size,
        PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS | MAP_PRIVATE,
        -1,
        0
    );

    if (ptr == MAP_FAILED)
        return NULL;

    t_block *b = (t_block *)ptr;
    b->size = size;
    b->free = 0;
    b->next = NULL;

    if (large == NULL)
        large = b;
    else
        last->next = b;
    return (void *)((char *)b + sizeof(t_block));
}
