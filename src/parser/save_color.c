#include "../../cub3D.h"

static void	change_status(int *status, t_data *data)
{
	if (*status == FLOOR_1)
		*status = F_COMMA_1;
	else if (*status == FLOOR_2)
		*status = F_COMMA_2;
	else if (*status == FLOOR_3)
	{
		*status = PARAMS;
		data->f_flag = 1;
	}
	else if (*status == CEL_1)
		*status = C_COMMA_1;
	else if (*status == CEL_2)
		*status = C_COMMA_2;
	else if (*status == CEL_3)
	{
		*status = PARAMS;
		data->c_flag = 1;
	}
}

static int	control_comma(char *line, int *status, int i)
{
	if (line[i] != ',')
	{
		ft_putendl_fd("Error, incorrect format", 2);
		return (0);
	}
	if (*status == F_COMMA_1)
		*status = FLOOR_2;
	else if (*status == F_COMMA_2)
		*status = FLOOR_3;
	else if (*status == C_COMMA_1)
		*status = CEL_2;
	else if (*status == C_COMMA_2)
		*status = CEL_3;
	return (1);
}

static void	load_channel(t_data *data, int color, int *status)
{
	if (*status == FLOOR_1)
		data->floor = data->floor | (color << 24);
	else if (*status == FLOOR_2)
		data->floor = data->floor | (color << 16);
	else if (*status == FLOOR_3)
		data->floor = data->floor | (color << 8);
	else if (*status == CEL_1)
		data->ceiling = data->ceiling | (color << 24);
	else if (*status == CEL_2)
		data->ceiling = data->ceiling | (color << 16);
	else if (*status == CEL_3)
		data->ceiling = data->ceiling | (color << 8);
}

static int	control_num(t_data *data, char *line, int *status, int i)
{
	int	start;
	int	temp_num;

	start = i;
	while (line[i] && ft_isnum(line[i]))
		i++;
	if (!avoid_spaces(line[i]) && line[i] != ',')
	{
		ft_putendl_fd("Error, incorrect format", 2);
		return (0);
	}
	temp_num = ft_atoi(line + start);
	if (temp_num < 0 || temp_num > 255)
	{
		ft_putendl_fd("Error, incorrect format", 2);
		return (0);
	}
	load_channel(data, temp_num, status);
	change_status(status, data);
	return (i);
}

int	save_color(t_data *data, char *line, int *status)
{
	int	i;

	i = 0;
	while (line[i] && avoid_spaces(line[i]))
		i++;
	if (!line[i])
		return (i);
	if (*status >= 5 && *status <= 10)
	{
		i = control_num(data, line, status, i);
		if (i == 0)
			return (0);
	}
	else if (*status >= 11 && *status <= 14)
	{
		i = control_comma(line, status, i);
		if (i == 0)
			return (0);
	}
	return (i);
}
