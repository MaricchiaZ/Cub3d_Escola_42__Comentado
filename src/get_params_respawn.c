/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params_respawn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:30:52 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/22 09:48:20 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_direction(t_data *data)
{
	if (data->respawn == 'N')
	{
		data->direction.x = 0;
		data->direction.y = -1;
	}
	else if (data->respawn == 'S')
	{
		data->direction.x = 0;
		data->direction.y = 1;
	}
	else if (data->respawn == 'E')
	{
		data->direction.x = 1;
		data->direction.y = 0;
	}
	else if (data->respawn == 'W')
	{
		data->direction.x = -1;
		data->direction.y = 0;
	}
}

static void	get_plane(t_data *data)
{
	if (data->respawn == 'N')
	{
		data->plane.x = 0.66;
		data->plane.y = 0;
	}
	else if (data->respawn == 'S')
	{
		data->plane.x = -0.66;
		data->plane.y = 0;
	}
	else if (data->respawn == 'E')
	{
		data->plane.x = 0;
		data->plane.y = 0.66;
	}
	else if (data->respawn == 'W')
	{
		data->plane.x = 0;
		data->plane.y = -0.66;
	}
}

void	get_params_respawn_player(t_data *data)
{
	get_direction(data);
	get_plane(data);
	data->wall_height = 8;
	data->wall_width = 8;
	data->step = 0;
}
