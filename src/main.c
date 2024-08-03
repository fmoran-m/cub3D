#include "../cub3D.h"

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
	// for (int i = 0; map.map[i]; i++)
	// 	printf("%s\n", map.map[i]);
	start_player(&utils);
	printf("Pos del jugador: %f,%f\nDireccion: %f, %f\n, Plane: %f, %f\n", utils.player->posX, utils.player->posY, utils.player->dirX, utils.player->dirY, utils.player->planeX, utils.player->planeY);
	start_window(&utils);
	free_structs(&utils);
	return (EXIT_SUCCESS);
}
