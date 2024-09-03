/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_calculations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:28:40 by nvillalt          #+#    #+#             */
/*   Updated: 2024/09/03 14:57:19 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

double	get_text_pos(t_ray *ray, double step)
{
	double	text_pos;

	text_pos = (ray->draw_start - IMG_HEIGHT / 2 + ray->line / 2)
		* step;
	return (text_pos);
}

int	get_text_color(int text_x, int text_y, t_img texture)
{
	uint32_t	color;
	uint32_t	i;

	color = 0;
	i = (texture.display->width * text_y + text_x) * 4;
	color |= texture.display->pixels[i] << 24;
	color |= texture.display->pixels[i + 1] << 16;
	color |= texture.display->pixels[i + 2] << 8;
	color |= texture.display->pixels[i + 3];
	return (color);
}

double	get_ray_impact(t_ray *ray, t_player *player)
{
	double	square_impact;

	if (ray->side == VERTICAL_AXIS)
		square_impact = player->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		square_impact = player->pos_x + ray->wall_dist * ray->ray_dir_x;
	return (square_impact);
}

int	get_text_x(t_ray *ray, t_img text, double square_impact)
{
	int	text_x;

	text_x = (int)(square_impact * text.display->width);
	if (ray->side == VERTICAL_AXIS && ray->ray_dir_x < 0)
		text_x = text.display->width - text_x - 1;
	if (ray->side == HORIZONAL_AXIS && ray->ray_dir_y > 0)
		text_x = text.display->width - text_x - 1;
	return (text_x);
}

double	get_step(t_ray *ray, t_img text)
{
	double	step;

	step = 1.0 * text.display->height / ray->line;
	return (step);
}
