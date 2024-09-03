/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:45:11 by nvillalt          #+#    #+#             */
/*   Updated: 2024/09/03 15:29:50 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ARGC_ERR "Error: This program requires only 1 argument"
# define EXT_ERR  "Error: Invalid file extension"
# define FILE_NOT_FOUND "Error: File not found"
# define INC_FORMAT "Error: Incorrect data format"
# define INC_FORMAT_MAP "Error: Incorrect map format"
# define INC_FORMAT_PLY "Error: Multiple player position declarations"
# define MLX_ERROR_MSG "Error: Incorrect mlx initialisation"
# define MLX_DFL_MSG "Error: Incorrect mlx syscall"
# define MEM_ERROR_MSG "Error: Incorrect memory allocation"
# define MLX_IMG_ERROR "Error: Could not initialise image"
# define XPM_ERR "Error: Incorrect image extension"
# define PATH_ERR "Error: Texture path does not exist"
# define OPEN_ERR "Error: Cannot open argument file"
# define DIR_ERR "Error: No player"

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

# define IMG_WIDTH  1920
# define IMG_HEIGHT	1080

# define TRUE 1
# define FALSE 0

# define VERTICAL_AXIS 0
# define HORIZONAL_AXIS 1

# define HIT 1
# define NO_HIT 0

# define MLX_ERROR 1
# define MEM_ERROR 2
# define IMG_ERROR 3

# define FOV 0.66

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
	unsigned int		ceiling;
	size_t				empty_lines;
	int					c_flag;
	int					f_flag;
	int					dir_flag;
	int					data_fill;
}	t_data;

typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				fov_factor;
	char				direction;
}	t_player;

typedef struct s_ray
{
	int					step_x;
	int					step_y;
	double				side_dist_x;
	double				side_dist_y;
	double				normalise;
	double				ray_dir_x;
	double				ray_dir_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				wall_dist;
	double				wall_x;
	int					map_x;
	int					map_y;
	int					hit;
	int					side;
	int					line;
	int					draw_start;
	int					draw_end;
}	t_ray;

typedef struct s_img
{
	xpm_t		*text;
	mlx_image_t	*display;
	char		*addr;
}	t_img;

typedef struct s_graphs
{
	t_img	text[4];
	double	text_start;
	double	text_x;
	double	text_y;
	double	step;
}	t_graphs;

typedef struct s_texture
{
	int		text_x;
	int		text_y;
	double	text_pos;
	double	step;
}	t_texture;

typedef struct s_move
{
	double		speed;
	double		theta;
	double		old_dir_x;
	double		old_dir_y;
	double		old_plane_x;
	double		old_plane_y;
	double		new_pos_x;
	double		new_pos_y;
}	t_move;

typedef struct s_utils
{
	t_data		*data;
	t_map		*map;
	t_player	*player;
	t_ray		*ray;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_graphs	*text;
}	t_utils;

// parse functions
void		init_data(t_data *data);
void		init_utils(t_utils *utils);
void		free_structs(t_utils *utils);
int			file_checker(char *argv, char *ext);
int			parse_file(t_utils *utils, char *file);
int			save_path(t_data *data, char *line, int *status);
int			check_params(t_data *data);
int			avoid_spaces(char c);
int			save_color(t_data *data, char *line, int *status);
int			get_map(t_utils *utils, int fd);
int			create_map(t_utils *utils, char *doc);
void		init_map(t_map *map);
int			null_avoid_spaces(char c);
int			is_map_dir(char c);
int			check_middle_square(t_map *map, int y, int x);
int			check_space(t_map *map, int y, int x);
int			ft_isnum(char c);
int			is_correct_char(char c);
int			is_map_char(char c);
int			is_dir_char(char c);
int			xpm_checker(t_data *data);

// handle_error
int			print_error(int type);

// play_game.c
void		raycasting(t_utils *utils);
int			play_game(t_utils *utils);

// line_and_wall.c
void		draw_line(t_utils *utils, int x);
void		get_line_height(t_ray *ray, t_player *player);

// movements.c
void		inputs(t_utils *utils);

// movements_hit.c
int			check_hit_y(t_player *player, t_map *map, double new_pos_y);
int			check_hit_x(t_player *player, t_map *map, double new_pos_x);

// texture_calculations.c
double		get_ray_impact(t_ray *ray, t_player *player);
double		get_text_pos(t_ray *ray, double step);
double		get_step(t_ray *ray, t_img text);
int			get_text_color(int text_x, int text_y, t_img texture);
int			get_text_x(t_ray *ray, t_img text, double square_impact);

// player_initialisation
int			start_player(t_utils *utils);
t_player	*init_player(void);

#endif
