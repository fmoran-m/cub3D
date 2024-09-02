/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:50:56 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/09/02 15:17:40 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	xpm_checker(t_data *data)
{
	if (!file_checker(data->north, ".xpm42"))
		return (0);
	if (!file_checker(data->west, ".xpm42"))
		return (0);
	if (!file_checker(data->east, ".xpm42"))
		return (0);
	if (!file_checker(data->south, ".xpm42"))
		return (0);
	return (1);
}

int	is_dir_char(char c)
{
	if (c == 'N' || c == 'E'
		|| c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	is_map_dir(char c)
{
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'W')
		return (1);
	if (c == 'E')
		return (1);
	return (0);
}

int	check_middle_square(t_map *map, int y, int x)
{
	if (null_avoid_spaces(map->map[y - 1][x - 1])
		|| null_avoid_spaces(map->map[y - 1][x])
		|| null_avoid_spaces(map->map[y - 1][x + 1])
		|| null_avoid_spaces(map->map[y][x - 1])
		|| null_avoid_spaces(map->map[y][x + 1])
		|| null_avoid_spaces(map->map[y + 1][x - 1])
		|| null_avoid_spaces(map->map[y + 1][x])
		|| null_avoid_spaces(map->map[y + 1][x + 1]))
	{
		ft_putendl_fd(INC_FORMAT, STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	check_space(t_map *map, int y, int x)
{
	if (x == 0)
		return (ft_putendl_fd(INC_FORMAT, STDOUT_FILENO), 0);
	else if (x == map->map_width - 1)
		return (ft_putendl_fd(INC_FORMAT, STDOUT_FILENO), 0);
	else if (y == 0)
		return (ft_putendl_fd(INC_FORMAT, STDOUT_FILENO), 0);
	else if (y == map->map_size - 1)
		return (ft_putendl_fd(INC_FORMAT, STDOUT_FILENO), 0);
	else
	{
		if (!check_middle_square(map, y, x))
			return (0);
	}
	return (1);
}
