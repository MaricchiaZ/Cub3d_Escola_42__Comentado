/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:26:46 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/30 19:23:35 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(t_data *data, char **argv)
//função responsável por alocar e inicializar todas as structs que são necessárias para o funcionamento do meu programa.
{
	data->map = ft_calloc(sizeof(t_map), 1);//faço a alocação da minha struct map.
	data->mlx = ft_calloc(sizeof(t_mlx), 1);//faço a alocação da minha struct mlx.
	data->map->map = read_maps(argv);//minha variável map que é uma matriz recebe a função mapa responsável por transformar o mapa numa matriz e retorná-la.
	data->map->b_map = read_maps(argv);//salvo um backup do mapa.
	data->tex = ft_calloc(sizeof(t_tex), 1);//faço a alocação da minha struct tex.
	data->tex->north = ft_calloc(sizeof(t_img), 1);//faço a alocação da struct north dentro da minha struc tex para poder salvar as texturas de cada parece no local certo.
	data->tex->south = ft_calloc(sizeof(t_img), 1);//faço a alocação da struct south dentro da minha struc tex para poder salvar as texturas de cada parece no local certo.
	data->tex->east = ft_calloc(sizeof(t_img), 1);//faço a alocação da struct east dentro da minha struc tex para poder salvar as texturas de cada parece no local certo.
	data->tex->west = ft_calloc(sizeof(t_img), 1);//faço a alocação da struct west dentro da minha struc tex para poder salvar as texturas de cada parece no local certo.
	data->ceil = -1;//inicializo o teto com o valor de -1, porque ainda não tem nada.
	data->floor = -1;//inicializo o chão com o valor de -1, porque ainda não tem nada.
	/* `data->init_image = 0;` is initializing the `init_image` variable inside the `t_data` struct to 0.
	This variable is used to keep track of whether the game's main image has been initialized or not. */
	data->init_image = 0;//inicializo a variável init_image em zero, essa variável serve ára verificar se a imagem principal do jogo foi inicializada ou não.
	data->btn = ft_calloc(sizeof(t_btn), 1);//faço a alocação da minha struct btn(buttons).
	data->btn->move_down = NO;//inicio o botão com o valor NO(0), que é despressionado.
	data->btn->move_up = NO;//inicio o botão com o valor NO(0), que é despressionado.
	data->btn->move_left = NO;//inicio o botão com o valor NO(0), que é despressionado.
	data->btn->move_right = NO;//inicio o botão com o valor NO(0), que é despressionado.
	data->btn->rotate_left = NO;//inicio o botão com o valor NO(0), que é despressionado.
	data->btn->rotate_right = NO;//inicio o botão com o valor NO(0), que é despressionado.
	data->rc = ft_calloc(sizeof(t_ray), 1);//faço a alocação da minha struct rc(raycast).
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
