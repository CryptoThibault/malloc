#include "libft_malloc.h"

int main(void) {
    ft_printf("=== MALLOC TEST ===\n");

    ft_printf("TINY allocations:\n");
    void *p1 = malloc(10);
    void *p2 = malloc(50);
    void *p3 = malloc(100);
    show_alloc_mem();

    ft_printf("\nFree p2:\n");
    free(p2);
    show_alloc_mem();

    ft_printf("\nRealloc p1 to 60 (TINY):\n");
    p1 = realloc(p1, 60);
    show_alloc_mem();

    ft_printf("\nRealloc p3 to 200 (TINY -> SMALL):\n");
    p3 = realloc(p3, 200);
    show_alloc_mem();

    ft_printf("\nSMALL allocations:\n");
    void *s1 = malloc(200);
    void *s2 = malloc(500);
    void *s3 = malloc(1024);
    show_alloc_mem();

    ft_printf("\nFree s1 and s3:\n");
    free(s1);
    free(s3);
    show_alloc_mem();

    ft_printf("\nRealloc s2 to 1500 (SMALL -> LARGE):\n");
    s2 = realloc(s2, 1500);
    show_alloc_mem();

    ft_printf("\nRealloc s2 to 100 (LARGE -> TINY):\n");
    s2 = realloc(s2, 100);
    show_alloc_mem();

    ft_printf("\nLARGE allocations:\n");
    void *l1 = malloc(2048);
    void *l2 = malloc(4096);
    show_alloc_mem();

    ft_printf("\nFree l1:\n");
    free(l1);
    show_alloc_mem();

    ft_printf("\nFree all:\n");
    free(p1);
    free(p3);
    free(s2);
    free(l2);
    show_alloc_mem();

    return 0;
}

// int main() {
//     void *p[220];

//     for (int i = 0; i < 220; i++)
//         p[i] = malloc(10);

//     show_alloc_mem();
//     for (int i = 10; i < 220; i++)
//         free(p[i]);

//     return 0;
// }