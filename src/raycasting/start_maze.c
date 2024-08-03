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
