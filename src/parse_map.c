/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:37:27 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/31 19:33:12 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Aqui verificamos se um caractere específico está presente em um conjunto de caracteres. 
static int	char_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i]) // percorre o set
	{
		if (set[i] == c) // se encontrar o caractere c
			return (1); // retornamos 1
		i++;
	}
	return (0); // se percorrermos tudo e não encontrarmos os caracteres da string set, retornamos 0
}

// Essa função tem como objetivo verificar se há apenas um jogador (caractere 'N', 'S', 'E' ou 'W')
// no mapa do jogo.
static void	just_one_player(t_data *data)
{
	int	i;
	int	nb_players;
	int	j;

	nb_players = 0;
	i = 0;
	while (data->map->map[i]) // percorre todas as strings que compoe o mapa
	{
		j = 0;
		while (data->map->map[i][j]) // percorre todas os caracteres das strings do mapa
		{
			if (char_in_set(data->map->map[i][j], "NSEW")) // verifica se o caractere atual é um
			// jogador válido ('N', 'S', 'E' ou 'W')
			{
				nb_players++;
				data->player.y = (float) i + 0.5; // salvamos a posição do player e somamos 0.5 para o 
				// player se posicionar no meio do caractere em que ele se encontra
				data->player.x = (float) j + 0.5; // salvamos a posição do player e somamos 0.5 para o 
				// player se posicionar no meio do caractere em que ele se encontra
			}
			if (nb_players > 1) // se tiver mais de um jogador no jogo
				error_more_one_player(data); // avisamos que tem um erro de jogadores em excesso
				// e que nao dá para jogar
			j++;
		}
		i++;
	}
	if (nb_players == 0) // se não existem jogadores
		error_no_player(data); // avisamos que tem um erro e que nao dá para jogar, pois não tem
		// player
}

//  Essa função verifica os caracteres válidos no mapa do jogo e realizar algumas substituições. 
static void	char_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->map[i]) // percorremos todas as strings que compõe o mapa
	{
		j = 0;
		while (data->map->map[i][j]) // percorre todas os caracteres das strings do mapa
		{
			if (!ft_strchr("10NSEW ", data->map->map[i][j])) // verifica se o caractere atual
			//  não pertence ao conjunto de caracteres válidos ("10NSEW "). 
			{
				printf("Error\nInvalid character in map.\n"); // avisamos o erro
				kill_game(data); // liberamos a memória e saímos do jogo
			}
			if (data->map->map[i][j] == ' ') // se encontrarmos um espaço
				data->map->map[i][j] = '1'; // trocamos por 1 (isso evita muitos segmentation fault)
			j++;
		}
		i++;
	}
}

// A função flood_fill_wall implementa o algoritmo de preenchimento por inundação (flood fill) 
// para identificar e marcar áreas de parede em um mapa. 
static int	flood_fill_wall(t_map *map, int px, int py)
{
	if (px < 0 || py < 0 || !map->b_map || !map->b_map[px]) // ESSAS SÃO AS CONDIÇOES DE PARADA
	// se formos em uma posição negativa do mapa, ou se o mapa não existir
		return (0);
	if ((!map->b_map || !map->b_map[px][py]) || map->b_map[px][py] == ' ') // se o mapa não existir
	// ou encontrarmos um espaço
		return (0);
	if (!char_in_set(map->b_map[px][py], "1X ")) // se for 1 ou X
	{	
		map->b_map[px][py] = 'X'; // preenchemos a posição que estamos com X
		if (!flood_fill_wall(map, px + 1, py)) // vamos recursivamente para a casa do lado px+1
			return (0);
		if (!flood_fill_wall(map, px - 1, py)) // vamos recursivamente para a casa do lado px-1
			return (0);
		if (!flood_fill_wall(map, px, py + 1)) // vamos recursivamente para a casa do lado py+1
			return (0);
		if (!flood_fill_wall(map, px, py - 1)) // vamos recursivamente para a casa do lado py-1
			return (0);
		if (!flood_fill_wall(map, px + 1, py + 1)) // vamos na diagonal px + 1 py + 1
			return (0);
		if (!flood_fill_wall(map, px + 1, py - 1)) // vamos na diagonal px + 1 py - 1
			return (0);
		if (!flood_fill_wall(map, px - 1, py - 1)) // vamos na diagonal px - 1 py - 1
			return (0);
		if (!flood_fill_wall(map, px - 1, py + 1)) // vamos na diagonal px - 1 py + 1
			return (0);
	}
	return (1); // se preencher o mapa todo, encontramos um mapa válido e retornamos 1
}

// Essa função analisa e vê se o mapa está adequado para o ser jogado
void	parse_map(t_data *data)
{
	int	result;

	if (!data->map->map || !data->map->bmap) //se não tiver map ou bmap
	{
		printf("Error\nInvalid Map.\n"); // avisamos que o mapa está inválido
		kill_game(data); // limpamos a memória e saímos do jogo
	}
	char_map(data); // conferimos os caracteres que compõem o mapa
	just_one_player(data); // conferimos se só tem um mapa
	data->respawn = data->map->map[(int)data->player.y][(int)data->player.x]; // salvamos o respaw do jogador
	// para que lado ele estava olhando 
	data->map->map[(int)data->player.y][(int)data->player.x] = '0'; // trocamos o caractere do jogador para
	// caminho
	result = flood_fill_wall(data->map, data->player.y, data->player.x); // tentamos ver se o mapa é válido e tem um caminho possível
	if (result == 0) // se o flood fill retornar erro
	{
		printf("Error\nInvalid Map.\n"); // avisamos o erro
		kill_game(data); // liberamos a memória e saímos do jogo
	}
}
