/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:35:46 by nvillalt          #+#    #+#             */
/*   Updated: 2024/09/03 15:28:13 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	get_player_direction(t_player *player, char dir)
{
	if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	player->plane_x = player->dir_y * FOV;
	if (dir == 'N' || dir == 'S')
		player->plane_x *= -1;
	player->plane_y = player->dir_x * FOV;
	return ;
}

int	start_player(t_utils *utils)
{
	int	x;
	int	y;

	y = 0;
	while (utils->map->map[y])
	{
		x = 0;
		while (utils->map->map[y][x])
		{
			if (utils->map->map[y][x] == 'N' || utils->map->map[y][x] == 'E'
				|| utils->map->map[y][x] == 'S' || utils->map->map[y][x] == 'W')
			{
				utils->player->direction = utils->map->map[y][x];
				utils->player->pos_x = (float)x + 0.5;
				utils->player->pos_y = (float)y + 0.5;
				get_player_direction(utils->player, utils->map->map[y][x]);
			}
			x++;
		}
		y++;
	}
	return (FUNC_SUCC);
}

t_player	*init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
	{
		print_error(MEM_ERROR);
		return (NULL);
	}
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->fov_factor = 0.66;
	return (player);
}
