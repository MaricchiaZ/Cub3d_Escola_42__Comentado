/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:26:30 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/24 14:01:56 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// Essa função carrega cada textura, a partir de um arquivo .XPM (X PixMap) e armazena 
// as informações relevantes na struct t_img texture. (cada um dos lados do jogo tem uma textura própria)
static int	load_texture(t_img *texture, t_data *data)
{
	int	ignore; //  Enão usamos para nada...é apenas uma exigência das funções mlx abaixo.

	texture->img_ptr = mlx_xpm_file_to_image(data->mlx->mlx, texture->name, \
	&ignore, &ignore); //  carregamos a imagem da textura, a partir do arquivo .XPM salvo em 
	// texture->name e retornamos um ponteiro para a imagem carregada, "texture->img_ptr"
	if (!texture->img_ptr) // se a imagem não puder ser aberta
		return (0); // retornamos 0
	texture->addr = mlx_get_data_addr(texture->img_ptr, \
	&texture->bpp, &texture->size_line, &texture->endian); // obtemos informações sobre a imagem
	// como: o endereço de memória onde os dados da imagem estão armazenados, a quantidade de bits 
	// por pixel (texture->bpp), o tamanho de uma linha da imagem em bytes (texture->size_line),
	// e a ordem dos bytes da imagem (texture->endian).
	if (!texture->addr) // se garimpagem desses dados der errado
		return (0); // retornamos 0
	return (1); // se tudo der certo, RETORNAMOS 1
}

// Funçao que verifica se cada uma das texturas foi inicializada corretamente
static int	check_load_texture(t_data *data)
{
	//se não for possível abrir a textura do lado norte
	if (!load_texture(data->tex->north, data))
	{
		printf("Error\nFailed to initialize texture.\n"); // avisamos o erro
		free_game(data); // limpamos a memória e saímos finalizamos o jogo
	}
	if (!load_texture(data->tex->south, data)) //se não for possível abrir a textura do lado sul
	{
		printf("Error\nFailed to initialize texture.\n"); // avisamos o erro
		free_game(data); // limpamos a memória e saímos finalizamos o jogo
	}
	if (!load_texture(data->tex->east, data)) //se não for possível abrir a textura do lado leste
	{
		printf("Error\nFailed to initialize texture.\n"); // avisamos o erro
		free_game(data); // limpamos a memória e saímos finalizamos o jogo
	} 
	if (!load_texture(data->tex->west, data)) //se não for possível abrir a textura do lado oeste
	{
		printf("Error\nFailed to initialize texture.\n"); // avisamos o erro
		free_game(data); // limpamos a memória e saímos finalizamos o jogo
	}
	// se todas as texturas foram devidamente abertas e carregas chegaremos até aqui
	return (1); // se TUDO der certo, retornamos 1
}

int	main(int argc, char **argv)
{
	t_data	data;

	//função responsável por verificar se o jogo tem os pré-requisitos mínimos para abrir.
	valid_init_game(argc, argv, &data);
	//inicializamos a biblioteca gráfica mlx.
	data.mlx->mlx = mlx_init();
	//essa primeira verificação serve para vermos se a iniciliazação da mlx ocorreu, caso não ocorra. Já retorna um erro e limpamos o que alocamos.
	if (!data.mlx->mlx)
	{
		printf("Error\nFailed to initialize window.\n");
		free_game(&data);
	}
	//inicializamos a janela gráfica.
	data.mlx->window = mlx_new_window(data.mlx->mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	//novamente há uma verificação de erro para ver se ocorreu a inicilização da janela de forma correta.
	if (!data.mlx->window)
	{
		printf("Error\nFailed to initialize window.\n");
		free_game(&data);
	}
	//a init games vai servir para fazer a pintura do jogo(parede (N, S, L e O), chão e teto).
	init_images(&data);
	//verificação para ver se todas as paredes tem textura. Se alguma não tiver, o jogo não pode abrir.
	check_load_texture(&data);
	//função da biblioteca mlx responsável por ficar renderizando na tela as imagens do jogo, então a cada momento que eu ando na tela. Tudo é atualizado por essa função.
	mlx_loop_hook(data.mlx->mlx, make_image, &data);
	//função da mlx responsável por fazer com que seja possível apertar as teclas do teclado e movimentar no mapa.
	mlx_hook(data.mlx->window, KeyPress, KeyPressMask, press_keys, &data);
	//função da mlx responsável por verificar se a tecla pressionada, foi despressionada.
	mlx_hook(data.mlx->window, KeyRelease, KeyReleaseMask, depress_keys, &data);
	//função da mlx responsável por verificar se a tecla ESC foi pressionada, ou se o botão "x" da tela foi clicado.
	mlx_hook(data.mlx->window, 17, 0L, kill_game, &data);
	//função da mlx responsável por manter a janela aberta, fica num loop até ser stopada pela tecla ESC, ou botão "x" da janela.
	mlx_loop(data.mlx->mlx);
	return (0);
}
