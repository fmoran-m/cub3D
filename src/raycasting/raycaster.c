#include "../../cub3D.h"

static void	dda_algorithm(t_ray *ray, t_map *map)
{
	ray->hit = NO_HIT;
	while (ray->hit == NO_HIT)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = VERTICAL_AXIS;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = HORIZONAL_AXIS;
		}
		if (map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = HIT;
	}
}

static void	steps_initialisation(t_ray *ray, t_player *player)
{
	ray->map_x = floor((int)player->pos_x);
	ray->map_y = floor((int)player->pos_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

static void	set_delta_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_calculations(t_ray *ray, t_player *player, int x)
{
	ray->normalise = 2 * x / (double)IMG_WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->normalise;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->normalise;
}

static void get_line_height(t_ray *ray, t_player *player)
{
	// Wall x -> represents the exact value where the wall was hit, not just the integer coordinates of the wall. 
	// This is required to know which x-coordinate of the texture we have to use.
	if (ray->side == VERTICAL_AXIS)
	{
		ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
		ray->wall_x = player->pos_y + ray->wall_dist * ray->ray_dir_y;
	}
	else if (ray->side == HORIZONAL_AXIS)
	{
		ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
		ray->wall_x = player->pos_x + ray->wall_dist * ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->line = (int)(IMG_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line / 2 + IMG_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line / 2 + IMG_HEIGHT / 2;
	if (ray->draw_end >= IMG_HEIGHT)
		ray->draw_end = IMG_HEIGHT - 1;
}

void	get_texture(t_ray *ray, t_utils *utils, t_graphs *text)
{
    //   Código original de la guía, para que lo revises porsi. Unifiqué la condición en un or porque en los dos casos hace lo mismo.
	//		Finally, texX is the x-coordinate of the texture, and this is calculated out of wallX. <- Sirve para esto
    //   int texX = int(wallX * double(texWidth));
    //   if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
    //   if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
	text->text_x = (int)(ray->wall_x) * (double)text->text[0].display->width;
	if ((ray->side == 0 && utils->player->dir_x > 0)
		|| (ray->side == 1 && utils->player->dir_y < 0))
		text->text_x = text->text[0].display->width - text->text_x - 1;
	text->step = 1.0 * text->text[0].display->height / ray->line;
	text->text_start = (ray->draw_start - IMG_HEIGHT / 2
			+ ray->line / 2) * text->step;
}

// Parámetros: la imagen que queremos usar, el punto de x en el que estamos, el punto de y en el que estamos.
// La x hay que calcularla, de ahí el chorizo en la llamada a la función
static uint32_t	get_color(mlx_image_t *img, int x, int y)
{

}
void	draw_line(t_utils *utils, int x)
{
	int 		y;
	uint32_t	color;

	y = 0;
	get_texture(utils->ray, utils, utils->text);
	while(y < utils->ray->draw_start)
	{
		mlx_put_pixel(utils->img, x, y, utils->data->ceiling);
		y++;
	}
	// Aquí hay que ver qué textura poner dependiendo de a qué pared mire el moñeco, de momento he cogido una de prueba
	while(y <= utils->ray->draw_end)
	{
		//Código original:
		//         // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        // int texY = (int)texPos & (texHeight - 1);
        // texPos += step;
		utils->text->text_y = (int)utils->text->text_start;
		utils->text->text_start += utils->text->step;
		// color = get_color(utils->text->text[0].display, 
		// 	utils->text->text[0].display->width - utils->text->text_x - 1, utils->text->text_y);
		mlx_put_pixel(utils->img, x, y, 255);
		y++;
	}
	
	// while (y <= utils->ray->draw_end)
	// {
	// 	mlx_put_pixel(utils->img, x, y, 0xFF0000FF);
	// 	y++;
	// }
	while(y < IMG_HEIGHT)
	{
		mlx_put_pixel(utils->img, x, y, utils->data->floor);
		y++;
	}
	return;
}

void	raycasting(t_utils *utils)
{
	int	x;

	x = 0;
	utils->img = mlx_new_image(utils->mlx, IMG_WIDTH, IMG_HEIGHT);
	while (x < IMG_WIDTH)
	{
		init_calculations(utils->ray, utils->player, x);
		set_delta_dist(utils->ray);
		steps_initialisation(utils->ray, utils->player);
		dda_algorithm(utils->ray, utils->map);
		get_line_height(utils->ray, utils->player);
		draw_line(utils, x);
		x++;
	}
}
