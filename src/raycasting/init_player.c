#include "../../cub3D.h"

// Ojo con esta función en caso de que la mlx esté graciosa y sea moviendose en Y vs X
static void	get_player_direction(t_player *player, char dir)
{
	if (dir == 'W')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'E')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (dir == 'N')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (dir == 'S')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	player->plane_x = player->dir_y * -0.66;
	player->plane_y = player->dir_x * 0.66;
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
				utils->player->pos_x = (float)x + 0.5;
				utils->player->pos_y = (float)y + 0.5;
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
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->fov_factor = 0.66;
	return (player);
}
