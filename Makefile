NAME = cub3D 

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft

LIBMLX = ./MLX42
MLX = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

CC = cc
LM = make -C
CFLAGS = -fsanitize=address -Wall -Wextra -Werror


INCLUDES = cub3D.h $(LIBMLX)/include

SRC = main.c control_argc.c init.c free.c parse.c parse_utils.c save_path.c save_color.c get_map.c create_map.c validate_utils.c
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
