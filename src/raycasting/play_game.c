/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:45:48 by nvillalt          #+#    #+#             */
/*   Updated: 2024/08/29 16:49:13 by nvillalt         ###   ########.fr       */
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
	utils->text->text[2].text= mlx_load_xpm42(utils->data->south);
	utils->text->text[3].text = mlx_load_xpm42(utils->data->west);
	while (++i < 4)
	{
		if (!utils->text->text[i].text)
			return (free_structs(utils), EXIT_FAILURE);
	}
	load_textures(utils->text, utils);
}

static int	check_hit_x(t_player *player, t_map *map, double new_pos_x)
{
	int	pos_y;
	int pos_x;

	pos_y = floor(player->pos_y);
	pos_x = floor(new_pos_x);
	if (map->map[pos_y][pos_x] == '1')
		return 0;
	return 1;
}

static int	check_hit_y(t_player *player, t_map *map, double new_pos_y)
{
	int	pos_y;
	int pos_x;

	pos_x = (player->pos_x);
	pos_y = (new_pos_y);
	if (map->map[pos_y][pos_x] == '1')
		return 0;
	return 1;
}

static void inputs(t_utils *utils)
{
    double      speed;
	double		theta;
    double      old_dir_x;
    double      old_dir_y;
	double		old_plane_x;
	double		old_plane_y;
	double 		new_pos_x;
	double 		new_pos_y;

    speed = 0.05;
    theta = 0.05;
    old_dir_x = utils->player->dir_x;
    old_dir_y = utils->player->dir_y;
	old_plane_x = utils->player->plane_x;
	old_plane_y = utils->player->plane_y;
    if (mlx_is_key_down(utils->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(utils->mlx);
    if (mlx_is_key_down(utils->mlx, MLX_KEY_W))
    {
		new_pos_x = utils->player->pos_x + utils->player->dir_x * speed; 
		new_pos_y = utils->player->pos_y + utils->player->dir_y * speed; 
		if (check_hit_x(utils->player, utils->map, new_pos_x)
			&& check_hit_y(utils->player, utils->map, new_pos_y))
			utils->player->pos_x = new_pos_x;
		if (check_hit_y(utils->player, utils->map, new_pos_y)
			&& check_hit_x(utils->player, utils->map, new_pos_x))
 			utils->player->pos_y = new_pos_y;
    }
    else if (mlx_is_key_down(utils->mlx, MLX_KEY_S))
    {
		new_pos_x = utils->player->pos_x - utils->player->dir_x * speed; 
		new_pos_y = utils->player->pos_y - utils->player->dir_y * speed; 
		if (check_hit_x(utils->player, utils->map, new_pos_x)
			&& check_hit_y(utils->player, utils->map, new_pos_y))
            utils->player->pos_x -= utils->player->dir_x * speed;
		if (check_hit_y(utils->player, utils->map, new_pos_y)
			&& check_hit_x(utils->player, utils->map, new_pos_x))
            utils->player->pos_y -= utils->player->dir_y * speed;
    }
	else if (mlx_is_key_down(utils->mlx, MLX_KEY_D))
    {
		new_pos_x = utils->player->pos_x + utils->player->plane_x * speed; 
		new_pos_y = utils->player->pos_y + utils->player->plane_y * speed; 
		if (check_hit_x(utils->player, utils->map, new_pos_x)
			&& check_hit_y(utils->player, utils->map, new_pos_y))
        	utils->player->pos_x = new_pos_x;
		if (check_hit_y(utils->player, utils->map, new_pos_y)
			&& check_hit_x(utils->player, utils->map, new_pos_x))
        	utils->player->pos_y = new_pos_y;
    }
	else if (mlx_is_key_down(utils->mlx, MLX_KEY_A))
	{
		new_pos_x = utils->player->pos_x - utils->player->plane_x * speed; 
		new_pos_y = utils->player->pos_y - utils->player->plane_y * speed; 
		if (check_hit_x(utils->player, utils->map, new_pos_x)
			&& check_hit_y(utils->player, utils->map, new_pos_y))
        	utils->player->pos_x = new_pos_x;
		if (check_hit_y(utils->player, utils->map, new_pos_y)
			&& check_hit_x(utils->player, utils->map, new_pos_x))
        	utils->player->pos_y = new_pos_y;
	}
    else if (mlx_is_key_down(utils->mlx, MLX_KEY_RIGHT))
    {
        utils->player->dir_x = old_dir_x * cos(-theta) - old_dir_y * sin(-theta);
        utils->player->dir_y = old_dir_x * sin(-theta) + old_dir_y * cos(-theta);
        utils->player->plane_x = old_plane_x * cos(-theta) - old_plane_y * sin(-theta);
        utils->player->plane_y = old_plane_x * sin(-theta) + old_plane_y * cos(-theta);
    }
    else if (mlx_is_key_down(utils->mlx, MLX_KEY_LEFT))
    {
        utils->player->dir_x = old_dir_x * cos(theta) - old_dir_y * sin(theta);
        utils->player->dir_y = old_dir_x * sin(theta) + old_dir_y * cos(theta);
        utils->player->plane_x = old_plane_x * cos(theta) - old_plane_y * sin(theta);
        utils->player->plane_y = old_plane_x * sin(theta) + old_plane_y * cos(theta);
    }
    return;
}

static void	render_image(void   *param)
{
	t_utils     *utils;

	utils = (t_utils *)param;
    mlx_delete_image(utils->mlx, utils->img);
	raycasting(utils);
	mlx_image_to_window(utils->mlx, utils->img, 0, 0);
    inputs(utils);
    return;
}

void	play_game(t_utils *utils)
{
	utils->mlx = mlx_init(IMG_WIDTH, IMG_HEIGHT, "Cub3D", TRUE);
	start_maze(utils);
	mlx_loop_hook(utils->mlx, render_image, utils);
	mlx_loop(utils->mlx);
}