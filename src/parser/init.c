/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:50:32 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/09/02 21:09:01 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ray->normalise = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->hit = NO_HIT;
	ray->side = 0;
	ray->line = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
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
	data->floor = 0x000000ff;
	data->ceiling = 0x000000ff;
	data->data_fill = 0;
	data->empty_lines = 0;
	data->dir_flag = 0;
}

t_graphs	*init_graphs(void)
{
	t_graphs	*graphs;

	graphs = malloc(sizeof(t_graphs));
	if (!graphs)
		return (print_error(MEM_ERROR), NULL);
	graphs->text[0].text = NULL;
	graphs->text[1].text = NULL;
	graphs->text[2].text = NULL;
	graphs->text[3].text = NULL;
	graphs->text_start = 0;
	graphs->text_x = 0;
	graphs->text_y = 0;
	graphs->step = 0;
	return (graphs);
}

void	init_utils(t_utils *utils)
{
	utils->mlx = NULL;
	utils->player = init_player();
	if (!utils->player)
	{
		free_structs(utils);
		exit(EXIT_FAILURE);
	}
	utils->ray = init_ray();
	if (!utils->ray)
	{
		free_structs(utils);
		exit(EXIT_FAILURE);
	}
	utils->text = init_graphs();
	if (!utils->text)
	{
		free_structs(utils);
		exit(EXIT_FAILURE);
	}
	init_data(utils->data);
	init_map(utils->map);
	return ;
}
