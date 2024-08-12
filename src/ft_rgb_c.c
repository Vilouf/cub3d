/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velbling <velbling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:48:00 by ktaplin           #+#    #+#             */
/*   Updated: 2024/08/12 18:34:09 by velbling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_color_c(char *number, int cpt, t_game *game)
{
	if (cpt == 1)
		game->ceiling_r = ft_atoi(number);
	if (cpt == 2)
		game->ceiling_g = ft_atoi(number);
	if (cpt == 3)
		game->ceiling_b = ft_atoi(number);
}

int	ceiling_utils_two(t_game *game, char *number)
{
	game->j_rgb++;
	if (game->j_rgb > 3)
	{
		free(number);
		error("Error wrong RGB value", game);
	}
	return (game->j_rgb);
}

int	ceiling_utils_three(t_game *game, int i, char *number, char *str)
{
	number[game->j_rgb] = str[i];
	i++;
	game->j_rgb = ceiling_utils_two(game, number);
	return (i);
}

char	*ceiling_utils(char *number, int cpt, t_game *game)
{
	if (cpt < 3)
	{
		free (number);
		number = malloc(sizeof (char) * 5);
		if (number == NULL)
			error("Error in malloc", game);
		number[0] = 0;
		number[1] = 0;
		number[2] = 0;
		number[3] = 0;
		number[4] = 0;
	}
	return (number);
}

int	ceiling(char *str, int i, t_game *game, int n)
{
	char	*number;
	int		cpt;

	cpt = check_fc(str, 'C', game);
	number = malloc(sizeof (char) * 5);
	ft_check_malloc(number, game);
	while (str[++i] && str[i] == ' ')
		;
	while (str[i] && str[i] != '\n')
	{	
		while (ft_isdigit(str[i]) == 0)
			i = ceiling_utils_three(game, i, number, str);
		game->j_rgb = 0;
		set_color_c(number, ++cpt, game);
		number = ceiling_utils(number, cpt, game);
		while (str[i] == ' ')
			i++;
		if (str[i] == ',')
			i++;
		while (str[i] == ' ')
			i++;
	}
	free(number);
	return (n + 1);
}
