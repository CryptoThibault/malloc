#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/mman.h>

# define TINY 1
# define SMALL 2
# define LARGE 3
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

typedef struct s_malloc_data {
    t_zone *tiny;
    t_zone *small;
    t_block *large;
} t_malloc_data;

extern t_malloc_data g_malloc;

void free(void *ptr);
void *malloc(size_t size);
void *malloc_large(size_t size);
void *realloc(void *ptr, size_t size);
void *ft_memcpy(void *dst, const void *src, size_t n);
int get_zone_type(size_t size);
t_zone *zoneset(size_t size, size_t n);
void show_alloc_mem();

#endif