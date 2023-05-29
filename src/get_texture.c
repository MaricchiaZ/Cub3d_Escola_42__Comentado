/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:10:08 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/19 09:37:36 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*init_walls(t_data *data)
{
	if (data->rc->touch_side == 0 && data->rc->ray_dir.x < 0)
		return (data->tex->west);
	if (data->rc->touch_side == 0 && data->rc->ray_dir.x > 0)
		return (data->tex->east);
	if (data->rc->touch_side == 1 && data->rc->ray_dir.y > 0)
		return (data->tex->south);
	if (data->rc->touch_side == 1 && data->rc->ray_dir.y < 0)
		return (data->tex->north);
	return ((t_img *) 0);
}

t_img	*get_texture(t_data *data)
{
	if (data->map->map[data->rc->pos_map.y][data->rc->pos_map.x] == '1')
		return (init_walls(data));
	return ((t_img *) 0);
}
