#include "../../cub3D.h"

static void	set_initial_plane(t_player *player, char dir)
{
	if (dir == 'W' || dir == 'E')
	{
		player->planeX = 0.66;
		player->planeY = 0;
	}
	else if (dir == 'N' || dir == 'S')
	{
		player->planeX = 0;
		player->planeY = 0.66;
	}
	return ;
}

static void	get_player_direction(t_player *player, char dir)
{
	if (dir == 'W')
	{
		player->dirX = 0;
		player->dirY = -1;
		set_initial_plane(player, dir);
	}
	else if (dir == 'E')
	{
		player->dirX = 0;
		player->dirY = 1;
		set_initial_plane(player, dir);
	}
	else if (dir == 'N')
	{
		player->dirX = -1;
		player->dirY = 0;
		set_initial_plane(player, dir);
	}
	else if (dir == 'S')
	{
		player->dirX = 1;
		player->dirY = 0;
		set_initial_plane(player, dir);
	}
	return ;
}

int	start_player(t_utils *utils)
{
	int	x;
	int	y;

	x = 0;
	while (x < utils->map->map_size)
	{
		y = 0;
		while (y < utils->map->map_width)
		{
			if (utils->map->map[x][y] == 'N' || utils->map->map[x][y] == 'E'
				|| utils->map->map[x][y] == 'S' || utils->map->map[x][y] == 'W')
			{
				utils->player->posX = x;
				utils->player->posY = y;
				get_player_direction(utils->player, utils->map->map[x][y]);
			}
			y++;
		}
		x++;
	}
	return (FUNC_SUCC);
}