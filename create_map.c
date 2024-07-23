#include "cub3D.h"

static int	is_map_dir(char c)
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

static int	check_last_column(t_utils *utils, int y, int x)
{
	if (avoid_spaces(utils->map->map[y][x - 1]))
	{
		ft_putendl_fd("Error, incorrect format", 2);
		return (0);
	}
	if (y != 0)
	{
		if (avoid_spaces(utils->map->map[y - 1][x])
			|| utils->map->map[y - 1][x - 1])
		{
			ft_putendl_fd("Error, incorrect format", 2);
			return (0);
		}
	}
	if (y != utils->data->map_size - 1)
	{
		if (avoid_spaces(utils->map->map[y + 1][x])
			|| utils->map->map[y + 1][x - 1])
		{
			ft_putendl_fd("Error, incorrect format", 2);
			return (0);
		}
	}
	return (1);
}

static int	check_first_column(t_utils *utils, int y, int x)
{
	if (avoid_spaces(utils->map->map[y][x + 1]))
	{
		ft_putendl_fd("Error, incorrect format", 2);
		return (0);
	}
	if (y != 0)
	{
		if (avoid_spaces(utils->map->map[y - 1][x])
			|| avoid_spaces(utils->map->map[y - 1][x + 1]))
		{
			ft_putendl_fd("Error, incorrect format", 2);
			return (0);
		}
	}
	if (y != utils->data->map_size - 1)
	{
		if (avoid_spaces(utils->map->map[y + 1][x]) 
			|| avoid_spaces(utils->map->map[y + 1][x + 1]))
		{
			ft_putendl_fd("Error, incorrect format", 2);
			return (0);
		}
	}
	return (1);
}

static int	check_last_row(t_utils *utils, int y, int x)
{
	if (avoid_spaces(utils->map->map[y - 1][x])
		|| avoid_spaces(utils->map->map[y][x - 1])
		|| avoid_spaces(utils->map->map[y][x + 1])
		|| avoid_spaces(utils->map->map[y - 1][x + 1])
		|| avoid_spaces(utils->map->map[y - 1][x - 1]))
	{
		ft_putendl_fd("Error, incorrect format", 2);
		return (0);
	}
	return (1);
}

static int	check_first_row(t_utils *utils, int y, int x)
{
	if (avoid_spaces(utils->map->map[y + 1][x])
		|| avoid_spaces(utils->map->map[y][x - 1])
		|| avoid_spaces(utils->map->map[y][x + 1])
		|| avoid_spaces(utils->map->map[y + 1][x + 1])
		|| avoid_spaces(utils->map->map[y + 1][x - 1]))
	{
		ft_putendl_fd("Error, incorrect format", 2);
		return (0);
	}
	return (1);
}

static int	check_middle_square(t_utils *utils, int y, int x)
{
	if (avoid_spaces(utils->map->map[y - 1][x - 1])
		|| avoid_spaces(utils->map->map[y - 1][x])
		|| avoid_spaces(utils->map->map[y - 1][x + 1])
		|| avoid_spaces(utils->map->map[y][x - 1])
		|| avoid_spaces(utils->map->map[y][x + 1])
		|| avoid_spaces(utils->map->map[y + 1][x - 1])
		|| avoid_spaces(utils->map->map[y + 1][x])
		|| avoid_spaces(utils->map->map[y + 1][x + 1]))
	{
		ft_putendl_fd("Error, incorrect format", 2);
		return (0);
	}
	return (1);
}

static int	check_space(t_utils *utils, int y, int x)
{
	if (x == 0)
	{
		if (!check_first_column(utils, y, x))
			return (0);
	}
	else if (x == utils->data->map_width - 1)
	{
		if (!check_last_column(utils, y, x))
			return (0);
	}
	else if (y == 0)
	{
		if (!check_first_row(utils, y, x))
			return (0);
	}
	else if (y == utils->data->map_size - 1)
	{
		if (!check_last_row(utils, y, x))
			return (0);
	}
	else
	{
		if (!check_middle_square(utils, y, x))
			return (0);
	}
	return (1);
}

static int	validate_map(t_utils *utils)
{
	int	y;
	int	x;
	int	mapchar_flag;
	int	zero_flag;

	y = 0;
	x = 0;
	mapchar_flag = 0;
	zero_flag = 0;
	while (y < utils->data->map_size)
	{
		while (utils->map->map[y][x])
		{
			if (utils->map->map[y][x] == '0' || is_map_dir(utils->map->map[y][x]))
			{
				zero_flag = 1;
				if (!check_space(utils, y, x))
					return (0);
			}
			//else if (utils->map->map[y][x] == '1')
			//{
			//	if (!check_single_one(utils, y, x)
			//		return (0);
			//}
			else if (is_map_dir(utils->map->map[y][x]))
			{
				if (mapchar_flag == 1)
				{
					ft_putendl_fd("Error, incorrect format", 2);
					return (0);
				}
				mapchar_flag = 1;
			}
			x++;
		}
		y++;
	}
	if (zero_flag == 0)
	{
		ft_putendl_fd("Error, incorrect format", 2);
		return (0);
	}
	return (1);
}

static int	allocate_line(t_map *map, char *line, int i)
{
	int j;

	j = 0;
	while (line[j] && line[j] != '\n')
		j++;
	map->map[i] = ft_calloc(j + 1, sizeof(char));
	if (!map->map[i])
	{
		ft_putendl_fd("Error, memory allocation", 2); // Liberar toda la matriz
		return (0);
	}
	j = 0;
	while (line[j] && line[j] != '\n')
	{
		map->map[i][j] = line[j];
		j++;
	}
	return (1);
}

static int	allocate_map(t_utils *utils, int fd)
{
	char	*line;
	int		i;

	i = 0;
	utils->map->map = ft_calloc(utils->data->map_size + 1, sizeof(char *));
	if (!utils->map->map)
	{
		ft_putendl_fd("Error, memory allocation", 2);
		return (0);
	}
	while (i < utils->data->map_size)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!allocate_line(utils->map, line, i))
			return (free(line), 0);
		free(line);
		i++;
	}
	return (1);
}

int	create_map(t_utils *utils, char *doc)
{
	int		fd;
	size_t	i;
	char	*line;

	i = 0;
	fd = open(doc, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Open error", 2);
		return (0);
	}
	while (i < utils->data->empty_lines)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		free(line);
		i++;
	}
	if (!allocate_map(utils, fd))
		return (0);
	if (!validate_map(utils))
		return (0);
	return (1);
}
