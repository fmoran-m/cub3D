/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:52:22 by nvillalt          #+#    #+#             */
/*   Updated: 2024/09/03 14:49:15 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	dda_algorithm(t_ray *ray, t_map *map)
{
	ray->hit = NO_HIT;
	while (ray->hit == NO_HIT)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = VERTICAL_AXIS;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = HORIZONAL_AXIS;
		}
		if (map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = HIT;
	}
}

static void	steps_initialisation(t_ray *ray, t_player *player)
{
	ray->map_x = floor((int)player->pos_x);
	ray->map_y = floor((int)player->pos_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

static void	set_delta_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_calculations(t_ray *ray, t_player *player, int x)
{
	ray->normalise = 2 * x / (double)IMG_WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->normalise;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->normalise;
}

void	raycasting(t_utils *utils)
{
	int	x;

	x = 0;
	utils->img = mlx_new_image(utils->mlx, IMG_WIDTH, IMG_HEIGHT);
	if (!utils->img)
	{
		ft_putendl_fd(MLX_DFL_MSG, STDERR_FILENO);
		free_structs(utils);
		exit(1);
	}
	while (x < IMG_WIDTH)
	{
		init_calculations(utils->ray, utils->player, x);
		set_delta_dist(utils->ray);
		steps_initialisation(utils->ray, utils->player);
		dda_algorithm(utils->ray, utils->map);
		get_line_height(utils->ray, utils->player);
		draw_line(utils, x);
        printf("X: %f, Y: %f\n", utils->ray->ray_dir_x, utils->ray->ray_dir_y); //!!!!!
		x++;
	}
}
