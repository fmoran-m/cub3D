/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:50:48 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/09/02 13:59:55 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	assign_dup(t_data *data, char *dup, int status)
{
	if (status == NORTH)
		data->north = dup;
	else if (status == SOUTH)
		data->south = dup;
	else if (status == EAST)
		data->east = dup;
	else if (status == WEST)
		data->west = dup;
}

static char	*get_path(char *line, int *i)
{
	int		start;
	int		n;
	char	*dup;

	n = 0;
	while (line[*i] && avoid_spaces(line[*i]))
		(*i)++;
	if (!line[*i])
		return (NULL);
	start = *i;
	while (line[*i] && !avoid_spaces(line[*i]))
	{
		(*i)++;
		n++;
	}
	dup = ft_substr(line, start, n);
	if (!dup)
	{
		ft_putendl_fd(MEM_ERROR_MSG, STDERR_FILENO);
		return (NULL);
	}
	return (dup);
}

int	save_path(t_data *data, char *line, int *status)
{
	int		fd;
	char	*dup;
	int		i;

	i = 0;
	dup = get_path(line, &i);
	if (!dup)
		return (0);
	fd = open(dup, O_RDONLY);
	if (fd == -1)
	{
		free(dup);
		ft_putendl_fd(PATH_ERR, STDERR_FILENO);
		return (0);
	}
	close(fd);
	assign_dup(data, dup, *status);
	*status = PARAMS;
	return (i);
}
