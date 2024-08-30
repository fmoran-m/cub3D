#include "../cub3D.h"
#include <stdio.h>

static int	xpm_checker(t_data *data)
{
	if (!file_checker(data->north, ".xpm42"))
		return (0);
	if (!file_checker(data->west, ".xpm42"))
		return (0);
	if (!file_checker(data->east, ".xpm42"))
		return (0);
	if (!file_checker(data->south, ".xpm42"))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_utils	utils;
	t_map	map;
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd(ARGC_ERR, STDERR_FILENO);
		return (EXIT_ERR);
	}
	if (!file_checker(argv[1], ".cub"))
	{
		ft_putendl_fd(EXT_ERR, STDERR_FILENO);
		return (EXIT_ERR);
	}
	utils.data = &data;
	utils.map = &map;
	init_utils(&utils);
	if (!parse_file(&utils, argv[1]))
	{
		free_structs(&utils);
		return (EXIT_ERR);
	}
	if (!xpm_checker(utils.data))
	{
		ft_putendl_fd(XPM_ERR, STDERR_FILENO);
		free_structs(&utils);
		return (EXIT_ERR);
	}
	if (!create_map(&utils, argv[1]))
	{
		free_structs(&utils);
		return (EXIT_ERR);
	}
	play_game(&utils);
	free_structs(&utils);
	return (EXIT_SUCCESS);
}
