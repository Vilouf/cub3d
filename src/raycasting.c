/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:22:10 by velbling          #+#    #+#             */
/*   Updated: 2024/07/14 18:46:36 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_text_img(t_game *game, int wHeight, float wallSize, float x)
{
	uint32_t	color;
	float		r;
	uint8_t		*pix_tab;

	r = wallSize / game->current_txt->height;
	color = 0;
	pix_tab = game->current_txt->pixels;
	wHeight -= (HEIGHT / 2 - (wallSize / 2));
	wHeight /= r;
	if (x >= game->current_txt->width)
		x = (int)floor(x) % game->current_txt->width + (floor(x) - x);
	color = color | (pix_tab[(int)((game->current_txt->width * (x - floor(x))))
			* 4 + (wHeight * game->current_txt->height * 4)] << 24);
	color = color | (pix_tab[(int)((game->current_txt->width * (x - floor(x))))
			* 4 + (wHeight * game->current_txt->height * 4) + 1] << 16);
	color = color | (pix_tab[(int)((game->current_txt->width * (x - floor(x))))
			* 4 + (wHeight * game->current_txt->height * 4) + 2] << 8);
	color = color | (pix_tab[(int)((game->current_txt->width * (x - floor(x))))
			* 4 + (wHeight * game->current_txt->height * 4) + 3]);
	return (color);
}

void	ft_cast_ray(t_game *game, float ray_length, int ray_pos)
{
	float	wall_size;
	float	d_wall_size;

	(void) game;
	if (ray_pos >= 960)
		return ;
	wall_size = 50000 / ray_length;
	if (wall_size > HEIGHT)
		d_wall_size = HEIGHT;
	else
		d_wall_size = wall_size;
	ft_cast_ray_bis(game, wall_size, d_wall_size, ray_pos);
}

float	next_point(t_game *game, float angle, char point)
{
	float	x;
	float	y;

	angle += M_PI / 480;
	x = game->player->x_pos;
	y = game->player->y_pos;
	while (game->map->map[(int)(y / 64)][(int)x / 64] != '1')
	{
		x += cos(angle) * 0.1;
		y += sin(angle) * 0.1;
	}
	if (point == 'x')
		return (x);
	return (y);
}

void	ft_gendarmes(t_game *game)
{
	if (fabs(game->ray->last_ray
			- (dist(game->player->x_pos, game->player->y_pos,
					game->ray->x, game->ray->y)
				* cos(game->player->angle - game->ray->angle))) < 50)
	{
		game->ray->jsp = fabs(game->ray->last_x - game->ray->x)
			< fabs(game->ray->last_y - game->ray->y);
	}
	else
	{
		game->ray->jsp = fabs(game->ray->x
				- next_point(game, game->ray->angle, 'x'))
			< fabs(game->ray->y - next_point(game, game->ray->angle, 'y'));
	}
}

void	save(t_game *game)
{
	game->ray->last_ray = dist(game->player->x_pos,
			game->player->y_pos, game->ray->x, game->ray->y)
		*cos(game->player->angle - game->ray->angle);
	game->ray->last_x = game->ray->x;
	game->ray->last_y = game->ray->y;
}
