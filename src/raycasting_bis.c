/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:02:28 by velbling          #+#    #+#             */
/*   Updated: 2024/05/04 15:32:51 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t    ceiling_color(t_game *game)
{
	uint32_t    color;
	
   color = (uint32_t)((game->ceiling_r << 24) \
			| (game->ceiling_g << 16) \
			| (game->ceiling_b << 8) \
			| (255 << 0));
	return (color);
}

static uint32_t    floor_color(t_game *game)
{
	uint32_t    color;
	
   color = (uint32_t)((game->floor_r << 24) \
			| (game->floor_g << 16) \
			| (game->floor_b << 8) \
			| (255 << 0));
	return (color);
}

void    ft_cast_ray_bis(t_game *game, float ws, float d_ws, int ray_pos)
{
	int	i;
	int	cl;

	i = 0;
	cl = -1;
	i = HEIGHT / 2 - d_ws / 2;
	while (++cl < i)
		mlx_put_pixel(game->image, ray_pos, cl, ceiling_color(game));
	while (i < HEIGHT / 2 + d_ws / 2)
	{
		if (game->ray->jsp)
			mlx_put_pixel(game->image, ray_pos, i,
				get_text_img(game, i, ws, game->ray->y / 64));
		else
			mlx_put_pixel(game->image, ray_pos, i,
				get_text_img(game, i, ws, game->ray->x / 64));
		i++;
	}
	while (i < HEIGHT)
	{
		mlx_put_pixel(game->image, ray_pos, i, floor_color(game));
		i++;
	}
}
