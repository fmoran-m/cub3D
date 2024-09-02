/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_argc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:50:00 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/09/02 13:51:00 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
