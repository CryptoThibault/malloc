#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

#include "../libft/libft.h"
#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_block {
    size_t size;
    int free;
    struct s_block *next;
} t_block;

extern t_block *head;

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();

#endif