/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:51:41 by nvillalt          #+#    #+#             */
/*   Updated: 2024/08/29 16:52:05 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	print_error(int type)
{
	if (type == MLX_ERROR)
		ft_putendl_fd(MLX_ERROR_MSG, 2);
	else if (type == MEM_ERROR)
		ft_putendl_fd(MEM_ERROR_MSG, 2);
	else if (type == IMG_ERROR)
		ft_putendl_fd(MLX_IMG_ERROR, 2);
	return (FUNC_FAIL);
}
