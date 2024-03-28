/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:01:33 by velbling          #+#    #+#             */
/*   Updated: 2024/03/26 15:54:53 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	ft_is_movement(mlx_t *mlx)
// {
// 	return(mlx_is_key_down(mlx, MLX_KEY_W) 
// 		|| mlx_is_key_down(mlx, MLX_KEY_S)
// 		|| mlx_is_key_down(mlx, MLX_KEY_A)
// 		|| mlx_is_key_down(mlx, MLX_KEY_D)
// 		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT)
// 		|| mlx_is_key_down(mlx, MLX_KEY_LEFT));
// }

static void	ft_movement(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player->x_pos -= 2 * -cos(game->player->angle);
		game->player->y_pos -= 2 * -sin(game->player->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player->x_pos += 2 * -cos(game->player->angle);
		game->player->y_pos += 2 * -sin(game->player->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player->x_pos -= 2 * -sin(game->player->angle);
		game->player->y_pos -= 2 * cos(game->player->angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player->x_pos += 2 * -sin(game->player->angle);
		game->player->y_pos += 2 * cos(game->player->angle);
	}
}

void	ft_hook(void* param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	ft_movement(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player->angle += M_PI / 64;
		if (game->player->angle > 2 * M_PI)
			game->player->angle -= 2 * M_PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player->angle -= M_PI / 64;
		if (game->player->angle < 0)
			game->player->angle += 2 * M_PI;
	}
	put_image(game);
}
