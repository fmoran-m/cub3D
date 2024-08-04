#include "../../cub3D.h"

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
