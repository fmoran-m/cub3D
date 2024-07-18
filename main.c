#include "cub3D.h"

static void	file_checker(char *argv)
{
	char	*cub;
	char	*file_type;

	cub = ".cub";
	file_type = ft_strrchr(argv, '.');
	if (!file_type || ft_strcmp(cub, file_type) != 0)
	{
		ft_putendl_fd(EXT_ERR, STDERR_FILENO);
		exit(EXIT_ERR);
	}
}

static int	check_params(t_data *data)
{
	int	i;

	i = 0;
	if (data->north != NULL)
		i++;
	if (data->south != NULL)
		i++;
	if (data->east != NULL)
		i++;
	if (data->west != NULL)
		i++;
	if (data->f_flag)
		i++;
	if (data->c_flag)
		i++;
	if (i == 6)
		return (1);
	else
		return (0);
}

static int	avoid_spaces(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == 32) 
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

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

static int	save_path(t_data *data, char *line, int *status)
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
	fd = open(dup, O_RDONLY);
	if (fd == -1) //OJO PERMISOS
	{
		ft_putendl_fd("Salimos porque no encontramos la ruta", 2);
		exit (1); //ESTA SALIDA HAY QUE HACERLA BIEN
	}
	close(fd);
	assign_dup(data, dup, *status);
	*status = PARAMS;
	return (i);
}

static int	change_status(t_data *data, char *line, int *status)
{
	int	i;

	i = 0;
	while(line[i] && !avoid_spaces(line[i]))
		i++;
	if (ft_strncmp(line, "NO", 2) && i == 2 && data->north == NULL)
		*status = NORTH;
	else if (ft_strncmp(line, "SO", 2) && i == 2 && data->south == NULL)
		*status = SOUTH;
	else if (ft_strncmp(line, "EA", 2) && i == 2 && data->east == NULL)
		*status = EAST;
	else if (ft_strncmp(line, "WE", 2) && i == 2 && data->west == NULL)
		*status = WEST;
	else if (ft_strncmp(line, "F", 1) && i == 1 && data->f_flag == 0)
		data->f_flag = 1;
	else if (ft_strncmp(line, "C", 1) && i == 1 && data->c_flag == 0)
		data->c_flag = 1;
	if (*status != PARAMS)
		return (i);
	else
		return (0);
}

static int	parse_line(t_utils *utils, char *line, int status)
{
	int	i;
	int	r_value;

	i = 0;
	r_value = 0;
	while (line[i] && !check_params(utils->data))
	{
		if (avoid_spaces(line[i]))
			i++;
		else if (status == PARAMS)
		{
			r_value = change_status(utils->data, line + i, &status);
			if (!r_value)
				exit(1);
			i += r_value;
		}
		else if (status >= 1 && status <= 4)
		{
			r_value = save_path(utils->data, line + i, &status);
			if (!r_value)
				exit(1);
			i += r_value;
		}
		/*
		else if (status >= 5 && status <= 6)
		{
			r_value = save_color(utils->data, line + i, &status);
			if (!r_value)
				exit(1);
			i += r_value;
		}
		*/
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
		parse_line(utils, line, status);
		free(line);
	}
	return (1);
}

static int	parse_file(t_utils *utils, char *file)
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
	/*if (!get_map())*/
	/*	return (0);*/
	return (1);
}

static void	init_data(t_data *data)
{
	data->north = NULL;
	data->south = NULL;
	data->east = NULL;
	data->west = NULL;
	data->f_flag = 0;
	data->c_flag = 0;
	data->floor = 0;
	data->ceiling = 0;
}

static void	init_utils(t_utils *utils)
{
	init_data(utils->data);
}

int	main(int argc, char **argv)
{
	t_utils	utils;
	t_data data;

	if (argc != 2)
	{
		ft_putendl_fd(ARGC_ERR, STDERR_FILENO);
		return (EXIT_ERR);
	}
	file_checker(argv[1]);
	utils.data = &data;
	init_utils(&utils);
	if (!parse_file(&utils, argv[1]))
		return (EXIT_ERR);
	printf("North: %s\n", data.north);
	printf("South: %s\n", data.south);
	printf("East: %s\n", data.east);
	printf("West: %s\n", data.west);
	return (0);
}
