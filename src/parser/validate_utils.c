#include "../../cub3D.h"

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
		ft_putendl_fd("Error, incorrect format", 2);
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
