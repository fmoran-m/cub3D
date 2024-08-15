#include "../../cub3D.h"

static void	get_player_direction(t_player *player, char dir)
{
	if (dir == 'W')
	{
		player->dirX = 0;
		player->dirY = -1;
	}
	else if (dir == 'E')
	{
		player->dirX = 0;
		player->dirY = 1;
	}
	else if (dir == 'N')
	{
		player->dirX = -1;
		player->dirY = 0;
	}
	else if (dir == 'S')
	{
		player->dirX = 1;
		player->dirY = 0;
	}
	player->planeX = player->dirY * -0.66;
	player->planeY = player->dirX * 0.66;
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
				utils->player->posX = (float)x + 0.5;
				utils->player->posY = (float)y + 0.5;
				get_player_direction(utils->player, utils->map->map[x][y]);
			}
			y++;
		}
		x++;
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
	player->posX = 0;
	player->posY = 0;
	player->dirX = 0;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0;
	player->fov_factor = 0.66;
	return (player);
}
