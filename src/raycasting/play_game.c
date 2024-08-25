#include "../../cub3D.h"
#include <string.h>

	// Se coge el xpm y se pasa a imagen para poder usar la textura en una imagen displayeable
	// Ref.: https://github.com/codam-coding-college/MLX42/blob/master/docs/XPM42.md
static int	load_textures(t_graphs *text, t_data *data, t_utils *utils)
{
	int	i;

	i = -1;
	text->text[0].text = mlx_load_xpm42(data->north);
	text->text[1].text = mlx_load_xpm42(data->east);
	text->text[2].text= mlx_load_xpm42(data->south);
	text->text[3].text = mlx_load_xpm42(data->west);
	while (++i < 4)
	{
		if (!text->text[i].text)
			return (free_structs(utils), EXIT_FAILURE);
	}
	text->text[0].display = mlx_texture_to_image(utils->mlx, &text->text[0].text->texture);
	text->text[1].display = mlx_texture_to_image(utils->mlx, &text->text[1].text->texture);
	text->text[2].display = mlx_texture_to_image(utils->mlx, &text->text[2].text->texture);
	text->text[3].display = mlx_texture_to_image(utils->mlx, &text->text[0].text->texture);
	i = -1;
		while (++i < 4)
	{
		if (!text->text[i].display)
			return (free_structs(utils), EXIT_FAILURE);
	}
	return (FUNC_SUCC);
}

static void	start_maze(t_utils *utils)
{
	start_player(utils);
	load_textures(utils->text, utils->data, utils);
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