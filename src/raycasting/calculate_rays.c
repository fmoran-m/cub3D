#include "../../cub3D.h"

static void	get_walls_height(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
	{
		ray-> perpWallDist = ray->sideDistX - ray->deltaDistX;
		ray->wallX = player->posY + ray->perpWallDist * ray->rayDirY;
	}
	else
	{
		ray->perpWallDist = ray->sideDistY - ray->deltaDistY;
		ray->wallX = player->posX + ray->perpWallDist * ray->rayDirX;
	}
	ray->wallX -= floor(ray->wallX);
	ray->line = (int)(IMG_HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->line / 2 + IMG_HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->line / 2 + IMG_HEIGHT / 2;
	if (ray->drawEnd >= IMG_HEIGHT)
		ray->drawEnd = IMG_HEIGHT - 1;
//	printf("line: %d\nlineStart: %d\nlineEnd: %d\nwallDist: %f\n-----\n", ray->line, ray->drawStart, ray->drawEnd, ray->perpWallDist);
}

// jump to next map square, either in x-direction, or in y-direction
static void	get_collision(t_utils *utils, t_ray *ray)
{
	printf("Con utils: %f\nSin utils: %f\n", utils->ray->deltaDistY, ray->deltaDistY);
	//printf("ENTRAS AQUERA??? ray = %d\nVEZ: %d\n", ray->hit, column);
	while (utils->ray->hit == NO_HIT)
	{
		printf("--->Con utils: %f\n--->Sin utils: %f\n", utils->ray->deltaDistY, ray->deltaDistY);
		printf("ENTRAS AQUI SIQUIERA??? ray = %d\n", ray->hit);
		if (utils->ray->sideDistX < utils->ray->sideDistY)
		{
			printf("Con utils: %f\nSin utils: %f\n", utils->ray->deltaDistX, ray->deltaDistX);
			printf("AntesdeltadistX----> %f\nAntes-sideDistX: %f\n-----\n", utils->ray->deltaDistX, utils->ray->sideDistX);
			utils->ray->sideDistX += utils->ray->deltaDistX;
			printf("Despues-deltadist----> %f\nsideDist: %f\n-----\n", utils->ray->deltaDistX, utils->ray->sideDistX);
			utils->ray->mapX += utils->ray->stepX;
			utils->ray->side = 0; // Rayo encontró una pared en vertical
		}
		else
		{
			printf("ENTRAS????????\n\n\n");
			printf("antes-deltadistY----> %f\nsideDistY: %f\n-----\n", utils->ray->deltaDistY, utils->ray->sideDistY);
			utils->ray->sideDistY += utils->ray->deltaDistY;
			printf("despues-deltadist----> %f\nsideDist: %f\n-----\n", utils->ray->deltaDistY, utils->ray->sideDistY);
			utils->ray->mapY += utils->ray->stepY; // hacia qué lado se moverá el moñeco
			utils->ray->side = 1; // Hittea pared horizontal
		}
		if (utils->map->map[(int)utils->ray->mapX][(int)utils->ray->mapY] == '1')
			utils->ray->hit = HIT;
	}
//	printf("Deltadist x = %f\nDeltadist y = %f\n Collision sidedistx = %f\nCollision sidedisty = %f\n", ray->deltaDistX, ray->deltaDistY, ray->sideDistX, ray->sideDistY);
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
		ray->sideDistX = (ray->mapX + 1.0 - player->posX) * ray->deltaDistX;
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
	ray->cameraX = (2 * (float)column) / ((float)w - 1); // Normalizar
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
	printf("Dentro de la funcion, sidedistX: %f\nDentro de la funcion, sidedistY: %f\n\n", ray->sideDistX, ray->sideDistY);
}

// static void draw_pixel(mlx_image_t* img, uint32_t x, uint32_t y, uint32_t color) {
//     // Verifica que las coordenadas estén dentro de los límites de la imagen
//     if (x >= img->width || y >= img->height)
//         return;

//     // Calcula la posición del pixel en el arreglo
//     uint32_t position = y * img->width + x;

//     // El arreglo pixels está compuesto de uint8_t, pero los colores son uint32_t.
//     // Cada píxel ocupa 4 bytes (RGBA), por lo que multiplicamos la posición por 4.
//     uint32_t* pixel_ptr = (uint32_t*)&img->pixels[position * 4];

//     // Asigna el valor del color
//     *pixel_ptr = color;
// }

// static void	draw_wall_column(t_utils *utils, int column)
// {
// 	int y = utils->ray->drawStart;

// 	while (y <= utils->ray->drawEnd)
// 	{
// 		draw_pixel(utils->img, column, y, 255);
// 		y++;
// 	}
// 	return ;
// }

void	raycasting(t_utils *utils)
{
	int	column;
	int	screen_width;

    mlx_delete_image(utils->mlx, utils->img);
	column = 0;
	screen_width = IMG_WIDTH;
	while (column < screen_width)
	{
		set_ray(utils, utils->ray, column);
		printf("FUERA: utils-> DeltaDist: %f\n", utils->ray->deltaDistX);
		get_collision(utils, utils->ray);
		get_walls_height(utils->ray, utils->player);
		column++;
	}
	return ;
}