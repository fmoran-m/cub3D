#include "../../cub3D.h"

void	start_raycasting(t_utils *utils)
{
	
}

int	start_window(t_utils *utils)
{
	//mlx_set_setting(MLX_MAXIMIZED, TRUE); // Opción para que empiece todo maximized de primeras
	utils->mlx = mlx_init(IMG_WIDTH, IMG_HEIGHT, "Cub3D", TRUE);
	if (!utils->mlx)
		return (print_error(MLX_ERROR));
	//start_raycasting(utils);
	mlx_loop(utils->mlx);
	//mlx_terminate(utils->mlx);
	return (FUNC_SUCC);
}

static void	get_player_direction(t_player *player, int x, int y, char dir)
{
	player->posX = x;
	player->posY = y;
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
	else
	{
		player->dirX = 1;
		player->dirY = 0;
	}
	return ;
}

int	start_player(t_utils *utils)
{
	int	map_width;
	int	map_size; // El x, a lo alto
	int	x;
	int	y;

	x = 0;
	map_width = utils->map->map_width;
	map_size = utils->map->map_size;
	while (x < map_size)
	{
		y = 0;
		while (y < map_width)
		{
			if (utils->map->map[x][y] == 'N' || utils->map->map[x][y] == 'E'
				|| utils->map->map[x][y] == 'S' || utils->map->map[x][y] == 'W')
				get_player_direction(utils->player, x, y, utils->map->map[x][y]);
			y++;
		}
		x++;
	}
	return (FUNC_SUCC);
}
