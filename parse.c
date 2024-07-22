#include "cub3D.h"

static int	change_status(t_data *data, char *line, int *status)
{
	int	i;

	i = 0;
	while(line[i] && !avoid_spaces(line[i]))
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
		ft_putendl_fd("Error, incorrect format", STDERR_FILENO);
		return (0);
	}
}

static int	parse_line(t_utils *utils, char *line, int *status)
{
	int	i;
	int	r_value;

	i = 0;
	r_value = 0;
	while (line[i] && !check_params(utils->data))
	{
		if (avoid_spaces(line[i]))
			i++;
		else if (*status == PARAMS )
		{
			r_value = change_status(utils->data, line + i, status);
			if (!r_value)
				return (0);
			i += r_value;
		}
		else if (*status >= 1 && *status <= 4 && !check_params(utils->data))
		{
			r_value = save_path(utils->data, line + i, status);
			if (!r_value)
				return (0);
			i += r_value;
		}
		else if (*status >= 5 && *status <= 14 && !check_params(utils->data))
		{
			r_value = save_color(utils->data, line + i, status);
			if (!r_value)
				return (0);
			i += r_value;
		}
	}
	if (utils->data->data_fill == 1)
	{
		while (line[i])
		{
			if (!avoid_spaces(line[i]))
			{
				ft_putendl_fd("Error, incorect format",  2);
				return(0);
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
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd(FILE_NOT_FOUND, STDERR_FILENO);
		return (0);
	}
	if (!get_file_data(utils, fd))
		return (0);
	if (!get_map(utils->data, fd))
		return (0);
	return (1);
}


