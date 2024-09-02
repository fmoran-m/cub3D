/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:07:29 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/09/02 16:16:50 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	main(int argc, char **argv)
{
	t_utils		utils;
	t_map		map;
	t_data		data;

	if (argc != 2)
		return (ft_putendl_fd(ARGC_ERR, STDERR_FILENO), EXIT_ERR);
	if (!file_checker(argv[1], ".cub"))
		return (ft_putendl_fd(EXT_ERR, STDERR_FILENO), EXIT_ERR);
	utils.data = &data;
	utils.map = &map;
	init_utils(&utils);
	if (!parse_file(&utils, argv[1]))
		return (free_structs(&utils), EXIT_ERR);
	if (!xpm_checker(utils.data))
	{
		ft_putendl_fd(XPM_ERR, STDERR_FILENO);
		free_structs(&utils);
		return (EXIT_ERR);
	}
	if (!create_map(&utils, argv[1]))
		return (free_structs(&utils), EXIT_ERR);
	if (!play_game(&utils))
		return (free_structs(&utils), EXIT_ERR);
	free_structs(&utils);
	return (EXIT_SUCCESS);
}
