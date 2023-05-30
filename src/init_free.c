/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:26:46 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/30 20:30:42 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:26:46 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/30 20:25:19 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:26:46 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/30 20:10:37 by gissao-m         ###   ########.fr       */
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
//função responsável por iniciar as imagens do jogo.
{
	data->paint_img.img_ptr = mlx_new_image(data->mlx->mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT);//faço a minha struct responsável pela pintura receber essa função da mlx que é responsável por criar as imagens com a altura e largura já pré-estabelecidas.
	data->paint_img.addr = mlx_get_data_addr(data->paint_img.img_ptr, \
	&data->paint_img.bpp, &data->paint_img.size_line, &data->paint_img.endian);//essa função da mlx é usada para obter informações sobre a imagem recém-criada. Ela retorna um ponteiro para os dados da imagem (data->paint_img.addr), além de preencher outros campos da estrutura data->paint_img, como o número de bits por pixel (data->paint_img.bpp), o tamanho de cada linha da imagem (data->paint_img.size_line) e a ordem dos bytes nos pixels (data->paint_img.endian).
	data->init_image = 1;//minha variável init_image recebe o valor de 1 indicando que tudo foi inicializado com sucesso.
}

void	kill_window(t_data *data)
//função responsável por destruir as janelas e limpar tudo relacionado à mlx.
{
	mlx_clear_window(data->mlx->mlx, data->mlx->window);//função responsável por limpar a janela criada.
	mlx_loop_end(data->mlx->mlx);//função responsável por stopar o loop infinito, que é utilizada para manter a janela funcionando.
	mlx_destroy_window(data->mlx->mlx, data->mlx->window);//função responsável por destruir a janela e assim limpar o conteúdo da variável void *window
	mlx_destroy_display(data->mlx->mlx);//é usada para encerrar corretamente a exibição gráfica do jogo e liberar os recursos associados a ela
	free(data->mlx->mlx);// limpo o void *mlx.
}

void	free_game(t_data *data)
//função responsável por liberar toda as alocações feitas durante o projeto.
{
	if (data->map->map)//se a variavel map existir.
		free_matrix(data->map->map);//limpo a matriz
	if (data->map->b_map)//se a variavel backup map existir.
		free_matrix(data->map->b_map);//limpo a matriz
	if (data->map != NULL)//se a struct map não estiver vazia.
		free(data->map);//limpo a struct.
	free_tex(data);//função responsável por limpar as texturas.
	if (data->btn)//se a struct buttons não estiver vazia.
		free(data->btn);//limpo a struct.
	if (data->init_image)//se a init_image existir.
		mlx_destroy_image(data->mlx->mlx, data->paint_img.img_ptr);//uso uma função da mlx para destruir as imagens.
	if (data->mlx->mlx != NULL && data->mlx->window != NULL)//se mlx e window existirem.
		kill_window(data);//entro nesta função para destruir a mlx e a window.
	free(data->mlx);//limpo a struct mlx.
	free(data->rc);//limpo a struct raycast.
	exit(0);//finalizo o meu programa.
}

int	kill_game(t_data *data)
//função criada, pois era necessário ser uma função int numa das funções da mlx.
{
	free_game(data);//limpo tudo do meu programa.
	return (1);//retorno 1.
}
