/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:47:59 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/19 20:17:35 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Essa função inverte as imagens da textura das paredes
// como as imagens estão espelhadas devemos usar ssa fórmura que espelhe/rotacione as imagens
// verticalmente (isso é possível observar se vc usar uma imagem para a textura que tenha 
// algo escrito)
static int	vertical_mirror(int texture, t_data *data)
{
	if (data->rc->touch_side == 0 && data->rc->ray_dir.x < 0) //verificacamos se o raio está atingindo o lado esquerdo de um objeto
		texture = 64 - texture - 1; // refletimos a textura verticalmente. Se texture for 0, 
		//o resultado será 64 - 0 - 1 = 63, ou seja, a textura é espelhada para a última posição da linha.
	if (data->rc->touch_side == 1 && data->rc->ray_dir.y > 0) //verificacamos se o raio está atingindo o lado direito de um objeto
		texture = 64 - texture - 1; // refletimos a textura verticalmente. Se texture for 0, 
		//o resultado será 64 - 0 - 1 = 63, ou seja, a textura é espelhada para a última posição da linha.
	return (texture); // retornamos a textura já espelhada
}

// Essa função calcula e retorna a textura apropriada para um determinado ponto na parede do jogo
static int	set_texture(t_data *data)
{
	int		texture; //  para armazenar o valor da textura a ser determinada
	double	wall; // para calcular a distância perpendicular até a parede

	if (data->rc->touch_side == 0) // Se atingir o lado esquerdo ou direito da parede.
	{
		if (data->rc->ray_dir.x > 0) // Isso verifica se o raio está indo para a direita
			wall = fabs(data->player.y + data->rc->perpendicular_wall_dist * \
			data->rc->ray_dir.y); //  calcula-se a posição da parede somando a coordenada y do jogador
			// com a distância perpendicular multiplicada pelo componente y da direção do raio.
		else // Se o raio está indo para a esquerda
			wall = fabs(data->player.y - data->rc->perpendicular_wall_dist * \
			data->rc->ray_dir.y); // OU calcula-se a posição da parede subtraindo a coordenada y do jogador
			// pela distância perpendicular multiplicada pelo componente y da direção do raio.
	}
	else // Tratamos do caso em que o raio atinge o lado superior ou inferior da parede
	{
		if (data->rc->ray_dir.y > 0) //  Isso verifica se o raio está indo para cima
			wall = fabs(data->player.x + data->rc->perpendicular_wall_dist * \
			data->rc->ray_dir.x); //  calcula-se a posição da parede somando a coordenada x do jogador 
			//com a distância perpendicular multiplicada pelo componente x da direção do raio
		else //  Ou se o raio está indo para baixo
			wall = fabs(data->player.x - data->rc->perpendicular_wall_dist * \
			data->rc->ray_dir.x); //  calcula-se a posição da parede subtraindo a coordenada x do jogador pela distância perpendicular multiplicada pelo componente x da direção do raio.
	}
	wall -= floor(wall); //  Isso é feito para obter apenas a parte fracionária da posição da parede 
	// (considerar apenas a parte fracionária da posição da parede, a função consegue determinar qual parte
	//  da textura deve ser exibida nessa posição específica, garantindo um mapeamento adequado entre a 
	// textura e a geometria do ambiente 3D.)
	texture = (int)(wall * (double)SIZE_IMG); // multiplica-se a parte fracionária de wall pelo tamanho total da
	// imagem (SIZE_IMG) e convertendo-a para um valor inteiro.
	texture = vertical_mirror(texture, data); // vertical_mirror realiza um espelhamento vertical na textura.
	return (texture); // retornamos a textura já ajustada
}

// Essa função renderiza uma parede na imagem do jogo
static void	render_wall(t_data *data)
{
	int	line; // para armazenar o número da linha atual (dos pixels da tela)
	int	colour; // para salvar a cor do pixel da textura

	line = data->rc->init_draw; // representa a linha inicial a partir da qual a parede será desenhada
	while (line < data->rc->finish_draw) // até acabar de fazer a parede
	{
		data->rc->texture_y = (int)data->rc->texture_pos & (64 - 1); //  linha atual é processada para determinar
		// a posição vertical na textura da parede, data->rc->texture_y é atualizada com o valor da parte 
		//inteira da posição vertical da textura.
		data->rc->texture_pos += data->rc->step; // é incrementada em data->rc->step, pelo valor 
		//para se percorrer a textura horizontalmente.
		colour = put_texture(data->rc->tex, (t_vector) \
		{.y = data->rc->texture_y, .x = data->rc->texture_x}); // put_texture obtém a cor do pixel
		// correspondente àquela posição da textura
		put_pixel(&data->paint_img, (t_vector){.x = data->rc->ray, \
		.y = line}, colour); //  put_pixel é chamada para desenhar o pixel na tela, utilizando as 
		//coordenadas (data->rc->ray, line), e a cor colour.
		line++; // passamos para a próxima linha a ser desenhada.
	}
}


// Função responsável por renderizar uma parede com uma textura específica na imagem do jogo
void	render_with_texture(t_data *data)
{
	data->rc->texture_x = set_texture(data); // calcula e retorna a posição horizontal na textura
	data->rc->step = 1.0 * 64 / data->rc->line_height; //  data->rc->step é calculada como um valor decimal 
	// representando o incremento para percorrer a textura horizontalmente. (Calculamos isso 
	//dividindo 64 (tamanho da textura em pixels) pelo data->rc->line_height (altura da parede))
	data->rc->texture_pos = (data->rc->init_draw - SCREEN_HEIGHT / 2 + \
	data->rc->line_height / 2) * data->rc->step; // calculamos a posição da textura
	data->rc->tex = get_texture(data); // obtemos a textura específica para cada lado do jogo
	render_wall(data);  //renderizamos a parede com a textura correta
}
