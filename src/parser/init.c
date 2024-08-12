#include "../../cub3D.h"

void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_size = 0;
	map->map_width = 0;
}

t_ray	*init_ray(void)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (print_error(MEM_ERROR), NULL);
	ray->cameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	ray->deltaDistX = 0;
	ray->deltaDistY = 0;
	ray->sideDistX = 0;
	ray->sideDistY = 0;
	ray->perpWallDist = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->hit = NO_HIT;
	ray->side = 0;
	ray->lineHeight = 0;
	ray->drawStart = 0;
	ray->drawEnd = 0;
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

t_line	*init_line(void)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
	{
		print_error(MEM_ERROR);
		return (NULL);
	}
	line->x = 0;
	line->y = 0;
	line->tex_x = 0;
	line->tex_y = 0;
	line->y0 = 0;
	line->y1 = 0;
	return (line);	
}

void	init_utils(t_utils *utils)
{
	utils->mlx = NULL;
	utils->player = init_player();
	utils->ray = init_ray();
	utils->line = init_line();
	init_data(utils->data);
	init_map(utils->map);
	if (!utils->player || !utils->ray)
	{
		free_structs(utils);
		exit(EXIT_FAILURE);
	}
}
