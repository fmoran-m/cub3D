#include "cub3D.h"

static int	validate_line(t_map *map, int y, int *zero_flag, int *mapchar_flag)
{
	int	x;

	x = 0;
	while (map->map[y][x])
	{
		if (map->map[y][x] == '0' || is_map_dir(map->map[y][x]))
		{
			*zero_flag = 1;
			if (!check_space(map, y, x))
				return (0);
		}
		else if (is_map_dir(map->map[y][x]))
		{
			if (*mapchar_flag == 1)
			{
				ft_putendl_fd("Error, incorrect format", 2);
				return (0);
			}
			*mapchar_flag = 1;
		}
		x++;
	}
	return (1);
}

static int	validate_map(t_map *map)
{
	int	y;
	int	mapchar_flag;
	int	zero_flag;

	y = 0;
	mapchar_flag = 0;
	zero_flag = 0;
	while (y < map->map_size)
	{
		if (!validate_line(map, y, &zero_flag, &mapchar_flag))
			return (0);
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
	int	j;

	map->map[i] = ft_calloc(map->map_width + 1, sizeof(char));
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
	utils->map->map = ft_calloc(utils->map->map_size + 1, sizeof(char *));
	if (!utils->map->map)
	{
		ft_putendl_fd("Error, memory allocation", 2);
		return (0);
	}
	while (i < utils->map->map_size)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
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
			break ;
		free(line);
		i++;
	}
	if (!allocate_map(utils, fd))
		return (0);
	if (!validate_map(utils->map))
		return (0);
	return (1);
}
