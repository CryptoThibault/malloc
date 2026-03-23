#include "libft_malloc.h"

int thread_finished[4] = {0};

void *thread_func(void *arg) {
    int id = *(int *)arg;
    void *ptrs[10];

    for (int i = 0; i < 10; i++) {
        ptrs[i] = malloc(50 + id * 10);
        if (!ptrs[i]) {
            return NULL;
        }
    }

    ptrs[0] = realloc(ptrs[0], 100 + id * 20);

    for (int i = 5; i < 10; i++) {
        free(ptrs[i]);
    }

    thread_finished[id - 1] = 1;
    return NULL;
}

int main(void) {
    ft_printf("=== EXTENDED MEMORY DUMP ===\n");
    void *test_ptr = malloc(50);
    if (test_ptr)
        ft_strlcpy(test_ptr, "Hello, malloc test data!", 50);
    show_alloc_mem_ex();
    free(test_ptr);

    ft_printf("\n=== COALESCENCE TEST ===\n");
    void *c1 = malloc(100);
    void *c2 = malloc(100);
    void *c3 = malloc(100);
    show_alloc_mem();

    free(c1);
    free(c2);
    ft_printf("\nFreed c1 and c2 (coalesced)\n");

    void *c4 = malloc(120);
    void *c5 = malloc(80);
    show_alloc_mem();

    ft_printf("\nFree all:\n");
    free(c3);
    free(c4);
    free(c5);
    show_alloc_mem();

    ft_printf("\n=== MULTI-THREAD TEST ===\n");

    pthread_t threads[4];
    int ids[4] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, &ids[i]) != 0) {
            ft_printf("Error creating thread %d\n", i);
        }
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < 4; i++) {
        if (thread_finished[i]) {
            ft_printf("Thread %d finished\n", i + 1);
        }
    }

    ft_printf("All threads finished\n");
    show_alloc_mem();

    return 0;
}