#include "cub3D.h"

static int	is_map_char(char c)
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

static int	is_correct_char(char c)
{
	if (!avoid_spaces(c) && !is_map_char(c))
		return (0);
	else 
		return (1);
}

static int	get_to_map(char *line, int *status, t_data *data)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		i = 0;
		if (!is_correct_char(line[i]))
		{
			printf("entra1\n");
			ft_putendl_fd("Error, incorrect format", 2);
			return (free(line), 0);
		}
		if (is_map_char(line[i]))
		{
			data->empty_lines--;
			*status = 1;
			break;
		}
		i++;
	}
	data->empty_lines++;
	return (1);
}

static int	check_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_correct_char(line[i]))
		{
			ft_putendl_fd("Error, incorrect format", 2);
			return (free(line), 0);
		}
		i++;
	}
	return (1);
}

int	get_map(t_data *data, int fd)
{
	char	*line;
	size_t	n;
	int		status;

	status = 0;
	n = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (status == 0)
		{
			if (!get_to_map(line, &status, data))
				return (0);
		}
		if (status == 1)
		{
			if (!check_map(line))
				return (0);
			n++;
		}
		free(line);
	}
	return (n);
}

