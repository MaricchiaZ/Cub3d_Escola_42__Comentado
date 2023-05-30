/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:11:38 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/30 19:17:15 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Essa função é a ALMA do jogo. Ela que coordena os eventos de fazer aparecer as imagens na tela.
int	make_image(t_data *data)
{
	set_img_background(data); // definimos as cores de fundo (teto e chão)
	player_walking(data); // atualizamos a posição do jogador, se ele andar
	player_rotate(data); // atualizamos a posição do jogador, virar para os lados
	do_rayscast(data); // realizamos o processo de lançamento de raios e renderização das paredes
	// do jogo. Essa função é responsável por calcular os raios de visão do jogador e renderizar 
	// as paredes correspondentes com as texturas apropriadas.
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->window, \
	data->paint_img.img_ptr, 0, 0); // A função utiliza a função mlx_put_image_to_window para exibir a 
	// imagem renderizada na janela do jogo. Ela recebe como argumentos o ponteiro para a estrutura 
	// mlx contendo as informações do ambiente gráfico, o ponteiro para a janela onde a imagem será exibida.
	return (0);
}
