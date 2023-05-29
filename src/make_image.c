/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:11:38 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/19 09:46:43 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	make_image(t_data *data)
{
	set_img_background(data);
	player_walking(data);
	player_rotate(data);
	do_rayscast(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->window, \
	data->paint_img.img_ptr, 0, 0);
	return (0);
}
