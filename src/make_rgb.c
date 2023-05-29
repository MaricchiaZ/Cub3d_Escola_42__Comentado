/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 09:23:56 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/24 07:35:04 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	compose_rgb(char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if ((r == -1 || g == -1 || b == -1) || (r < 0 || g < 0 || b < 0) || \
	(r > 255 || g > 255 || b > 255))
	{
		printf("Error\ninvalid RGB\n");
		return (-2);
	}
	return ((r * 65536) + (g * 256) + b);
}

static int	error_sintaxe(char *str_colour)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (str_colour[i])
	{
		if (str_colour[i] == ',')
			comma++;
		if (str_colour[i] == ' ')
			return (1);
		i++;
	}
	if (comma != 2)
		return (1);
	return (0);
}

static int	check_rgb(char **rgb, char *str_color)
{
	int	i;

	if (error_sintaxe(str_color))
		return (1);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
		return (1);
	i = 0;
	while (rgb[i] && i < 3)
	{
		if (rgb[i][0] == '\n')
			return (1);
		if (ft_str_isdigit_or_nwline(rgb[i]))
			return (1);
		i++;
	}
	return (0);
}

int	make_rgb(char *str_color)
{
	char	*temp_rgb;
	char	**rgb;
	int		colour;

	colour = 0;
	temp_rgb = ft_strtrim(str_color, " ");
	rgb = ft_split(temp_rgb, ',');
	if (check_rgb(rgb, str_color))
	{
		printf("Error\ninvalid RGB\n");
		free_matrix(rgb);
		free(temp_rgb);
		return (-2);
	}
	colour = compose_rgb(rgb);
	free_matrix(rgb);
	free(temp_rgb);
	return (colour);
}

int	make_color(int color, double shade)
{
	int	r;
	int	g;
	int	b;

	r = ((color & (0xFF << 16)) >> 16) * shade;
	g = ((color & (0xFF << 8)) >> 8) * shade;
	b = (color & 0xFF) * shade;
	return (r << 16 | g << 8 | b);
}
