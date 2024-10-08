/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:41:12 by ktaplin           #+#    #+#             */
/*   Updated: 2024/08/13 21:59:18 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strcpy(char *src, char *dest, int i)
{
	int	j;

	j = 0;
	while (src[i])
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j - 1] = '\0';
	return (dest);
}

char	*ft_strdup(char *s1)
{
	char	*dup;
	int		i;

	i = ft_strlen(s1);
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

float	dist(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ft_check_malloc(char *number, t_game *game)
{
	if (number == NULL)
		error("Error in malloc", game);
	number[0] = 0;
	number[1] = 0;
	number[2] = 0;
	number[3] = 0;
	number[4] = 0;
}

void	free_utils(t_game *game)
{
	free(game->map->path_n);
	free(game->map->path_s);
	free(game->map->path_e);
	free(game->map->path_w);
	mlx_delete_image(game->mlx, game->image);
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
	mlx_close_window(game->mlx);
	free(game);
}
