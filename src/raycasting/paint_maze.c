#include "../../cub3D.h"

int	start_window(t_utils *utils)
{
	//mlx_set_setting(MLX_MAXIMIZED, TRUE); // Opción para que empiece todo maximized de primeras
	utils->mlx = mlx_init(IMG_WIDTH, IMG_HEIGHT, "Cub3D", TRUE);
	utils->img = mlx_new_image(utils->mlx, IMG_WIDTH, IMG_HEIGHT);
	if (!utils->mlx)
		return (print_error(MLX_ERROR));
	raycasting(utils);
	//mlx_loop_hook(utils->mlx, raycasting, utils);
	mlx_loop(utils->mlx);
	mlx_terminate(utils->mlx);
	return (FUNC_SUCC);
}
