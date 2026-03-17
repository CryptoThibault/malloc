#include "libft_malloc.h"

static size_t show_blocks_mem(t_block *b) {
    if (!b)
        return 0;

    size_t total = 0;

    while (b) {
        ft_printf("%p - %p : ",
                  (void *)((char *)b + sizeof(t_block)),
                  (void *)((char *)b + sizeof(t_block) + b->size));
        ft_putnbr_fd((int)b->size, 1);
        ft_printf(" bytes\n");
        total += b->size;
        b = b->next;
    }

    return total;
}

void show_alloc_mem() {
    size_t total = 0;
    t_zone *z = NULL;

    if (g_malloc.tiny) {
        ft_printf("TINY : %p\n", (void *)g_malloc.tiny);
        z = g_malloc.tiny;
        while (z) {
            total += show_blocks_mem(z->blocks);
            z = z->next;
        }
    }
    if (g_malloc.small) {
        ft_printf("SMALL : %p\n", (void *)g_malloc.small);
        z = g_malloc.small;
        while (z) {
            total += show_blocks_mem(z->blocks);
            z = z->next;
        }
    }
    if (g_malloc.large) {
        ft_printf("LARGE : %p\n", (void *)g_malloc.large);
        total += show_blocks_mem(g_malloc.large);
    }
    ft_printf("Total : ");
    ft_putnbr_fd((int)total, 1);
    ft_printf(" bytes\n");
}