#include "cub3D.h"

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

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

int	null_avoid_spaces(char c)
{
	if (c == 0)
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

int	is_correct_char(char c)
{
	if (!avoid_spaces(c) && !is_map_char(c))
		return (0);
	else
		return (1);
}
