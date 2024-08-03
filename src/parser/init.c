#include "../../cub3D.h"

void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_size = 0;
	map->map_width = 0;
}

t_player	*init_player()
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
	{
		print_error(MEM_ERROR);
		return (NULL);
	}
	player->posX = 0;
	player->posY = 0;
	player->dirX = 0;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0;
	player->fov_factor = 0.66;
	return (player);
}

t_ray	*init_ray()
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
	{
		print_error(MEM_ERROR);
		return (NULL);
	}
	ray->cameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	return (ray);
}

void	init_data(t_data *data)
{
	data->north = NULL;
	data->south = NULL;
	data->east = NULL;
	data->west = NULL;
	data->f_flag = 0;
	data->c_flag = 0;
	data->floor = 0;
	data->ceiling = 0;
	data->data_fill = 0;
	data->empty_lines = 0;
}

void	init_utils(t_utils *utils)
{
	utils->mlx = NULL;
	utils->player = init_player();
	utils->ray = init_ray();
	init_data(utils->data);
	init_map(utils->map);
	if (!utils->player || !utils->ray)
	{
		free_structs(utils);
		exit(EXIT_FAILURE);
	}
}
