/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:26:46 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/24 12:51:48 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(t_data *data, char **argv)
{
	data->map = ft_calloc(sizeof(t_map), 1);
	data->mlx = ft_calloc(sizeof(t_mlx), 1);
	data->map->map = read_maps(argv);
	data->map->b_map = read_maps(argv);
	data->tex = ft_calloc(sizeof(t_tex), 1);
	data->tex->north = ft_calloc(sizeof(t_img), 1);
	data->tex->south = ft_calloc(sizeof(t_img), 1);
	data->tex->east = ft_calloc(sizeof(t_img), 1);
	data->tex->west = ft_calloc(sizeof(t_img), 1);
	data->ceil = -1;
	data->floor = -1;
	data->init_image = 0;
	data->btn = ft_calloc(sizeof(t_btn), 1);
	data->btn->move_down = NO;
	data->btn->move_up = NO;
	data->btn->move_left = NO;
	data->btn->move_right = NO;
	data->btn->rotate_left = NO;
	data->btn->rotate_right = NO;
	data->rc = ft_calloc(sizeof(t_ray), 1);
}

void	init_images(t_data *data)
{
	data->paint_img.img_ptr = mlx_new_image(data->mlx->mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT);
	data->paint_img.addr = mlx_get_data_addr(data->paint_img.img_ptr, \
	&data->paint_img.bpp, &data->paint_img.size_line, &data->paint_img.endian);
	data->init_image = 1;
}

void	kill_window(t_data *data)
{
	mlx_clear_window(data->mlx->mlx, data->mlx->window);
	mlx_loop_end(data->mlx->mlx);
	mlx_destroy_window(data->mlx->mlx, data->mlx->window);
	mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
}

void	free_game(t_data *data)
{
	if (data->map->map)
		free_matrix(data->map->map);
	if (data->map->b_map)
		free_matrix(data->map->b_map);
	if (data->map != NULL)
		free(data->map);
	free_tex(data);
	if (data->btn)
		free(data->btn);
	if (data->init_image)
		mlx_destroy_image(data->mlx->mlx, data->paint_img.img_ptr);
	if (data->mlx->mlx != NULL && data->mlx->window != NULL)
		kill_window(data);
	free(data->mlx);
	free(data->rc);
	exit(0);
}

int	kill_game(t_data *data)
{
	free_game(data);
	return (1);
}
