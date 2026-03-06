# Malloc
A custom implementation of the standard C memory allocator.
This project recreates the behavior of malloc, free, and realloc while managing memory manually using mmap.
The allocator organizes memory into different zones to optimize allocations depending on their size and provides tools to visualize allocated memory blocks.

## Features
- **Custom memory allocator**
  - Reimplementation of `malloc`, `free`, and `realloc`.

- **Zone-based memory management**
  - **TINY zone** for very small allocations.
  - **SMALL zone** for medium allocations.
  - **LARGE allocations** handled individually with `mmap`.

- **Efficient block management**
  - Linked list of memory blocks.
  - Reuse of freed blocks when possible.
  - Block splitting to reduce fragmentation.

- **Dynamic zone creation**
  - New zones are created automatically when existing ones are full.

- **Page-aligned allocations**
  - Memory is aligned to system page size using `sysconf(_SC_PAGESIZE)`.

- **Large allocation handling**
  - Each large allocation is mapped independently.
  - Freed large blocks are immediately released with `munmap`.

- **Memory visualization**
  - `show_alloc_mem()` prints all allocated blocks and total allocated memory.

## Build
```sh
make
make main
```

## Run
```sh
LD_LIBRARY_PATH=. LD_PRELOAD=./libft_malloc.so ./main
```