#include "../../cub3D.h"
#include <string.h>
static void	start_maze(t_utils *utils)
{
	start_player(utils);
	// utils->bg = mlx_new_image(utils->mlx, IMG_WIDTH, IMG_HEIGHT);
		// Pintar mitad y mitad para hacer el fondo de todo
	//mlx_put_pixel(utils->bg, utils->bg->height);
	// mlx_image_to_window(utils->mlx, utils->bg, 0, 0);
}

static void	render_image(void	*param)
{
	t_utils *utils;

	utils = (t_utils *)param;
	raycasting(utils);
}

void	play_game(t_utils *utils)
{
	utils->mlx = mlx_init(IMG_WIDTH, IMG_HEIGHT, "Cub3D", TRUE);
	start_maze(utils);
	render_image(utils);
	mlx_image_to_window(utils->mlx, utils->img, 0, 0);
	//mlx_loop_hook(utils->mlx, render_image, utils);
	mlx_loop(utils->mlx);
}