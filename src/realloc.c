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

    void *new = malloc(size);
    if (!new)
        return NULL;

    ft_memcpy(new, ptr,(block->size < size ? block->size : size));
    free(ptr);
    return new;
}