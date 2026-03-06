#include "libft_malloc.h"

int main(void) {
    printf("=== TEST TINY MALLOC ===\n");
    void *p1 = malloc(10);
    void *p2 = malloc(50);
    void *p3 = malloc(100);
    show_alloc_mem();

    printf("\n=== FREE p2 ===\n");
    free(p2);
    show_alloc_mem();

    printf("\n=== ADDITIONAL TINY MALLOC ===\n");
    void *p4 = malloc(20);
    show_alloc_mem(); 

    printf("\n=== REALLOC p1 -> 60 (still TINY) ===\n");
    p1 = realloc(p1, 60);
    show_alloc_mem();

    printf("\n=== REALLOC p3 -> 200 (TINY -> SMALL) ===\n");
    p3 = realloc(p3, 200);
    show_alloc_mem();

    printf("\n=== TEST SMALL MALLOC ===\n");
    void *s1 = malloc(200);
    void *s2 = malloc(500);
    void *s3 = malloc(1024);
    show_alloc_mem();

    printf("\n=== FREE s1 and s3 ===\n");
    free(s1);
    free(s3);
    show_alloc_mem();

    printf("\n=== REALLOC s2 -> 1500 (SMALL -> LARGE) ===\n");
    s2 = realloc(s2, 1500);
    show_alloc_mem();

    printf("\n=== TEST LARGE MALLOC ===\n");
    void *l1 = malloc(2048);
    void *l2 = malloc(4096);
    show_alloc_mem();

    printf("\n=== FREE l1 ===\n");
    free(l1);
    show_alloc_mem();

    printf("\n=== FREE all ===\n");
    free(p1);
    free(p3);
    free(p4);
    free(s2);
    free(l2);
    show_alloc_mem();

    return 0;
}