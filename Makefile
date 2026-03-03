CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -shared

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

SRC = malloc.c free.c realloc.c
SRCS = $(addprefix $(SRC_DIR)/,$(SRC))
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

HOSTTYPE := $(HOSTTYPE)
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	ln -sf $(NAME) libft_malloc.so

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC -I $(INC_DIR) -I $(LIBFT_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f main
	rm -f libft_malloc.so libft_malloc_*.so
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

main: main.c src/show_alloc_mem.c $(NAME)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) main.c src/show_alloc_mem.c -L. -lft_malloc_$(HOSTTYPE) -o main

.PHONY: all clean fclean re