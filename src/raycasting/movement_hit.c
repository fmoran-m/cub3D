/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:27:06 by nvillalt          #+#    #+#             */
/*   Updated: 2024/08/29 17:27:16 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	check_hit_x(t_player *player, t_map *map, double new_pos_x)
{
	int	pos_y;
	int	pos_x;

	pos_y = floor(player->pos_y);
	pos_x = floor(new_pos_x);
	if (map->map[pos_y][pos_x] == '1')
		return (0);
	return (1);
}

static int	check_hit_y(t_player *player, t_map *map, double new_pos_y)
{
	int	pos_y;
	int	pos_x;

	pos_x = (player->pos_x);
	pos_y = (new_pos_y);
	if (map->map[pos_y][pos_x] == '1')
		return (0);
	return (1);
}