NAME = cub3D 

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft

LIBMLX = ./mlx
MLX_LIB = $(LIBMLX)/build/libmlx42.a
MLX = $(MLX_LIB) -ldl -lglfw -pthread -lm

CC = cc
LM = make -C
CFLAGS = -fsanitize=address -Wall -Wextra #-Werror


INCLUDES = cub3D.h mlx/include/MLX42/MLX42.h

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
	src/parser/validate_utils.c \
	src/raycasting/start_maze.c \
	src/raycasting/print_errors.c

OBJS = ${SRC:.c=.o}

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(CFLAGS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB): 
	cmake $(LIBMLX) -B $(LIBMLX)/build
	$(LM) $(LIBMLX)/build -j4

$(LIBFT):
	$(LM) $(LIBFTDIR)

all: $(NAME)

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
