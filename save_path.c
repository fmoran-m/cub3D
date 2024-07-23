#include "cub3D.h"

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

int	save_path(t_data *data, char *line, int *status)
{
	int		i;
	int		start;
	int		n;
	int		fd;
	char	*dup;

	i = 0;
	n = 0;
	while(line[i] && avoid_spaces(line[i]))
		i++;
	if (!line[i])
		return (i); //CUIDADO CON ESTO
	start = i;
	while (line[i] && !avoid_spaces(line[i]))
	{
		i++;
		n++;
	}
	dup = ft_substr(line, start, n);
	if (!dup)
	{
		ft_putendl_fd("Error: Memory allocation", STDERR_FILENO);
		return (0);
	}
	fd = open(dup, O_RDONLY);
	if (fd == -1) //OJO PERMISOS
	{
		ft_putendl_fd("Error: Path does not exist", STDERR_FILENO);
		return (0);
	}
	close(fd);
	assign_dup(data, dup, *status);
	*status = PARAMS;
	return (i);
}
