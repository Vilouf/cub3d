/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:01:36 by velbling          #+#    #+#             */
/*   Updated: 2024/08/13 21:09:57 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_utils_bis(t_game *game)
{
	free(game->map->path_n);
	free(game->map->path_s);
	free(game->map->path_e);
	free(game->map->path_w);
	if (game->w_txt)
		mlx_delete_texture(game->w_txt);
	if (game->n_txt)
		mlx_delete_texture(game->n_txt);
	if (game->e_txt)
		mlx_delete_texture(game->e_txt);
	if (game->s_txt)
		mlx_delete_texture(game->s_txt);
	freetab(game->map->map);
	free(game->ray);
	free(game->map);
	free(game->player);
	free(game);
}

void	open_error(t_game *game, char *path, char *str, char *msg)
{
	free(str);
	free(path);
	error(msg, game);
}
