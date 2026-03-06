#include "libft_malloc.h"

static size_t show_blocks_mem(t_block *b) {
    if (!b)
        return 0;

    size_t total = 0;

    while (b) {
        printf("%p - %p : %zu bytes\n",
               (void *)((char *)b + sizeof(t_block)),
               (void *)((char *)b + sizeof(t_block) + b->size),
               b->size);
        total += b->size;
        b = b->next;
    }

    return total;
}

void show_alloc_mem() {
    size_t total = 0;
    t_zone *z = NULL;

    if (tiny) {
        printf("TINY : %p\n", (void *)tiny);
        z = tiny;
        while (z) {
            total += show_blocks_mem(z->blocks);
            z = z->next;
        }
    }
    if (small) {
        printf("SMALL : %p\n", (void *)small);
        z = small;
        while (z) {
            total += show_blocks_mem(z->blocks);
            z = z->next;
        }
    }
    if (large) {
        printf("LARGE : %p\n", (void *)large);
        total += show_blocks_mem(large);
    }
    printf("Total : %zu bytes\n", total);
}