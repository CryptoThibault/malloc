# Malloc
A custom C memory allocator library that implements malloc, free, and realloc while tracking and visualizing memory usage.

## BUILD
```sh
make
make main
```

## RUN
```sh
LD_LIBRARY_PATH=. LD_PRELOAD=./libft_malloc.so ./main
```