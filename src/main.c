#include "../cub3D.h"
#include <stdio.h>

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
	file_checker(argv[1]);
	utils.data = &data;
	utils.map = &map;
	init_utils(&utils);
	if (!parse_file(&utils, argv[1]))
	{
		free_structs(&utils);
		return (1);
	}
	if (!create_map(&utils, argv[1]))
	{
		free_structs(&utils);
		return (1);
	}
	play_game(&utils);
	free_structs(&utils);
	return (EXIT_SUCCESS);
}
