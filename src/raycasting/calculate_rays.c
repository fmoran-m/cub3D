#include "../../cub3D.h"

static void	remove_fisheye_get_walls(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = ray->sideDistX - ray->deltaDistX;
	else if (ray->side == 1)
		ray->perpWallDist = ray->sideDistY - ray->deltaDistY;
	ray->lineHeight = (int)(IMG_HEIGHT / ray->perpWallDist);
	ray->drawStart = (-ray->lineHeight / 2) + (IMG_HEIGHT / 2); // Aquí se pueden editar los tamaños de las paredes, multiplicando o dividiendo IMG_HEIGHT
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = (ray->lineHeight / 2) + (IMG_HEIGHT / 2);
	if (ray->drawEnd >= IMG_HEIGHT)
		ray->drawEnd = IMG_HEIGHT - 1;
}

// jump to next map square, either in x-direction, or in y-direction
static void	get_collision(t_utils *utils, t_ray *ray)
{
	while (ray->hit == NO_HIT)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0; // Rayo encontró una pared en vertical
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY; // hacia qué lado se moverá el moñeco
			ray->side = 1; // Hittea pared horizontal
		}
		if (utils->map->map[ray->mapX][ray->mapY] == '1')
			ray->hit = HIT;
	}
}

// Depending on the ray's direction, initialize steps (stepX, stepY) to move through the grid.
static void	step_initialisation(t_ray *ray, t_player *player)
{
	if (ray->rayDirX < 0) // El rayo va a la izq
	{
		ray->stepX = -1;
		ray->sideDistX = (player->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1 - player->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0) // El rayo va hacia arriba
	{
		ray->stepY = -1;
		ray->sideDistY = (player->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1 - player->posY) * ray->sideDistY;
	}
}

static void	set_ray(t_utils *utils, t_ray *ray, int column)
{
	int	w;

	w = IMG_WIDTH; // Se tiene que hacer en todos los pixeles de la pantalla
	ray->cameraX = 2 * (float)column / (float)w - 1; // Normalizar
	ray->rayDirX = utils->player->dirX + utils->player->planeX * ray->cameraX;
	ray->rayDirY = utils->player->dirY + utils->player->planeY * ray->cameraX;
	ray->mapX = (int)utils->player->posX;
	ray->mapY = (int)utils->player->posY;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX); // fabs sirve para tener el valor absoluto para floats
	if (ray->rayDirY == 0)
		ray->rayDirY = 1e30; // Ojo que esto puede dar error
	else
		ray->deltaDistY = fabs(1 / utils->ray->rayDirY);
	step_initialisation(ray, utils->player);
}

static void draw_pixel(mlx_image_t* img, uint32_t x, uint32_t y, uint32_t color) {
    // Verifica que las coordenadas estén dentro de los límites de la imagen
    if (x >= img->width || y >= img->height)
        return;

    // Calcula la posición del pixel en el arreglo
    uint32_t position = y * img->width + x;

    // El arreglo pixels está compuesto de uint8_t, pero los colores son uint32_t.
    // Cada píxel ocupa 4 bytes (RGBA), por lo que multiplicamos la posición por 4.
    uint32_t* pixel_ptr = (uint32_t*)&img->pixels[position * 4];

    // Asigna el valor del color
    *pixel_ptr = color;
}

static void	draw_wall_column(t_utils *utils, int column)
{
	int y = utils->ray->drawStart;

	while (y <= utils->ray->drawEnd)
	{
		draw_pixel(utils->img, column, y, 255);
		y++;
	}
	return ;
}

void	raycasting(t_utils *utils)
{
	int	column;
	int	screen_width;

	column = 0;
	screen_width = IMG_WIDTH;
	while (column < screen_width)
	{
		set_ray(utils, utils->ray, column);
		get_collision(utils, utils->ray);
		remove_fisheye_get_walls(utils->ray);
		draw_wall_column(utils, column);
		printf("RAYO %d: RayDirX = %f, RayDirY = %f\n", column, utils->ray->rayDirX, utils->ray->rayDirY);
		column++;
	}
	mlx_image_to_window(utils->mlx, utils->img, 0, 0);
	return ;
}