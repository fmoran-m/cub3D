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
		if (!is_correct_char(line[i]))
		{
			ft_putendl_fd("Error, incorrect format", 2);
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

static int	check_map(char *line, int *space_flag, t_map *map)
{
	int	i;
	int	char_flag;

	i = 0;
	char_flag = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_correct_char(line[i]))
			return (ft_putendl_fd(INC_FORMAT, STDOUT_FILENO), 0);
		if (is_map_char(line[i]) && *space_flag == 1)
			return (ft_putendl_fd(INC_FORMAT, STDOUT_FILENO), 0);
		if (is_map_char(line[i]))
			char_flag = 1;
		i++;
		if (i > map->map_width)
			map->map_width = i;
	}
	if (char_flag == 0)
		*space_flag = 1;
	return (1);
}

static int	check_map_status(t_utils *utils, char *line, int *status, size_t *n)
{
	int	space_flag;

	space_flag = 0;
	if (*status == 0)
	{
		if (!get_to_map(line, status, utils->data))
			return (0);
	}
	if (*status == 1)
	{
		if (!check_map(line, &space_flag, utils->map))
			return (0);
		if (!space_flag)
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
