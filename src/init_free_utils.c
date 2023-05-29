/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:26:58 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/23 19:35:19 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_img(t_img *img, t_data *data)
{
	if (img->name != NULL)
		free(img->name);
	if (img->img_ptr)
		mlx_destroy_image(data->mlx->mlx, img->img_ptr);
	if (img)
		free(img);
}

void	free_tex(t_data *data)
{
	if (data->tex->north)
		free_img(data->tex->north, data);
	if (data->tex->south)
		free_img(data->tex->south, data);
	if (data->tex->east)
		free_img(data->tex->east, data);
	if (data->tex->west)
		free_img(data->tex->west, data);
	free(data->tex);
}

void	error_more_one_player(t_data *data)
{
	printf("Error\nMore than one player in the map.\n");
	free_game(data);
}

void	error_no_player(t_data *data)
{
	printf("Error\nThere's no player in the map.\n");
	free_game(data);
}
