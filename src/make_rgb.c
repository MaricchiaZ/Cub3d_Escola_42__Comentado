/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 09:23:56 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/30 19:43:51 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Aqui convertemos um conjunto de valores RGB (vermelho, verde e azul) representados 
//como strings em um único valor inteiro que representa a cor no formato RGB.
static int	compose_rgb(char **rgb)
{
	int	r; // vai receber a quantidade de vermelho RED
	int	g; // vai receber a quantidade de verde GREEN
	int	b; // vai receber a quantidade de azul BLUE

	r = ft_atoi(rgb[0]); // transformamos os chars que compõem o a cor em inteiro
	g = ft_atoi(rgb[1]); // transformamos os chars que compõem o a cor em inteiro
	b = ft_atoi(rgb[2]); // transformamos os chars que compõem o a cor em inteiro
	if ((r == -1 || g == -1 || b == -1) || (r < 0 || g < 0 || b < 0) || \
	(r > 255 || g > 255 || b > 255)) // se estiver fora dos valores aceitáveis...
	{
		printf("Error\ninvalid RGB\n"); // avisamos que é uma cor inválida
		return (-2); // retornamos o erro
	}
	// Se todas as verificações forem bem-sucedidas e os valores RGB forem válidos,
	// a função retorna o valor inteiro calculado da cor no formato RGB. O valor é calculado
	//  multiplicando o componente vermelho por 65536 (256 * 256), o componente verde por 
	// 256 e somando o componente azul.
	return ((r * 65536) + (g * 256) + b);
	// 122 
}

// Essa função é necessária para conferir se a cor foi passada certo no mapa
// não podemos ter menos de 2 vírgulas, nem mais de 2 vírgulas e nem espaços entre
// os fatores que compõe a cor
static int	error_sintaxe(char *str_colour)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0; // inicialmente não temos nenhuma vírgula
	while (str_colour[i])
	{
		if (str_colour[i] == ',') // quando passarmos por uma vírgula
			comma++; // somamos 1 na variável vírgula
		if (str_colour[i] == ' ') // se encontrarmos espaço, já sabemos que está errado... e saímos do jogo
			return (1);
		i++;
	}
	if (comma != 2) // se encontrarmos um número de vírgulas diferente de 2
		return (1); // avisamos que temos um erro
	return (0); // se estiver tudo em ordem, retornamos 0
}

// Nessa funçao conferimos se os componentes do RGB estão presentes e se são válidos
static int	check_rgb(char **rgb, char *str_color)
{
	int	i;

	if (error_sintaxe(str_color)) // se tiver um erro de sintaxe
		return (1); // retornamos 1
	i = 0;
	while (rgb[i]) // enquanto não percorrermos matriz inteira
		i++; // vamos andando
	if (i != 3) // se tiver um número de componentes diferente de 3
		return (1); // está errado, então retornamos o erro
	i = 0; // rezamos o i para poder reutilizar
	while (rgb[i] && i < 3) // vamos percorrer cada componente
	{
		if (rgb[i][0] == '\n') // se estiver vazio
			return (1); // não conseguimos compor a cor, então avisamos o erro
		if (ft_str_isdigit_or_nwline(rgb[i])) // conferimos se é composto apenas por números ou \n
			return (1); // se tiver caracteres estranhos avisamos o erro, e saímos
		i++;
	}
	return (0); // se der tudo certo, retornamos 0
}

// Essa função transforma a string str_color  com 3 sequências de números em uma cor no
//  formato RGB e retorna o valor inteiro correspondente à cor no formato RGB. 
// EXEMPLO: string{122,132,76} vira a cor 8.029.260(bege)
int	make_rgb(char *str_color)
{
	char	*temp_rgb;
	char	**rgb;
	int		colour;

	colour = 0;
	temp_rgb = ft_strtrim(str_color, " "); // primeiro tiramos os espaços antes e depois da string
	rgb = ft_split(temp_rgb, ','); // splitamos a string nas vírgulas
	if (check_rgb(rgb, str_color)) // conferimos se os valores são válidos para montar a cor
	{
		printf("Error\ninvalid RGB\n");
		free_matrix(rgb);
		free(temp_rgb);
		return (-2);
	}
	colour = compose_rgb(rgb); // montamos a cor
	free_matrix(rgb); // liberamos a memória usada temporariamente aqui
	free(temp_rgb); // e aqui
	return (colour); // e retornamos o valor inteiro da cor
}

// A função make_color recebe um valor inteiro color representando uma cor no formato RGB
// e um valor shade que determina a intensidade da cor. 
int	make_color(int color, double shade)
{
	int	r; // vai receber o fator VERMELHO da cor
	int	g; // vai receber o fator VERDE da cor
	int	b; // vai receber o fator AZUL da cor

	r = ((color & (0xFF << 16)) >> 16) * shade; // aplica a intensidade sobre o VERMELHO
	g = ((color & (0xFF << 8)) >> 8) * shade; // aplica a intensidade sobre o VERDE
	b = (color & 0xFF) * shade; // aplica a intensidade sobre o AZUL
	return (r << 16 | g << 8 | b); // recalcula a nova cor
} 
