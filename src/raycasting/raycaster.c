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
	ray->line = (int)(IMG_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line / 2 + IMG_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line / 2 + IMG_HEIGHT / 2;
	if (ray->draw_end >= IMG_HEIGHT)
		ray->draw_end = IMG_HEIGHT - 1;
}

static double get_ray_impact(t_ray *ray, t_player *player)
{
	double square_impact;

	if (ray->side == VERTICAL_AXIS)
		square_impact = (player->pos_y + ray->wall_dist) * ray->ray_dir_y;
	else
		square_impact = (player->pos_x + ray->wall_dist) * ray->ray_dir_x;
	return (square_impact);
}

static int	get_text_x(t_ray *ray, t_img text, double square_impact)
{
	int text_x;

	text_x = (int)(square_impact * text.display->width);
	if (ray->side == VERTICAL_AXIS && ray->ray_dir_x > 0) 
		text_x = text.display->width - text_x - 1;
	if (ray->side == HORIZONAL_AXIS && ray->ray_dir_y < 0) 
		text_x = text.display->width - text_x - 1;
	return text_x;
}

static double get_step(t_ray *ray, t_img text)
{
	double	step;
	int		line_height;	

	line_height = ray->draw_end - ray->draw_start;
	step = (float)text.display->height / (float)line_height;
	return (step);
}

double	get_text_pos(t_ray *ray, double step)
{
	double text_pos;
	int		line_height;	

	line_height = ray->draw_end - ray->draw_start;
	text_pos = (ray->draw_start - IMG_HEIGHT / 2 + line_height / 2) * step;
	return (text_pos);
}

int	get_text_color(int text_x, int text_y, t_img texture)
{
	uint32_t color;
	uint32_t i;

	color = 0;
	i = (texture.display->width * text_y + text_x) * 4;
	color |= texture.display->pixels[i] << 24;
	color |= texture.display->pixels[i + 1] << 16;
	color |= texture.display->pixels[i + 2] << 8; 
	color |= texture.display->pixels[i + 3];
	return color;
}

static t_img    select_texture(t_ray *ray, t_img *text)
{
    if (ray->side == HORIZONAL_AXIS && ray->ray_dir_y <= 0)
        return (text[0]);
    if (ray->side == VERTICAL_AXIS && ray->ray_dir_x >= 0)
        return (text[1]);
    if (ray->side == VERTICAL_AXIS && ray->ray_dir_x < 0)
        return (text[2]);
    return(text[3]);
}

static void	draw_wall(t_utils *utils, int *y, int x)
{
	double		square_impact;
	int			text_x;
	int			text_y;
	uint32_t	color;
    t_img       texture;
	double		text_pos;
	double		step;

	square_impact = get_ray_impact(utils->ray, utils->player);
	square_impact -= floor(square_impact);
    texture = select_texture(utils->ray, utils->text->text);
	text_x = get_text_x(utils->ray, texture, square_impact);
	step = get_step(utils->ray, texture);
	text_pos = get_text_pos(utils->ray, step);
	while(*y < utils->ray->draw_end)
	{
		text_y = (int)text_pos & (texture.display->height - 1);
		text_pos += step;
		color = get_text_color(text_x, text_y, texture);
		mlx_put_pixel(utils->img, x, *y, color);
        *y = *y + 1;
	}
	return;
}

void	draw_line(t_utils *utils, int x)
{
	int 		y;

    y = utils->ray->draw_start;
	while(y < utils->ray->draw_start)
	{
		mlx_put_pixel(utils->img, x, y, utils->data->ceiling);
		y++;
	}
    draw_wall(utils, &y, x);
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
