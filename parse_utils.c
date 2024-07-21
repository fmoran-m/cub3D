#include "cub3D.h"

int	check_params(t_data *data)
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
	{
		data->data_fill = 1;
		return (1);
	}
	else
		return (0);
}

int	avoid_spaces(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == 32) 
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

