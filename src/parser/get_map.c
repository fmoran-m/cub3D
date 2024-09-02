/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:50:27 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/09/02 14:07:01 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	is_map_char(char c)
{
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'W')
		return (1);
	if (c == 'E')
		return (1);
	if (c == '0')
		return (1);
	if (c == '1')
		return (1);
	return (0);
}

static int	get_to_map(char *line, int *status, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!avoid_spaces(line[i]) && !is_map_char(line[i]))
		{
			ft_putendl_fd(INC_FORMAT, STDOUT_FILENO);
			return (0);
		}
		if (is_map_char(line[i]))
		{
			*status = 1;
			return (1);
		}
		i++;
	}
	data->empty_lines++;
	return (1);
}

static int	check_map(char *line, t_map *map, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_correct_char(line[i]))
			return (ft_putendl_fd(INC_FORMAT_MAP, STDOUT_FILENO), 0);
		if (is_dir_char(line[i]) && data->dir_flag)
			return (ft_putendl_fd(INC_FORMAT_PLY, STDOUT_FILENO), 0);
		if (is_dir_char(line[i]))
			data->dir_flag = 1;
		i++;
		if (i > map->map_width)
			map->map_width = i;
	}
	return (1);
}

static int	check_map_status(t_utils *utils, char *line, int *status, size_t *n)
{
	if (*status == 0)
	{
		if (!get_to_map(line, status, utils->data))
			return (0);
	}
	if (*status == 1)
	{
		if (!check_map(line, utils->map, utils->data))
			return (0);
		(*n)++;
	}
	return (1);
}

int	get_map(t_utils *utils, int fd)
{
	char	*line;
	size_t	n;
	int		status;

	status = 0;
	n = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!check_map_status(utils, line, &status, &n))
			return (free(line), 0);
		free(line);
	}
	utils->map->map_size = n;
	return (1);
}
