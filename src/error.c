/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:41:12 by ktaplin           #+#    #+#             */
/*   Updated: 2024/08/12 18:49:25 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error(char *str, t_game *game)
{
	printf("%s\n", str);
	if (game && game->map)
	{
		if (game->free == 1)
			freetab(game->map->map);
		if (game->free_n == 1 && game->map->path_n)
			free(game->map->path_n);
		if (game->free_s == 1 && game->map->path_s)
			free(game->map->path_s);
		if (game->free_e == 1 && game->map->path_e)
			free(game->map->path_e);
		if (game->free_w == 1 && game->map->path_w)
			free(game->map->path_w);
		free(game->map);
	}
	exit (EXIT_FAILURE);
}

void	error_check(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!(game->mlx))
	{
		puts(mlx_strerror(mlx_errno));
		error("jsp", game);
	}
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!(game->image))
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		error("jsp", game);
	}
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		error("jsp", game);
	}
}

void	*freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}
