/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:34:48 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/24 12:53:46 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_keys(int key_code, t_data *data)
{
	if (key_code == W)
		data->btn->move_up = YES;
	if (key_code == A)
		data->btn->move_left = YES;
	if (key_code == S)
		data->btn->move_down = YES;
	if (key_code == D)
		data->btn->move_right = YES;
	if (key_code == ARROW_LEFT)
		data->btn->rotate_left = YES;
	if (key_code == ARROW_RIGHT)
		data->btn->rotate_right = YES;
	if (key_code == ESC)
		kill_game(data);
	return (0);
}

int	depress_keys(int key_code, t_data *data)
{
	if (key_code == W)
		data->btn->move_up = NO;
	if (key_code == A)
		data->btn->move_left = NO;
	if (key_code == S)
		data->btn->move_down = NO;
	if (key_code == D)
		data->btn->move_right = NO;
	if (key_code == ARROW_LEFT)
		data->btn->rotate_left = NO;
	if (key_code == ARROW_RIGHT)
		data->btn->rotate_right = NO;
	return (0);
}
