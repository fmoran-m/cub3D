#include "../cub3D.h"

void	free_structs(t_utils *utils)
{
	if (utils->data->north)
		free(utils->data->north);
	if (utils->data->south)
		free(utils->data->south);
	if (utils->data->east)
		free(utils->data->east);
	if (utils->data->west)
		free(utils->data->west);
	if (utils->map->map)
		free_matrix(utils->map->map);
	if (utils->player)
		free(utils->player);
	if (utils->ray)
		free(utils->ray);
}
