#include "cub3D.h"

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
	{
		free_structs(&utils);
		return (1);
	}
	printf("North: %s\n", data.north);
	printf("South: %s\n", data.south);
	printf("East: %s\n", data.east);
	printf("West: %s\n", data.west);
	printf("Floor: %d\n", data.floor);
	printf("Ceiling: %d\n", data.ceiling);
	free_structs(&utils);
	return (0);
}
