/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:45:48 by nvillalt          #+#    #+#             */
/*   Updated: 2024/09/02 16:44:18 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	load_textures(t_graphs *text, t_utils *utils)
{
	int	i;

	i = -1;
	text->text[0].display = mlx_texture_to_image(utils->mlx,
			&text->text[0].text->texture);
	text->text[1].display = mlx_texture_to_image(utils->mlx,
			&text->text[1].text->texture);
	text->text[2].display = mlx_texture_to_image(utils->mlx,
			&text->text[2].text->texture);
	text->text[3].display = mlx_texture_to_image(utils->mlx,
			&text->text[3].text->texture);
	while (++i < 4)
	{
		if (!text->text[i].display)
			return (free_structs(utils), EXIT_FAILURE);
	}
	return (FUNC_SUCC);
}

static int	start_maze(t_utils *utils)
{
	int	i;

	i = -1;
	start_player(utils);
	utils->text->text[0].text = mlx_load_xpm42(utils->data->north);
	utils->text->text[1].text = mlx_load_xpm42(utils->data->east);
	utils->text->text[2].text = mlx_load_xpm42(utils->data->south);
	utils->text->text[3].text = mlx_load_xpm42(utils->data->west);
	while (++i < 4)
	{
		if (!utils->text->text[i].text)
			return (free_structs(utils), EXIT_FAILURE);
	}
	load_textures(utils->text, utils);
	return (FUNC_SUCC);
}

static void	render_image(void *param)
{
	t_utils	*utils;

	utils = (t_utils *)param;
	mlx_delete_image(utils->mlx, utils->img);
	raycasting(utils);
	if (mlx_image_to_window(utils->mlx, utils->img, 0, 0) == -1)
    {
        ft_putendl_fd(MLX_DFL_MSG, STDERR_FILENO);
        free_structs(utils);
        exit (1);
    }
	inputs(utils);
	return ;
}

int	play_game(t_utils *utils)
{
	utils->mlx = mlx_init(IMG_WIDTH, IMG_HEIGHT, "Cub3D", TRUE);
	if (!utils->mlx)
		return (ft_putendl_fd(MLX_ERROR_MSG, STDERR_FILENO), 0);
	start_maze(utils);
	if (!mlx_loop_hook(utils->mlx, render_image, utils))
		return (ft_putendl_fd(MLX_DFL_MSG, STDERR_FILENO), 0);
	mlx_loop(utils->mlx);
	return (1);
}
