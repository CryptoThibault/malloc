#include "libft_malloc.h"

void *_realloc(void *ptr, size_t size) {
    if (!ptr)
        return _malloc(size);

    if (size == 0) {
        _free(ptr);
        return NULL;
    }

    t_block *block = (t_block *)((char *)ptr - sizeof(t_block));
    int old_type = get_zone_type(block->size);
    int new_type = get_zone_type(size);

    if (block->size >= size) {
        if (old_type == new_type)
            return ptr;

        void *new_ptr = _malloc(size);
        if (!new_ptr)
            return NULL;

        ft_memcpy(new_ptr, ptr, size);
        _free(ptr);
        return new_ptr;
    }

    if (old_type == new_type && (old_type == TINY || old_type == SMALL)) {
        t_block *next = block->next;
        if (next && next->free && block->size + sizeof(t_block) + next->size >= size) {
            block->size += sizeof(t_block) + next->size;
            block->next = next->next;
            return ptr;
        }
    }

    void *new_ptr = _malloc(size);
    if (!new_ptr)
        return NULL;

    ft_memcpy(new_ptr, ptr, block->size);
    _free(ptr);
    return new_ptr;
}

void *realloc(void *ptr, size_t size) {
    void *new_ptr;

    pthread_mutex_lock(&g_malloc_mutex);
    new_ptr = _realloc(ptr, size);
    pthread_mutex_unlock(&g_malloc_mutex);

    return new_ptr;
}
