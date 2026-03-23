#include "libft_malloc.h"

static size_t show_blocks_mem(t_block *b)
{
    if (!b)
        return 0;

    size_t total = 0;

    while (b) {
        if (!b->free) {
            ft_printf("%p - %p : ",
                      (void *)((char *)b + sizeof(t_block)),
                      (void *)((char *)b + sizeof(t_block) + b->size));
            ft_putnbr_fd((int)b->size, 1);
            ft_printf(" bytes\n");
            total += b->size;
        }
        b = b->next;
    }

    return total;
}

void show_alloc_mem()
{
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

static void dump_hex(void *ptr, size_t size)
{
    unsigned char *data = (unsigned char *)ptr;
    size_t len = size < 16 ? size : 16;

    ft_putstr_fd("0x", 1);
    unsigned long addr = (unsigned long)ptr;
    char hex_addr[17];
    int i = 15;
    hex_addr[16] = '\0';
    while (i >= 0) {
        int digit = addr % 16;
        hex_addr[i--] = digit < 10 ? '0' + digit : 'a' + digit - 10;
        addr /= 16;
    }
    ft_putstr_fd(hex_addr, 1);
    ft_putstr_fd(": ", 1);

    for (size_t j = 0; j < len; j++) {
        int high = data[j] / 16;
        int low = data[j] % 16;
        ft_putchar_fd(high < 10 ? '0' + high : 'a' + high - 10, 1);
        ft_putchar_fd(low < 10 ? '0' + low : 'a' + low - 10, 1);
        ft_putchar_fd(' ', 1);
    }
    if (size > 16) {
        ft_putstr_fd("... (", 1);
        ft_putnbr_fd(size - 16, 1);
        ft_putstr_fd(" more bytes)", 1);
    }
    ft_putchar_fd('\n', 1);
}

static size_t show_blocks_mem_ex(t_block *b)
{
    if (!b)
        return 0;

    size_t total = 0;

    while (b) {
        if (!b->free) {
            void *ptr = (void *)((char *)b + sizeof(t_block));
            dump_hex(ptr, b->size);
            total += b->size;
        }
        b = b->next;
    }

    return total;
}

void show_alloc_mem_ex()
{
    size_t total = 0;
    t_zone *z = NULL;

    if (g_malloc.tiny) {
        ft_printf("TINY : %p\n", (void *)g_malloc.tiny);
        z = g_malloc.tiny;
        while (z) {
            total += show_blocks_mem_ex(z->blocks);
            z = z->next;
        }
    }
    if (g_malloc.small) {
        ft_printf("SMALL : %p\n", (void *)g_malloc.small);
        z = g_malloc.small;
        while (z) {
            total += show_blocks_mem_ex(z->blocks);
            z = z->next;
        }
    }
    if (g_malloc.large) {
        ft_printf("LARGE : %p\n", (void *)g_malloc.large);
        total += show_blocks_mem_ex(g_malloc.large);
    }
    ft_printf("Total : ");
    ft_putnbr_fd((int)total, 1);
    ft_printf(" bytes\n");
}