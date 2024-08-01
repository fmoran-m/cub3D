NAME = cub3D 

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft

LIBMLX = ./MLX42
MLX = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

CC = cc
LM = make -C
CFLAGS = -fsanitize=address -Wall -Wextra -Werror


INCLUDES = cub3D.h $(LIBMLX)/include

SRC = src/main.c \
	src/free.c \
	src/parser/control_argc.c \
	src/parser/init.c \
	src/parser/parse.c \
	src/parser/parse_utils.c \
	src/parser/save_path.c \
	src/parser/save_color.c \
	src/parser/get_map.c \
	src/parser/create_map.c \
	src/parser/validate_utils.c

OBJS = ${SRC:.c=.o}

$(NAME): libmlx $(OBJS) $(INCLUDES)
		$(LM) $(LIBFTDIR)
		$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

clean:
		$(RM) $(OBJS)
		cd $(LIBFTDIR) && make clean
		@rm -rf $(LIBMLX)/build
	
fclean: clean
		$(RM) $(NAME)
		cd $(LIBFTDIR) && make fclean
		@rm -rf $(LIBMLX)/build

re: fclean all

.PHONY: all clean fclean re
