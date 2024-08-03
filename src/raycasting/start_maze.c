#include "../../cub3D.h"

static void	get_raycasting(t_utils *utils)
{
	double	i;
	double	w;

	i = 0;
	w = utils->map->map_width;
	while (i < w)
	{
		utils->ray->cameraX = 2 * i / w - 1;
		utils->ray->rayDirX = utils->player->dirX + utils->player->planeX
			* utils->ray->cameraX;
		utils->ray->rayDirY = utils->player->dirY + utils->player->planeY
			* utils->ray->cameraX;
		i++;
	}
}

static void	paint_screen(t_utils *utils)
{
	while (TRUE)
	{
		get_raycasting(utils);
	}
}

int	start_window(t_utils *utils)
{
	//mlx_set_setting(MLX_MAXIMIZED, TRUE); // Opción para que empiece todo maximized de primeras
	utils->mlx = mlx_init(IMG_WIDTH, IMG_HEIGHT, "Cub3D", TRUE);
	if (!utils->mlx)
		return (print_error(MLX_ERROR));
	paint_screen(utils);
	mlx_loop(utils->mlx);
	//mlx_terminate(utils->mlx);
	return (FUNC_SUCC);
}
