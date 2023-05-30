/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params_respawn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:30:52 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/30 19:00:57 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Nessa função as direções X e Y recebem os valores adequados, para futuramente orientarmos os
// raios de visão e montarmos o cenário de acordo para onde o personagem olha
static void	get_direction(t_data *data) 
{
	if (data->respawn == 'N') // se o player nasce olhando para o NORTE
	{
		data->direction.x = 0; // X vale 0
		data->direction.y = -1; // Y vale -1
	}
	else if (data->respawn == 'S') // se o player nasce olhando para o SUL
	{
		data->direction.x = 0; // X vale 0
		data->direction.y = 1; // Y vale -1
	}
	else if (data->respawn == 'E') // se o player nasce olhando para o LESTE
	{
		data->direction.x = 1; // X vale 1
		data->direction.y = 0; // Y vale 0
	}
	else if (data->respawn == 'W')  // se o player nasce olhando para o OESTE
	{
		data->direction.x = -1; // X vale -1
		data->direction.y = 0; // Y vale 0
	}
}


/*
O valor de 0.66 é usado porque representa uma relação de aspecto de 16:9 com um campo de visão horizontal de aproximadamente 90 graus. É um valor comummente usado em jogos de primeira pessoa para criar uma perspectiva mais imersiva.

E SE FOSSE UM JOGO de resolução 4:3.....
Para um jogo 4:3, o valor da .plane seria de 0.75 e -0.2 para manter a proporção correta entre altura e largura da tela. Esses valores podem variar dependendo do tamanho da tela e da resolução do jogo.
*/

// Esta função é responsável por definir o vetor de plano (data->plane) com base na direção de 
// respawn (data->respawn) do player.
static void	get_plane(t_data *data)
{
	if (data->respawn == 'N')  // se o player nasce olhando para o NORTE
	{
		// ajustamos o plano de visão para se parecer com a visão humana
		data->plane.x = 0.66; // o 0.66 garante que a largura do plano de projeção tenha 
		// um valor adequado para uma visualização agradável.
		data->plane.y = 0; // 0  garante que o vetor do plano seja perpendicular ao vetor de direção do jogador,
		// que as paredes estejam verticais e não inclinadas
	}
	else if (data->respawn == 'S') // e assim vai...
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

// Aqui salvamos os parâmetros referentes ao lado que o player nasce olhando
void	get_params_respawn_player(t_data *data)
{
	get_direction(data); // pegamos a direção que o player está olhando
	get_plane(data); /// montamos o plano de visão
	data->wall_height = 8; // definimos que a altura da parede será 8
	data->wall_width = 8; // e que a largura será 8
	data->step = 0; // a distância para a construção da parede inicia-se zerada
}
