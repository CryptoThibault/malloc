CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -shared

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRC = malloc.c free.c realloc.c malloc_large.c utils.c show_alloc_mem.c 
SRCS = $(addprefix $(SRC_DIR)/,$(SRC))
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

HOSTTYPE := $(HOSTTYPE)
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
TESTER = tester

all: $(NAME)

$(NAME): $(OBJS) main.c
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
	ln -sf $(NAME) libft_malloc.so
	$(CC) $(CFLAGS) -I $(INC_DIR) main.c -L. -lft_malloc_$(HOSTTYPE) -o $(TESTER)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC -I $(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TESTER)
	rm -f libft_malloc.so libft_malloc_*.so

re: fclean all

.PHONY: all clean fclean re