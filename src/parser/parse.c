/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:50:40 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/09/02 16:04:38 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	change_status(t_data *data, char *line, int *status)
{
	int	i;

	i = 0;
	while (line[i] && !avoid_spaces(line[i]))
		i++;
	if (ft_strncmp(line, "NO", 2) == 0 && i == 2 && data->north == NULL)
		*status = NORTH;
	else if (ft_strncmp(line, "SO", 2) == 0 && i == 2 && data->south == NULL)
		*status = SOUTH;
	else if (ft_strncmp(line, "EA", 2) == 0 && i == 2 && data->east == NULL)
		*status = EAST;
	else if (ft_strncmp(line, "WE", 2) == 0 && i == 2 && data->west == NULL)
		*status = WEST;
	else if (ft_strncmp(line, "F", 1) == 0 && i == 1 && data->f_flag == 0)
		*status = FLOOR_1;
	else if (ft_strncmp(line, "C", 1) == 0 && i == 1 && data->c_flag == 0)
		*status = CEL_1;
	if (*status != PARAMS)
		return (i);
	else
	{
		ft_putendl_fd(INC_FORMAT, STDERR_FILENO);
		return (0);
	}
}

static int	data_save_assign(t_utils *utils, char *line, int *status, int *i)
{
	int	j;

	j = *i;
	if (avoid_spaces(line[*i]))
		(*i)++;
	else if (*status == PARAMS)
		*i += change_status(utils->data, line + *i, status);
	else if (*status >= 1 && *status <= 4 && !check_params(utils->data))
		*i += save_path(utils->data, line + *i, status);
	else if (*status >= 5 && *status <= 14 && !check_params(utils->data))
		*i += save_color(utils->data, line + *i, status);
	if (j == *i)
		return (0);
	else
		return (1);
}

static int	parse_line(t_utils *utils, char *line, int *status)
{
	int	i;

	i = 0;
	while (line[i] && !check_params(utils->data))
	{
		if (!data_save_assign(utils, line, status, &i))
			return (0);
	}
	if (utils->data->data_fill == 1)
	{
		while (line[i])
		{
			if (!avoid_spaces(line[i]))
			{
				ft_putendl_fd(INC_FORMAT, STDERR_FILENO);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

static int	get_file_data(t_utils *utils, int fd)
{
	char	*line;
	int		status;

	status = PARAMS;
	while (!check_params(utils->data))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!parse_line(utils, line, &status))
			return (free(line), 0);
		free(line);
		utils->data->empty_lines++;
	}
	return (1);
}

int	parse_file(t_utils *utils, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd(FILE_NOT_FOUND, STDERR_FILENO);
		return (0);
	}
	if (!get_file_data(utils, fd))
		return (0);
	if (!get_map(utils, fd))
		return (0);
	close(fd);
	return (1);
}
