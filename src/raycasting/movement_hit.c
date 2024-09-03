/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:27:06 by nvillalt          #+#    #+#             */
/*   Updated: 2024/09/03 15:37:46 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	check_hit_x(t_player *player, t_map *map, double new_pos_x)
{
	int	pos_y;
	int	max_pos_x;
	int	min_pos_x;

	max_pos_x = floor((new_pos_x) + OFFSET);
	min_pos_x = floor((new_pos_x) - OFFSET);
	pos_y = floor(player->pos_y);
	if (map->map[pos_y][max_pos_x] == '1' || map->map[pos_y][min_pos_x] == '1')
		return (0);
	return (1);
}

int	check_hit_y(t_player *player, t_map *map, double new_pos_y)
{
	int	max_pos_y;
	int	min_pos_y;
	int	pos_x;

	pos_x = floor((player->pos_x));
	max_pos_y = floor((new_pos_y) + OFFSET);
	min_pos_y = floor((new_pos_y) - OFFSET);
	if (map->map[max_pos_y][pos_x] == '1' || map->map[min_pos_y][pos_x] == '1')
		return (0);
	return (1);
}
