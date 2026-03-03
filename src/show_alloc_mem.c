#include "libft_malloc.h"
#include <stdio.h>

void show_alloc_mem() {
    // int n = 64;
    // int m = 1024;
    // int N = 6400;
    // int M = 102400;

    // printf("TINY : %p\n");
    // while ()
    //     printf("%p - %p : %d bytes\n");
    // printf("SMALL : %p\n");
    // while ()
    //     printf("%p - %p : %d bytes\n");
    // printf("LARGE : %p\n");
    // while ()
    //     printf("%p - %p : %d bytes\n");
    // printf("Total : %d bytes\n");

    printf("[Show allocation memory]\n");
    t_block *current = head;
    while (current)
    {
        printf("Bloc: %p | size: %zu | %s\n",
               (char *)current + sizeof(t_block),
               current->size,
               current->free ? "free" : "used");
        current = current->next;
    }
}