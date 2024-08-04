#include "../../cub3D.h"

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

static void	get_ray(t_utils *utils)
{
	float	column;
	float	w;

	column = 0;
	w = (float)IMG_WIDTH; // Se tiene que hacer en todos los pixeles de la pantalla
	while (column < w)
	{
		utils->ray->cameraX = 2 * column / w - 1; // Normalizar
		utils->ray->rayDirX = utils->player->dirX + utils->player->planeX
			* utils->ray->cameraX;
		utils->ray->rayDirY = utils->player->dirY + utils->player->planeY
			* utils->ray->cameraX;
		utils->ray->mapX = (int)utils->player->posX;
		utils->ray->mapY = (int)utils->player->posY;
		if (utils->ray->rayDirX == 0)
			utils->ray->deltaDistX = 1e30;
		else
			utils->ray->deltaDistX = fabs(1 / utils->ray->rayDirX);
		if (utils->ray->rayDirY == 0)
			utils->ray->rayDirY = 1e30;
		else
			utils->ray->deltaDistY = fabs(1 / utils->ray->rayDirY);
		step_initialisation(utils->ray, utils->player);
		column++;
	}
}

void	paint_screen(t_utils *utils)
{
	while (TRUE) // Revisar esto, no sé si hace falta aquí.
	{
		get_ray(utils);
	}
}