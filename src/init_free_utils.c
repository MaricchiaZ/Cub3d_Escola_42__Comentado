/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:26:58 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/30 19:12:04 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrix(char **matrix)
//função responsável por limpar a matriz alocada com o mapa.
{
	int	i;//contador

	i = 0;//atribuo um valor ao contador.
	if (matrix == NULL)//se a matriz não tiver nada dentro.
		return ;//retorno.
	while (matrix[i])//enquanto a matriz existir
	{
		free(matrix[i]);
		//vou limpando onde o i vai passando.
		i++;//vou incrementando até não sobrar mais nada e o i cheg
	}
	free(matrix);//limpo o ponteiro de fora.
}

void	free_img(t_img *img, t_data *data)
//função responsável por limpar as imagens que aparecem nas paredes, teto e chão.
{
	if (img->name != NULL)//se tiver conteúdo na minha variável name do tipo string 
		free(img->name);//limpo o seu conteúdo.
	if (img->img_ptr)//se tiver conteúdo na minha variável do tipo void *.
		mlx_destroy_image(data->mlx->mlx, img->img_ptr);//uso uma função própria da mlx, para destruir aquela imagem.
	if (img)//depois de limpar as variáveis da minha struct que são alocadas.
		free(img);//eu limpo a minha struct que está alocada.
}

void	free_tex(t_data *data)
//função responsável por limpar todas as structs de texturas que foram alocadas.
{
	if (data->tex->north)//se tiver conteúdo na variável north.
		free_img(data->tex->north, data);//uso a função free_img para limpar a struct
	if (data->tex->south)//se tiver conteúdo na variável south.
		free_img(data->tex->south, data);//uso a função free_img para limpar a struct
	if (data->tex->east)//se tiver conteúdo na variável east.
		free_img(data->tex->east, data);//uso a função free_img para limpar a struct
	if (data->tex->west)//se tiver conteúdo na variável west.
		free_img(data->tex->west, data);//uso a função free_img para limpar a struct
	free(data->tex);//após liberar todas as structs dentro da struc tex, limpo minha struct tex que é a de fora.
}

void	error_more_one_player(t_data *data)
//erro para quando há mais de um player no mapa.
{
	printf("Error\nMore than one player in the map.\n");
	//printo o erro
	free_game(data);
	//limpo tudo o que aloquei e saio do programa.
}

void	error_no_player(t_data *data)
//erro para quando não há player no mapa.
{
	printf("Error\nThere's no player in the map.\n");
	//printo erro.
	free_game(data);
	//limpo tudo o que aloquei e saio do meu programa.
}
