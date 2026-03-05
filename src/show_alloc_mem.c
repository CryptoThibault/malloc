#include "libft_malloc.h"
#include <stdio.h>

static size_t show_blocks_mem(t_block *b) {
    if (!b)
        return 0;

    t_block *head = b;
    t_block *tail = NULL;
    size_t total = 0;

    while (b) {
        total += b->size;
        tail = b;
        b = b->next;
    }

    printf("%p - %p : %zu bytes\n", (void *)head, (void *)tail, total);
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