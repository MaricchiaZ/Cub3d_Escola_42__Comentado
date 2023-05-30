/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:47:07 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/30 19:56:59 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Aqui realizamos a rotação do jogador no jogo. Nós utilizamos os valores de direção (data->direction)
//  e plano (data->plane) para realizar as transformações de rotação.
void	player_rotate(t_data *data)
{
	data->old_dir_x = data->direction.x; // armazenamos os valores atuais em variáves temporárias
	data->old_plane_x = data->plane.x;  // armazenamos os valores atuais em variáves temporárias
	if (data->btn->rotate_right == 1) // se o player rotacionar para a direita
	{
		// calculamos a nova direção de visão
		// A rotação é realizada através de cálculos trigonométricos que atualizam os 
		// vetores de direção e plano do jogador.
		data->direction.x = data->direction.x * cos(ROTATE_SPEED) - \
		data->direction.y * sin(ROTATE_SPEED);
		data->direction.y = data->old_dir_x * sin(ROTATE_SPEED) + \
		data->direction.y * cos(ROTATE_SPEED);
		data->plane.x = data->plane.x * cos(ROTATE_SPEED) - \
		data->plane.y * sin(ROTATE_SPEED);
		data->plane.y = data->old_plane_x * sin(ROTATE_SPEED) + \
		data->plane.y * cos(ROTATE_SPEED);
	}
	if (data->btn->rotate_left == 1) // se o player rotacionar para a esquerda
	{
		// calculamos a nova direção de visão
		// A rotação é realizada através de cálculos trigonométricos que atualizam os 
		// vetores de direção e plano do jogador.
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

// Essa função atualiza a posição do jogador no jogo. Ela recebe as novas coordenadas da 
// posição como parâmetro e atribui esses valores às variáveis data->player.x e data->player.y.
static void	update_pos(t_data *data, double newpos[2])
{
	data->player.x = newpos[X];
	data->player.y = newpos[Y];
}


// É nessa função que atualizamos a posição do jogador no jogo quando ele se movimenta. Aqui
// verificamos os botões de movimento foram pressionados pelo jogador e calculamos as novas 
// coordenadas de acordo com a direção em que o jogador está olhando e a velocidade de movimento definida.
void	player_walking(t_data *data)
{
	double	new[2];

	new[X] = 0;
	new[Y] = 0;
	if (data->btn->move_up == YES) // se andarmos para frente...
	{
		new[X] = ((new[Y] = data->player.y + (MOVE_SPEED * data->direction.y),
					data->player.x + (MOVE_SPEED * data->direction.x)));
		if (data->map->map[(int)(data->player.y + \
		data->direction.y * 0.2)][(int)new[X]] == '1') // Verifica se a nova posição calculada 
		// colide com uma parede no mapa do jogo. Isso é feito verificando se o caractere na posição 
		// correspondente no mapa é igual a '1'. Se for, a função retorna imediatamente para evitar a 
		// atualização da posição.
			return ;
	}
	else if (data->btn->move_down == YES) // se andarmos para trás
		new[X] = ((new[Y] = data->player.y - (MOVE_SPEED * data->direction.y),
					data->player.x - (MOVE_SPEED * data->direction.x)));
	else if (data->btn->move_left == YES) // se andarmos para a esquerda
		new[X] = ((new[Y] = data->player.y - (MOVE_SPEED * data->direction.x),
					data->player.x + (MOVE_SPEED * data->direction.y)));
	else if (data->btn->move_right == YES) // se andarmos para direita
		new[X] = ((new[Y] = data->player.y + (MOVE_SPEED * data->direction.x),
					data->player.x - (MOVE_SPEED * data->direction.y)));
	if (data->map->map[(int)new[Y]][(int)new[X]] == '1') // Verifica se a nova posição calculada 
		// colide com uma parede no mapa do jogo. Isso é feito verificando se o caractere na posição 
		// correspondente no mapa é igual a '1'. Se for, a função retorna imediatamente para evitar a 
		// atualização da posição.
		return ;
	update_pos(data, new); // se o movimento for válido, de fato movemos o player.
	return ;
}
