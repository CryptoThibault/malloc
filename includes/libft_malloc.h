#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

#include "../libft/libft.h"
#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

# define TINY_MAX 128
# define SMALL_MAX 1024
# define BLOCKS_PER_ZONE 100

typedef struct s_block {
    size_t size;
    int free;
    struct s_block *next;
} t_block;

typedef struct s_zone {
    size_t size;
    t_block *blocks;
    struct s_zone *next;
} t_zone;

extern t_zone *tiny;
extern t_zone *small;
extern t_block *large;

void free(void *ptr);
void *malloc(size_t size);
void *malloc_large(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();
t_zone *zoneset(size_t size, size_t n);

#endif