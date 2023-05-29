/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:44:53 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/19 20:12:29 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_distance_near_square(t_data *data)
{
	if (data->rc->ray_dir.x < 0)
	{
		data->rc->dist_wall_x = -1;
		data->rc->side_dist_x = (data->player.x - data->rc->pos_map.x) * \
		data->rc->delta_dist_x;
	}
	else
	{
		data->rc->dist_wall_x = 1;
		data->rc->side_dist_x = (data->rc->pos_map.x + 1 - data->player.x) * \
		data->rc->delta_dist_x;
	}
	if (data->rc->ray_dir.y < 0)
	{
		data->rc->dist_wall_y = -1;
		data->rc->side_dist_y = (data->player.y - data->rc->pos_map.y) * \
		data->rc->delta_dist_y;
	}
	else
	{
		data->rc->dist_wall_y = 1;
		data->rc->side_dist_y = (data->rc->pos_map.y + 1 - data->player.y) * \
		data->rc->delta_dist_y;
	}
}

static void	get_distance_next_square(t_data *data)
{
	if (data->rc->ray_dir.x == 0)
		data->rc->delta_dist_x = 10000000;
	else
		data->rc->delta_dist_x = fabs(1 / data->rc->ray_dir.x);
	if (data->rc->ray_dir.y == 0)
		data->rc->delta_dist_y = 10000000;
	else
		data->rc->delta_dist_y = fabs(1 / data->rc->ray_dir.y);
}

static void	algorithm_dda(t_data *data)
{
	data->rc->touch_side = 0;
	while (data->map->map[data->rc->pos_map.y][data->rc->pos_map.x] == '0')
	{
		if (data->rc->side_dist_x < data->rc->side_dist_y)
		{
			data->rc->side_dist_x += data->rc->delta_dist_x;
			data->rc->pos_map.x += data->rc->dist_wall_x;
			data->rc->touch_side = 0;
		}
		else
		{
			data->rc->side_dist_y += data->rc->delta_dist_y;
			data->rc->pos_map.y += data->rc->dist_wall_y;
			data->rc->touch_side = 1;
		}
	}
}

static void	render_wall(t_data *data)
{
	data->rc->line_height = fabs(SCREEN_HEIGHT / \
	data->rc->perpendicular_wall_dist);
	data->rc->init_draw = -data->rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->rc->init_draw < 0)
		data->rc->init_draw = 0;
	data->rc->finish_draw = data->rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->rc->finish_draw >= SCREEN_HEIGHT)
		data->rc->finish_draw = SCREEN_HEIGHT - 1;
	render_with_texture(data);
}

void	do_rayscast(t_data *data)
{
	data->rc->ray = 0;
	while (data->rc->ray < SCREEN_WIDTH)
	{
		data->rc->cam_plane_x = 2 * data->rc->ray / (double)SCREEN_WIDTH - 1;
		data->rc->camera_px = data->plane;
		vector_scale(&data->rc->camera_px, data->rc->cam_plane_x);
		data->rc->ray_dir = data->direction;
		vector_sum(&data->rc->ray_dir, &data->rc->camera_px);
		get_distance_next_square(data);
		data->rc->pos_map = (t_coord){.y = (int)data->player.y, \
		.x = (int)data->player.x};
		get_distance_near_square(data);
		algorithm_dda(data);
		if (data->rc->touch_side == 0)
			data->rc->perpendicular_wall_dist = (fabs(data->rc->pos_map.x - \
			data->player.x + ((1 - data->rc->dist_wall_x) / 2)) / \
			data->rc->ray_dir.x);
		else
			data->rc->perpendicular_wall_dist = (fabs(data->rc->pos_map.y - \
			data->player.y + ((1 - data->rc->dist_wall_y) / 2)) / \
			data->rc->ray_dir.y);
		render_wall(data);
		data->rc->ray++;
	}
}
