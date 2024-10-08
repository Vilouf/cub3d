/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:41:12 by ktaplin           #+#    #+#             */
/*   Updated: 2024/08/13 21:09:16 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	north(char *str, int i, int n, t_game *game)
{
	char	*path;
	int		j;

	j = 0;
	if (str[i + 1] != 'O')
		error("Error wrong character", game);
	while (str[j])
		j++;
	i += 2;
	while (str[i] == ' ')
		i++;
	path = malloc(sizeof (char) * (j - i));
	path = ft_strcpy(str, path, i);
	if (open(path, O_RDONLY) != -1)
	{
		game->map->path_n = ft_strdup(path);
		game->free_n = 1;
		free (path);
	}
	else
	{
		open_error(game, path, str, "Error north path");
	}
	return (n + 1);
}

int	south(char *str, int i, int n, t_game *game)
{
	char	*path;
	int		j;

	j = 0;
	if (str[i + 1] != 'O')
		error("Error wrong character", game);
	while (str[j])
		j++;
	i += 2;
	while (str[i] == ' ')
		i++;
	path = malloc(sizeof (char) * (j - i));
	path = ft_strcpy(str, path, i);
	if (open(path, O_RDONLY) != -1)
	{
		game->map->path_s = ft_strdup(path);
		game->free_s = 1;
		free (path);
	}
	else
	{
		open_error(game, path, str, "Error south path");
	}
	return (n + 1);
}

int	east(char *str, int i, int n, t_game *game)
{
	char	*path;
	int		j;

	j = 0;
	if (str[i + 1] != 'A')
		error("Error wrong character", game);
	while (str[j])
		j++;
	i += 2;
	while (str[i] == ' ')
		i++;
	path = malloc(sizeof (char) * (j - i));
	path = ft_strcpy(str, path, i);
	if (open(path, O_RDONLY) != -1)
	{
		game->map->path_e = ft_strdup(path);
		game->free_e = 1;
		free (path);
	}
	else
	{
		open_error(game, path, str, "Error east path");
	}
	return (n + 1);
}

int	west(char *str, int i, int n, t_game *game)
{
	char	*path;
	int		j;

	j = 0;
	if (str[i + 1] != 'E')
		error("Error wrong character", game);
	while (str[j])
		j++;
	i += 2;
	while (str[i] == ' ')
		i++;
	path = malloc(sizeof (char) * (j - i));
	path = ft_strcpy(str, path, i);
	if (open(path, O_RDONLY) != -1)
	{
		game->map->path_w = ft_strdup(path);
		game->free_w = 1;
		free (path);
	}
	else
	{
		open_error(game, path, str, "Error east path");
	}
	return (n + 1);
}
