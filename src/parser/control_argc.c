#include "../../cub3D.h"

int	file_checker(char *argv, char *ext)
{
	char	*file_type;

	if (!ft_strcmp(argv, ext))
		return (0);
	file_type = ft_strrchr(argv, '.');
	if (!file_type || ft_strcmp(ext, file_type) != 0)
		return (0);
	return (1);
}
