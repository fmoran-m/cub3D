#ifndef CUB3D_H
# define CUB3D_H

# define ARGC_ERR "Error: this program requires only 1 argument"
# define EXT_ERR  "Error: Invalid file extension"
# define FILE_NOT_FOUND "Error: File not found"

# define EXIT_ERR 1

# define PARAMS	0
# define NORTH	1
# define SOUTH	2	
# define EAST	3	
# define WEST	4	
# define FLOOR	5
# define CEL	6

# include <math.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_data
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		floor;
	int		ceiling;
	int		c_flag;
	int		f_flag;
}	t_data;

typedef struct s_utils
{
	t_data		*data;
//	t_map		*map;
//	t_player	*player;
//	t_mlx		*mlx;
}	t_utils;

void	init_data(t_data *data);
void	init_utils(t_utils *utils);
void	free_structs(t_utils *utils);
void	file_checker(char *argv);
int		parse_file(t_utils *utils, char *file);
int		save_path(t_data *data, char *line, int *status);
int	check_params(t_data *data);
int	avoid_spaces(char c);
#endif
