SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR) -I $(LIBFT_DIR)
LDFLAGS = -shared

SRC = malloc.c free.c realloc.c malloc_large.c zone.c block.c show_alloc_mem.c 
SRCS = $(addprefix $(SRC_DIR)/,$(SRC))
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

HOSTTYPE := $(HOSTTYPE)
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
TESTER = tester

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) main.c $(LIBFT)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	ln -sf $(NAME) libft_malloc.so
	$(CC) $(CFLAGS) main.c $(LIBFT) -L. -lft_malloc_$(HOSTTYPE) -o $(TESTER)
	$(CC) $(CFLAGS) main_bonus.c $(LIBFT) -L. -lft_malloc_$(HOSTTYPE) -o $(TESTER)_bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC -I $(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TESTER)
	rm -f $(TESTER)_bonus
	rm -f libft_malloc.so libft_malloc_*.so

re: fclean all

.PHONY: all clean fclean re