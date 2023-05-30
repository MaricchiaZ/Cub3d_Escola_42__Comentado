/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:34:48 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/30 18:29:31 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Esta função é responsável por marcar as flags dos botões como pressionadas
int	press_keys(int key_code, t_data *data)
{
	if (key_code == W) // se precionarmos a tecla W
		data->btn->move_up = YES; // a variável referente a andar pra frente recebe o valor 1 (YES)
	if (key_code == A) // ... assim vai
		data->btn->move_left = YES;
	if (key_code == S)
		data->btn->move_down = YES;
	if (key_code == D)
		data->btn->move_right = YES;
	if (key_code == ARROW_LEFT)
		data->btn->rotate_left = YES;
	if (key_code == ARROW_RIGHT)
		data->btn->rotate_right = YES;
	if (key_code == ESC) // se a tecla ESC é precionada
		kill_game(data); // liberamos a memória e saímos do game
	return (0);
}

// Esta função é responsável por marcar as flags dos botões como despressionadas. 
// Assim a variável da tecla é atualizada para indicar que o movimento não está mais sendo solicitado.
int	depress_keys(int key_code, t_data *data)
{
	if (key_code == W) // se a tecla W, referente a andar pra frente é solta
		data->btn->move_up = NO; // a variável referente a ela recebe o valor 0 (NO)
	if (key_code == A) // e assim vai..
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


// Estas duas funções permitem que o jogo responda adequadamente aos eventos do teclado e 
// ajuste o comportamento do personagem de acordo com as teclas pressionadas e liberadas.