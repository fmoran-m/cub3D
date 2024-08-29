/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:28:12 by nvillalt          #+#    #+#             */
/*   Updated: 2024/08/29 17:42:42 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	free_textures(t_graphs *text)
{
	if (text->text[0].text != NULL)
		mlx_delete_xpm42(text->text[0].text);
	if (text->text[1].text != NULL)
		mlx_delete_xpm42(text->text[1].text);
	if (text->text[2].text != NULL)
		mlx_delete_xpm42(text->text[2].text);
	if (text->text[3].text != NULL)
		mlx_delete_xpm42(text->text[3].text);
}

void	free_structs(t_utils *utils)
{
	if (utils->data->north)
		free(utils->data->north);
	if (utils->data->south)
		free(utils->data->south);
	if (utils->data->east)
		free(utils->data->east);
	if (utils->data->west)
		free(utils->data->west);
	if (utils->map->map)
		free_matrix(utils->map->map);
	if (utils->player)
		free(utils->player);
	if (utils->ray)
		free(utils->ray);
	if (utils->text)
	{
		free_textures(utils->text);
		free(utils->text);
	}
}
