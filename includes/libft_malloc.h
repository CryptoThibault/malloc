#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

#include <unistd.h>
#include <stddef.h>
#include <sys/mman.h>
#include <pthread.h>
#include "libft.h"

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
} __attribute__((aligned(16))) t_block;

typedef struct s_zone {
    size_t size;
    size_t block_count;
    t_block *blocks;
    struct s_zone *next;
} t_zone;

typedef struct s_malloc_data {
    t_zone *tiny;
    t_zone *small;
    t_block *large;
} t_malloc_data;

extern t_malloc_data g_malloc;
extern pthread_mutex_t g_malloc_mutex;

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

void *_malloc(size_t size);
void _free(void *ptr);
void *_realloc(void *ptr, size_t size);
void *malloc_large(size_t size);
int get_zone_type(size_t size);
t_zone *create_zone(size_t size, size_t n);
t_block *create_block(t_zone *z, size_t size, size_t block_size);
void show_alloc_mem();
void show_alloc_mem_ex();

#endif