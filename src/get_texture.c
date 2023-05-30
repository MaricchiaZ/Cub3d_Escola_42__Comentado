/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:10:08 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/30 19:13:19 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Essa função é responsável por determinar qual textura de parede deve ser usada com base na
//  interseção do raio de visão com a parede durante a renderização do jogo. 
t_img	*init_walls(t_data *data)
{
	// Se data->rc->touch_side for igual a 0 (indicando uma colisão com uma parede vertical) e 
	// se data->rc->ray_dir.x for menor que 0 (indicando que o raio está se movendo para a esquerda)

	// Se data->rc->touch_side for igual a 1 (indicando uma colisão com uma parede horizontal) e 
	// se data->rc->ray_dir.y for maior que 0 (indicando que o raio está se movendo para cima)

	// com base nisso calculamos qual é a textura de cada parede
	if (data->rc->touch_side == 0 && data->rc->ray_dir.x < 0) 
		return (data->tex->west);
	if (data->rc->touch_side == 0 && data->rc->ray_dir.x > 0)
		return (data->tex->east);
	if (data->rc->touch_side == 1 && data->rc->ray_dir.y > 0)
		return (data->tex->south);
	if (data->rc->touch_side == 1 && data->rc->ray_dir.y < 0)
		return (data->tex->north);
	return ((t_img *) 0); // retornamos a textura certa para cada parede
}

// Aqui obtemos a textura apropriada para uma determinada posição de parede no mapa do jogo.
t_img	*get_texture(t_data *data)
{
	if (data->map->map[data->rc->pos_map.y][data->rc->pos_map.x] == '1') // no mapa, os caracteres 1 
	// representam a parede
		return (init_walls(data)); // se encontrarmos uma parede no mapa, inicializamos essa parede
		//com base na interseção do raio de visão com a parede.
	return ((t_img *) 0);
}
