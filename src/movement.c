/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:47:07 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/19 20:49:39 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_rotate(t_data *data)
{
	data->old_dir_x = data->direction.x;
	data->old_plane_x = data->plane.x;
	if (data->btn->rotate_right == 1)
	{
		data->direction.x = data->direction.x * cos(ROTATE_SPEED) - \
		data->direction.y * sin(ROTATE_SPEED);
		data->direction.y = data->old_dir_x * sin(ROTATE_SPEED) + \
		data->direction.y * cos(ROTATE_SPEED);
		data->plane.x = data->plane.x * cos(ROTATE_SPEED) - \
		data->plane.y * sin(ROTATE_SPEED);
		data->plane.y = data->old_plane_x * sin(ROTATE_SPEED) + \
		data->plane.y * cos(ROTATE_SPEED);
	}
	if (data->btn->rotate_left == 1)
	{
		data->direction.x = data->direction.x * cos(-ROTATE_SPEED) - \
		data->direction.y * sin(-ROTATE_SPEED);
		data->direction.y = data->old_dir_x * sin(-ROTATE_SPEED) + \
		data->direction.y * cos(-ROTATE_SPEED);
		data->plane.x = data->plane.x * cos(-ROTATE_SPEED) - \
		data->plane.y * sin(-ROTATE_SPEED);
		data->plane.y = data->old_plane_x * sin(-ROTATE_SPEED) + \
		data->plane.y * cos(-ROTATE_SPEED);
	}
}

static void	update_pos(t_data *data, double newpos[2])
{
	data->player.x = newpos[X];
	data->player.y = newpos[Y];
}

void	player_walking(t_data *data)
{
	double	new[2];

	new[X] = 0;
	new[Y] = 0;
	if (data->btn->move_up == YES)
	{
		new[X] = ((new[Y] = data->player.y + (MOVE_SPEED * data->direction.y),
					data->player.x + (MOVE_SPEED * data->direction.x)));
		if (data->map->map[(int)(data->player.y + \
		data->direction.y * 0.2)][(int)new[X]] == '1')
			return ;
	}
	else if (data->btn->move_down == YES)
		new[X] = ((new[Y] = data->player.y - (MOVE_SPEED * data->direction.y),
					data->player.x - (MOVE_SPEED * data->direction.x)));
	else if (data->btn->move_left == YES)
		new[X] = ((new[Y] = data->player.y - (MOVE_SPEED * data->direction.x),
					data->player.x + (MOVE_SPEED * data->direction.y)));
	else if (data->btn->move_right == YES)
		new[X] = ((new[Y] = data->player.y + (MOVE_SPEED * data->direction.x),
					data->player.x - (MOVE_SPEED * data->direction.y)));
	if (data->map->map[(int)new[Y]][(int)new[X]] == '1')
		return ;
	update_pos(data, new);
	return ;
}
