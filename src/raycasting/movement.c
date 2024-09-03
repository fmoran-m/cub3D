/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:22:41 by nvillalt          #+#    #+#             */
/*   Updated: 2024/09/03 15:47:59 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	spin_move(t_move *move, t_utils *utils, int type)
{
	if (type == 0)
	{
		utils->player->dir_x = move->old_dir_x * cos(THETA)
			- move->old_dir_y * sin(THETA);
		utils->player->dir_y = move->old_dir_x * sin(THETA)
			+ move->old_dir_y * cos(THETA);
		utils->player->plane_x = move->old_plane_x * cos(THETA)
			- move->old_plane_y * sin(THETA);
		utils->player->plane_y = move->old_plane_x * sin(THETA)
			+ move->old_plane_y * cos(THETA);
	}
	else if (type == 1)
	{
		utils->player->dir_x = move->old_dir_x * cos(-THETA)
			- move->old_dir_y * sin(-THETA);
		utils->player->dir_y = move->old_dir_x * sin(-THETA)
			+ move->old_dir_y * cos(-THETA);
		utils->player->plane_x = move->old_plane_x * cos(-THETA)
			- move->old_plane_y * sin(-THETA);
		utils->player->plane_y = move->old_plane_x * sin(-THETA)
			+ move->old_plane_y * cos(-THETA);
	}
	return ;
}

static void	move_right_left(t_move *move, t_utils *utils, int type)
{
	if (type == 0)
	{
		move->new_pos_x = utils->player->pos_x + utils->player->plane_x
			* SPEED;
		move->new_pos_y = utils->player->pos_y + utils->player->plane_y
			* SPEED;
		if (check_hit_x(utils->player, utils->map, move->new_pos_x))
			utils->player->pos_x = move->new_pos_x;
		if (check_hit_y(utils->player, utils->map, move->new_pos_y))
			utils->player->pos_y = move->new_pos_y;
	}
	else if (type == 1)
	{
		move->new_pos_x = utils->player->pos_x - utils->player->plane_x
			* SPEED;
		move->new_pos_y = utils->player->pos_y - utils->player->plane_y
			* SPEED;
		if (check_hit_x(utils->player, utils->map, move->new_pos_x))
			utils->player->pos_x = move->new_pos_x;
		if (check_hit_y(utils->player, utils->map, move->new_pos_y))
			utils->player->pos_y = move->new_pos_y;
	}
	return ;
}

static void	move_up_down(t_move *move, t_utils *utils, int type)
{
	if (type == 0)
	{
		move->new_pos_x = utils->player->pos_x + utils->player->dir_x
			* SPEED;
		move->new_pos_y = utils->player->pos_y + utils->player->dir_y
			* SPEED;
		if (check_hit_x(utils->player, utils->map, move->new_pos_x))
			utils->player->pos_x = move->new_pos_x;
		if (check_hit_y(utils->player, utils->map, move->new_pos_y))
			utils->player->pos_y = move->new_pos_y;
		return ;
	}
	else if (type == 1)
	{
		move->new_pos_x = utils->player->pos_x - utils->player->dir_x
			* SPEED;
		move->new_pos_y = utils->player->pos_y - utils->player->dir_y
			* SPEED;
		if (check_hit_x(utils->player, utils->map, move->new_pos_x))
			utils->player->pos_x -= utils->player->dir_x * SPEED;
		if (check_hit_y(utils->player, utils->map, move->new_pos_y))
			utils->player->pos_y -= utils->player->dir_y * SPEED;
	}
	return ;
}

static void	spin(t_move *move, t_utils *utils)
{
	if (mlx_is_key_down(utils->mlx, MLX_KEY_RIGHT))
		spin_move(move, utils, 0);
	else if (mlx_is_key_down(utils->mlx, MLX_KEY_LEFT))
		spin_move(move, utils, 1);
	return ;
}

void	inputs(t_utils *utils)
{
	t_move	move;

	move.old_dir_x = utils->player->dir_x;
	move.old_dir_y = utils->player->dir_y;
	move.old_plane_x = utils->player->plane_x;
	move.old_plane_y = utils->player->plane_y;
	if (mlx_is_key_down(utils->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(utils->mlx);
	if (mlx_is_key_down(utils->mlx, MLX_KEY_W))
		move_up_down(&move, utils, 0);
	else if (mlx_is_key_down(utils->mlx, MLX_KEY_S))
		move_up_down(&move, utils, 1);
	else if (mlx_is_key_down(utils->mlx, MLX_KEY_D))
		move_right_left(&move, utils, 0);
	else if (mlx_is_key_down(utils->mlx, MLX_KEY_A))
		move_right_left(&move, utils, 1);
	else
		spin(&move, utils);
	return ;
}
