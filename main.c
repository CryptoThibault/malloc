#include "libft_malloc.h"

int main(void)
{
    void *p1 = malloc(42);
    void *p2 = malloc(50);
    show_alloc_mem();

    free(p1);
    show_alloc_mem();

    void *p3 = malloc(20);
    show_alloc_mem();

    free(p2);
    free(p3);

    return 0;
}