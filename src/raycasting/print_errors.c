#include "../../cub3D.h"

int	print_error(int	type)
{
	if (type == MLX_ERROR)
		ft_putendl_fd(MLX_ERROR_MSG, 2);
	else if (type == MEM_ERROR)
		ft_putendl_fd(MEM_ERROR_MSG, 2);
	return (FUNC_FAIL);
}
