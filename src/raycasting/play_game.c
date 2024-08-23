#include "../../cub3D.h"
#include <string.h>

static void	load_textures(t_graphs *text, t_data *data)
{
	text->no_text = mlx_load_xpm42(data->north);
	text->ea_text = mlx_load_xpm42(data->east);
	text->so_text = mlx_load_xpm42(data->south);
	text->we_text = mlx_load_xpm42(data->west);
}

static void	start_maze(t_utils *utils)
{
	start_player(utils);
	load_textures(utils->text, utils->data);
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