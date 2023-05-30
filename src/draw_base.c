/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:42:27 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/30 18:52:43 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Esta função é responsável por colocar um pixel, da cor color na posiçao x,y 
// passada pelo vetor de coordenadas point
void	put_pixel(t_img *data, t_vector point, int color)
{
	char	*dst; // receberá o endereço de memória correspondente ao pixel da imagem

	dst = data->addr + (((int)point.y) * data->size_line + \
	((int)point.x) * (data->bpp / 8)); // decobrimos o endereço
	*(unsigned int *)dst = color; // e atribuimos a cor
}

// Esta função é responsável por posicionar um pixel da textura passada, na posiçao x,y 
// passada pelo vetor de coordenadas point
int	put_texture(t_img *data, t_vector point)
{
	char	*dst; // receberá o endereço de memória correspondente ao pixel da imagem

	dst = data->addr + (((int)point.y) * data->size_line + \
	((int)point.x) * (data->bpp / 8));
	return (*(unsigned int *)dst); // esse endereço vai receber o pixel da textura
}


// Aqui montamos o fundo da imagem. Dividimos a tela ao meio e metade dela, por traz da textura
// é da cor passada para o chão, e a metade de cima é da cor passada como teto
void	set_img_background(t_data *data)
{
	int	height;
	int	width;

	height = 0;
	while (height < SCREEN_HEIGHT) //É iniciado um loop que percorre as linhas da imagem, durante toda
	// a altura da tela
	{
		width = 0;
		while (width < SCREEN_WIDTH) //  é iniciado um loop que percorre as colunas da imagem, até
		// percorrer toda a largura da tela
		{
			if (height < SCREEN_HEIGHT / 2) // a metade de cima da imagem
				put_pixel(&data->paint_img, (t_vector){.x = width, \
				.y = height}, data->ceil);// recebe a cor do teto
			else // a metade de baixo
				put_pixel(&data->paint_img, (t_vector){.x = width, \
				.y = height}, data->floor); // recebe a cor do chão
			width++; // percorremos a largura
		}
		height++; // percorremos toda a altura
	}
}
