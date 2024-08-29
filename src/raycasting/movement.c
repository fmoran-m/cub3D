/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:22:41 by nvillalt          #+#    #+#             */
/*   Updated: 2024/08/29 20:11:52 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void inputs(t_utils *utils)
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
		if (check_hit_x(utils->player, utils->map, new_pos_x))
			utils->player->pos_x = new_pos_x;
		if (check_hit_y(utils->player, utils->map, new_pos_y))
 			utils->player->pos_y = new_pos_y;
    }
    else if (mlx_is_key_down(utils->mlx, MLX_KEY_S))
    {
		new_pos_x = utils->player->pos_x - utils->player->dir_x * speed; 
		new_pos_y = utils->player->pos_y - utils->player->dir_y * speed; 
		if (check_hit_x(utils->player, utils->map, new_pos_x))
            utils->player->pos_x -= utils->player->dir_x * speed;
		if (check_hit_y(utils->player, utils->map, new_pos_y))
            utils->player->pos_y -= utils->player->dir_y * speed;
    }
	else if (mlx_is_key_down(utils->mlx, MLX_KEY_D))
    {
		new_pos_x = utils->player->pos_x + utils->player->plane_x * speed; 
		new_pos_y = utils->player->pos_y + utils->player->plane_y * speed; 
		if (check_hit_x(utils->player, utils->map, new_pos_x))
        	utils->player->pos_x = new_pos_x;
		if (check_hit_y(utils->player, utils->map, new_pos_y))
        	utils->player->pos_y = new_pos_y;
    }
	else if (mlx_is_key_down(utils->mlx, MLX_KEY_A))
	{
		new_pos_x = utils->player->pos_x - utils->player->plane_x * speed; 
		new_pos_y = utils->player->pos_y - utils->player->plane_y * speed; 
		if (check_hit_x(utils->player, utils->map, new_pos_x))
        	utils->player->pos_x = new_pos_x;
		if (check_hit_y(utils->player, utils->map, new_pos_y))
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
