#ifndef CUB3D_H
# define CUB3D_H

# define ARGC_ERR "Error: this program requires only 1 argument"
# define EXT_ERR  "Error: Invalid file extension"
# define FILE_NOT_FOUND "Error: File not found"
# define INC_FORMAT "Error, incorrect format"
# define MLX_ERROR_MSG "Error: MLX not correctly initialised"

# define EXIT_ERR	1
# define FUNC_FAIL	0
# define FUNC_SUCC	1

# define PARAMS		0
# define NORTH		1
# define SOUTH		2	
# define EAST		3	
# define WEST		4	
# define FLOOR_1	5
# define FLOOR_2	6
# define FLOOR_3	7	
# define CEL_1		8
# define CEL_2		9
# define CEL_3		10
# define F_COMMA_1	11
# define F_COMMA_2	12
# define C_COMMA_1	13
# define C_COMMA_2	14

# define IMG_WIDTH	1920
# define IMG_HEIGHT	1080

# define TRUE 1
# define FALSE 0

# define MLX_ERROR 1

# include <math.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx/include/MLX42/MLX42.h"

typedef struct s_map
{
	char	**map;
	int		map_size;
	int		map_width;
}	t_map;

typedef struct s_data
{
	char				*north;
	char				*south;
	char				*east;
	char				*west;
	unsigned int		floor;
	unsigned int		ceiling; // Hasta aquí para usar en las operaciones matemáticas
	size_t				empty_lines;
	int					c_flag; //Ceiling relleno
	int					f_flag; //Flag relleno
	int					data_fill; //Todos los datos se han completado
}	t_data;

typedef	struct s_player
{
	int					pl_X;
	int					pl_Y;
}	t_player;

typedef struct s_utils
{
	t_data		*data;
	t_map		*map;
//	t_player	*player;
	mlx_t		*mlx;
}	t_utils;

void	init_data(t_data *data);
void	init_utils(t_utils *utils);
void	free_structs(t_utils *utils);
void	file_checker(char *argv);
int		parse_file(t_utils *utils, char *file);
int		save_path(t_data *data, char *line, int *status);
int		check_params(t_data *data);
int		avoid_spaces(char c);
int		save_color(t_data *data, char *line, int *status);
int		get_map(t_utils *utils, int fd);
int		create_map(t_utils *utils, char *doc);
void	init_map(t_map *map);
int		null_avoid_spaces(char c);
int		is_map_dir(char c);
int		check_middle_square(t_map *map, int y, int x);
int		check_space(t_map *map, int y, int x);
int		ft_isnum(char c);
int		is_correct_char(char c);
int		is_map_char(char c);

// graphics
int		start_window(t_utils *utils);
int		print_error(int	type);

#endif
