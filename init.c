#include "cub3D.h"

void	init_data(t_data *data)
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

void	init_utils(t_utils *utils)
{
	init_data(utils->data);
}

