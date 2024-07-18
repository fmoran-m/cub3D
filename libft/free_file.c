#include "libft.h"

char	*free_file(char **file)
{
	free (*file);
	*file = NULL;
	return (NULL);
}