#include "../../cub3D.h"

void	file_checker(char *argv)
{
	char	*cub;
	char	*file_type;

	cub = ".cub";
	if (!ft_strcmp(argv, cub))
	{
		ft_putendl_fd(EXT_ERR, STDERR_FILENO);
		exit(EXIT_ERR);
	}
	file_type = ft_strrchr(argv, '.');
	if (!file_type || ft_strcmp(cub, file_type) != 0)
	{
		ft_putendl_fd(EXT_ERR, STDERR_FILENO);
		exit(EXIT_ERR);
	}
}
