#include "libft_malloc.h"

int main(void) {
    ft_printf("=== TEST TINY MALLOC ===\n");
    void *p1 = malloc(10);
    void *p2 = malloc(50);
    void *p3 = malloc(100);
    show_alloc_mem();

    ft_printf("\n=== FREE p2 ===\n");
    free(p2);
    show_alloc_mem();

    ft_printf("\n=== ADDITIONAL TINY MALLOC ===\n");
    void *p4 = malloc(20);
    show_alloc_mem(); 

    ft_printf("\n=== REALLOC p1 -> 60 (still TINY) ===\n");
    p1 = realloc(p1, 60);
    show_alloc_mem();

    ft_printf("\n=== REALLOC p3 -> 200 (TINY -> SMALL) ===\n");
    p3 = realloc(p3, 200);
    show_alloc_mem();

    ft_printf("\n=== TEST SMALL MALLOC ===\n");
    void *s1 = malloc(200);
    void *s2 = malloc(500);
    void *s3 = malloc(1024);
    show_alloc_mem();

    ft_printf("\n=== FREE s1 and s3 ===\n");
    free(s1);
    free(s3);
    show_alloc_mem();

    ft_printf("\n=== REALLOC s2 -> 1500 (SMALL -> LARGE) ===\n");
    s2 = realloc(s2, 1500);
    show_alloc_mem();

    ft_printf("\n=== TEST LARGE MALLOC ===\n");
    void *l1 = malloc(2048);
    void *l2 = malloc(4096);
    show_alloc_mem();

    ft_printf("\n=== FREE l1 ===\n");
    free(l1);
    show_alloc_mem();

    ft_printf("\n=== REALLOC move test (must allocate elsewhere) ===\n");
    char *pA = malloc(10);
    void *pB = malloc(10);
    malloc(10);

    for (int i = 0; i < 10; i++)
        pA[i] = (char)(i + 1);

    free(pB);

    char *pA2 = realloc(pA, 1000);
    ft_printf("pA: %p -> %p\n", (void *)pA, (void *)pA2);

    int ok = 1;
    for (int i = 0; i < 10; i++) {
        if (pA2[i] != (char)(i + 1)) {
            ok = 0;
            break;
        }
    }
    ft_printf("realloc copy ok: %s\n", ok ? "yes" : "NO");

    free(pA2);

    ft_printf("\n=== FREE all ===\n");
    free(p1);
    free(p3);
    free(p4);
    free(s2);
    free(l2);
    show_alloc_mem();

    return 0;
}

// int main() {
//     void *p[105];

//     for (int i = 0; i < 105; i++)
//         p[i] = malloc(10);

//     show_alloc_mem();
//     for (int i = 10; i < 105; i++)
//         free(p[i]);

//     return 0;
// }