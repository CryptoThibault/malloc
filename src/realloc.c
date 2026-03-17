#include "libft_malloc.h"

void *realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    t_block *block = (t_block *)((char *)ptr - sizeof(t_block));

    if (block->size >= size)
        return ptr;

    t_block *next = block->next;

    if (next && next->free && block->size + sizeof(t_block) + next->size >= size) {
        block->size += sizeof(t_block) + next->size;
        block->next = next->next;
        return ptr;
    }

    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;

    ft_memcpy(new_ptr, ptr, block->size);
    free(ptr);
    return new_ptr;
}