/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:42:27 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/19 19:59:16 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *data, t_vector point, int color)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->size_line + \
	((int)point.x) * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	put_texture(t_img *data, t_vector point)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->size_line + \
	((int)point.x) * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	set_img_background(t_data *data)
{
	int	height;
	int	width;

	height = 0;
	while (height < SCREEN_HEIGHT)
	{
		width = 0;
		while (width < SCREEN_WIDTH)
		{
			if (height < SCREEN_HEIGHT / 2)
				put_pixel(&data->paint_img, (t_vector){.x = width, \
				.y = height}, data->ceil);
			else
				put_pixel(&data->paint_img, (t_vector){.x = width, \
				.y = height}, data->floor);
			width++;
		}
		height++;
	}
}
