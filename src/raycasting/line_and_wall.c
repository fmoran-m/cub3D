/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:30:36 by nvillalt          #+#    #+#             */
/*   Updated: 2024/09/02 21:10:06 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static t_img	select_texture(t_ray *ray, t_img *text)
{
	if (ray->side == HORIZONAL_AXIS && ray->ray_dir_y <= 0)
		return (text[0]);
	if (ray->side == VERTICAL_AXIS && ray->ray_dir_x >= 0)
		return (text[1]);
	if (ray->side == VERTICAL_AXIS && ray->ray_dir_x < 0)
		return (text[2]);
	return (text[3]);
}

static void	draw_wall(t_utils *utils, int *y, int x)
{
	double		square_impact;
	t_texture	info;
	uint32_t	color;
	t_img		texture;

	square_impact = get_ray_impact(utils->ray, utils->player);
	square_impact -= floor(square_impact);
	texture = select_texture(utils->ray, utils->text->text);
	info.text_x = get_text_x(utils->ray, texture, square_impact);
	info.step = get_step(utils->ray, texture);
	info.text_pos = get_text_pos(utils->ray, info.step);
	while (*y < utils->ray->draw_end)
	{
		info.text_y = (int)info.text_pos
			& (texture.display->height - 1);
		info.text_pos += info.step;
		color = get_text_color(info.text_x, info.text_y, texture);
		mlx_put_pixel(utils->img, x, *y, color);
		*y = *y + 1;
	}
	return ;
}

void	draw_line(t_utils *utils, int x)
{
	int	y;

	y = 0;
	while (y < utils->ray->draw_start)
	{
		mlx_put_pixel(utils->img, x, y, utils->data->ceiling);
		y++;
	}
	y = utils->ray->draw_start;
	draw_wall(utils, &y, x);
	while (y < IMG_HEIGHT)
	{
		mlx_put_pixel(utils->img, x, y, utils->data->floor);
		y++;
	}
	return ;
}

void	get_line_height(t_ray *ray, t_player *player)
{
	if (ray->side == VERTICAL_AXIS)
	{
		ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
		ray->wall_x = player->pos_y + ray->wall_dist * ray->ray_dir_y;
	}
	else if (ray->side == HORIZONAL_AXIS)
	{
		ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
		ray->wall_x = player->pos_x + ray->wall_dist * ray->ray_dir_x;
	}
	ray->line = (int)(IMG_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line / 2 + IMG_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line / 2 + IMG_HEIGHT / 2;
	if (ray->draw_end >= IMG_HEIGHT)
		ray->draw_end = IMG_HEIGHT - 1;
}
