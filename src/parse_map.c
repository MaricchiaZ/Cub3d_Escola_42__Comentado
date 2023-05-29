/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:37:27 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/24 13:35:13 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	char_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	just_one_player(t_data *data)
{
	int	i;
	int	nb_players;
	int	j;

	nb_players = 0;
	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (char_in_set(data->map->map[i][j], "NSEW"))
			{
				nb_players++;
				data->player.y = (float) i + 0.5;
				data->player.x = (float) j + 0.5;
			}
			if (nb_players > 1)
				error_more_one_player(data);
			j++;
		}
		i++;
	}
	if (nb_players == 0)
		error_no_player(data);
}

static void	char_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (!ft_strchr("10NSEW ", data->map->map[i][j]))
			{
				printf("Error\nInvalid character in map.\n");
				kill_game(data);
			}
			if (data->map->map[i][j] == ' ')
				data->map->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

static int	flood_fill_wall(t_map *map, int px, int py)
{
	if (px < 0 || py < 0 || !map->b_map || !map->b_map[px])
		return (0);
	if ((!map->b_map || !map->b_map[px][py]) || map->b_map[px][py] == ' ')
		return (0);
	if (!char_in_set(map->b_map[px][py], "1X "))
	{	
		map->b_map[px][py] = 'X';
		if (!flood_fill_wall(map, px + 1, py))
			return (0);
		if (!flood_fill_wall(map, px - 1, py))
			return (0);
		if (!flood_fill_wall(map, px, py + 1))
			return (0);
		if (!flood_fill_wall(map, px, py - 1))
			return (0);
		if (!flood_fill_wall(map, px + 1, py + 1))
			return (0);
		if (!flood_fill_wall(map, px + 1, py - 1))
			return (0);
		if (!flood_fill_wall(map, px - 1, py - 1))
			return (0);
		if (!flood_fill_wall(map, px - 1, py + 1))
			return (0);
	}
	return (1);
}

void	parse_map(t_data *data)
{
	int	result;

	if (!data->map->map || !data->map->map)
	{
		printf("Error\nInvalid Map.\n");
		kill_game(data);
	}
	char_map(data);
	just_one_player(data);
	data->respawn = data->map->map[(int)data->player.y][(int)data->player.x];
	data->map->map[(int)data->player.y][(int)data->player.x] = '0';
	result = flood_fill_wall(data->map, data->player.y, data->player.x);
	if (result == 0)
	{
		printf("Error\nInvalid Map.\n");
		kill_game(data);
	}
}
