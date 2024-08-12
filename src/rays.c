/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:56:59 by velbling          #+#    #+#             */
/*   Updated: 2024/08/12 18:01:24 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	choose_texture(t_game *game, float angle)
{
	if (!game->ray->jsp)
	{
		if (angle > 0 && angle < M_PI)
			game->current_txt = game->s_txt;
		else
			game->current_txt = game->n_txt;
	}
	else
	{
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			game->current_txt = game->w_txt;
		else
			game->current_txt = game->e_txt;
	}
	return (1);
}

static int	verif_ray(t_game *game)
{
	return (game->map->map[(int)((game->ray->y / 64) + 0.001)] \
							[(int)((game->ray->x / 64) + 0.001)] != '1' \
				&& game->map->map[(int)((game->ray->y / 64) - 0.001)] \
							[(int)((game->ray->x / 64) - 0.001)] != '1' \
				&& game->map->map[(int)((game->ray->y / 64) - 0.001)] \
							[(int)((game->ray->x / 64) + 0.001)] != '1' \
				&& game->map->map[(int)((game->ray->y / 64) + 0.001)] \
							[(int)((game->ray->x / 64) - 0.001)] != '1');
}

static void	ray_processing(t_game *game, int invisible_ray, int *ray_pos)
{
	int	k;

	k = 0;
	game->ray->length = dist(game->player->x_pos, game->player->y_pos, \
									game->ray->x, game->ray->y);
	game->ray->length *= cos(game->player->angle - game->ray->angle);
	if (invisible_ray == 1)
	{
		ft_gendarmes(game);
		game->wall_color = choose_texture(game, game->ray->angle);
		while (k < 8 && invisible_ray)
			ft_cast_ray(game, game->ray->length, *ray_pos + (k++));
		*ray_pos += k;
	}
	save(game);
	game->ray->angle += M_PI / 360;
}

static void	put_image_bis(t_game *game)
{
	game->ray->x = game->player->x_pos;
	game->ray->y = game->player->y_pos;
	if (game->ray->angle < 0)
		game->ray->angle += 2 * M_PI;
	if (game->ray->angle > 2 * M_PI)
		game->ray->angle -= 2 * M_PI;
}

void	put_image(void *param)
{
	t_game	*game;
	int		invisible_ray;
	int		ray_pos;

	game = param;
	mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->ray->angle = game->player->angle - 30 * (M_PI / 180) - (M_PI / 180);
	game->ray->length = 0;
	invisible_ray = 0;
	ray_pos = 0;
	while (ray_pos < WIDTH)
	{
		put_image_bis(game);
		while (verif_ray(game))
		{
			game->ray->x += cos(game->ray->angle) * 0.1;
			game->ray->y += sin(game->ray->angle) * 0.1;
		}
		ray_processing(game, invisible_ray, &ray_pos);
		invisible_ray = 1;
	}
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}
