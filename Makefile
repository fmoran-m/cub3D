NAME = cub3D 

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

CC = cc

LM = make -C

CFLAGS = -fsanitize=address -Wall -Wextra -Werror

#MLXFLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -g

INCLUDES = cub3D.h

#MLX = ./mlx/libmlx.a

SRC = main.c control_argc.c init.c free.c parse.c parse_utils.c save_path.c save_color.c get_map.c create_map.c

OBJS = ${SRC:.c=.o}

$(NAME): $(OBJS) $(INCLUDES)
		$(LM) $(LIBFTDIR)
		$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
		$(RM) $(OBJS)
		cd $(LIBFTDIR) && make clean
	
fclean: clean
		$(RM) $(NAME)
		cd $(LIBFTDIR) && make fclean

re: fclean all

.PHONY: all clean fclean re
