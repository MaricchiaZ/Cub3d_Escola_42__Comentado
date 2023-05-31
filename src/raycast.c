/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:44:53 by maclara-          #+#    #+#             */
/*   Updated: 2023/05/30 20:37:32 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Esta função calcula as distâncias e as diferenças laterais para as paredes mais
//  próximas em relação à posição atual do jogador.
static void	get_distance_near_square(t_data *data)
{
	if (data->rc->ray_dir.x < 0) // se o raio apontar para a esquerda
	{
		data->rc->dist_wall_x = -1; // indica que a parede mais próxima está a esquerda
		data->rc->side_dist_x = (data->player.x - data->rc->pos_map.x) * \
		data->rc->delta_dist_x; // aí calcula a distância
	}
	else // se o raio apontar para a direita
	{
		data->rc->dist_wall_x = 1; // indica que a parede mais próxima está a direira
		data->rc->side_dist_x = (data->rc->pos_map.x + 1 - data->player.x) * \
		data->rc->delta_dist_x;  // aí calcula a distância
	}
	if (data->rc->ray_dir.y < 0) // se o raio aponta para cima
	{
		data->rc->dist_wall_y = -1; // indica que a parede mais próxima está acima
		data->rc->side_dist_y = (data->player.y - data->rc->pos_map.y) * \
		data->rc->delta_dist_y;  // aí calcula a distância
	}
	else // se o raio aponta para baixo
	{ 
		data->rc->dist_wall_y = 1; // indica que a parede mais próxima está abaixo
		data->rc->side_dist_y = (data->rc->pos_map.y + 1 - data->player.y) * \
		data->rc->delta_dist_y; // aí calcula a distância
	}
}

// Aqui descobrimos as distâncias incrementais para a próxima coluna ou linha de quadrados
// (squares) no mapa, com base na direção do raio (ray_dir) atual.
static void	get_distance_next_square(t_data *data)
{
	if (data->rc->ray_dir.x == 0) // se o raio for paralelo ao eixo y
		data->rc->delta_dist_x = 10000000; //  Nesse caso, a distância incremental (delta_dist_x)
		//  é definida como um valor alto (10000000) para indicar que é praticamente infinita e 
		//que não deve ser considerada.
	else // se não for paralelo, calculamos a distância incremental, que é a distância que o raio 
	// precisa percorrer em cada incremento no eixo x para atravessar uma unidade de largura no mapa.
		data->rc->delta_dist_x = fabs(1 / data->rc->ray_dir.x);
	if (data->rc->ray_dir.y == 0) // se o raio for paralelo ao eixo x
		data->rc->delta_dist_y = 10000000;  //  Nesse caso, a distância incremental (delta_dist_x)
		//  é definida como um valor alto (10000000) para indicar que é praticamente infinita e 
		//que não deve ser considerada.
	else
		data->rc->delta_dist_y = fabs(1 / data->rc->ray_dir.y); // calculamos a distância incremental, ou seja
		// a distância que o raio precisa percorrer em cada incremento no eixo y para atravessar 
		// uma unidade de altura no mapa.
}

// Aqui implementamos o algoritmo DDA (Digital Differential Analyzer) para determinar as interseções do
//  raio com as paredes do mapa. Esse algoritmo é utilizado no processo de lançamento de raios (raycasting) 
// para determinar as interseções do raio com as paredes do mapa. Ele percorre o raio em intervalos 
// discretos ao longo dos eixos x e y do mapa, calculando as distâncias até as próximas interseções e 
// atualizando a posição do raio até que uma parede seja encontrada
static void	algorithm_dda(t_data *data)
{
	data->rc->touch_side = 0;  // a variável touch_side vale 0 para indicar que o raio não 
	// tocou em uma parede lateral ainda.
	while (data->map->map[data->rc->pos_map.y][data->rc->pos_map.x] == '0') // enquanto estivermos em um
	// caractere vazio
	{
		if (data->rc->side_dist_x < data->rc->side_dist_y) // Se a distância no eixo x for menor
		{
			data->rc->side_dist_x += data->rc->delta_dist_x; // atualizamos a distância até a próxima 
			// interseção no eixo x adicionando a distância incremental 
			data->rc->pos_map.x += data->rc->dist_wall_x; // atualizamos a posição atual no mapa no eixo x 
			// adicionando o valor dist_wall_x, que indica a direção na qual o raio está se movendo no eixo x. 
			data->rc->touch_side = 0; // definimos touch_side como 0 para indicar que o raio 
			// tocou em uma parede vertical.
		}
		else //  se a distância no eixo y for menor,
		{
			data->rc->side_dist_y += data->rc->delta_dist_y; // atualizamos a distância até a próxima 
			// interseção no eixo y adicionando a distância incremental 
			data->rc->pos_map.y += data->rc->dist_wall_y; // atualizamos a posição atual no mapa no eixo y 
			// adicionando o valor dist_wall_y, que indica a direção na qual o raio está se movendo no eixo y.
			data->rc->touch_side = 1; // definimos touch_side como 1 para indicar que o raio tocou em 
			// uma parede horizontal.
		}
	} // O loop continua até que a posição atual no mapa não seja mais um espaço vazio (caractere '0').
}

// Esta função renderiza a parede encontrada pelo algoritmo de lançamento de raios.
static void	render_wall(t_data *data)
{
	data->rc->line_height = fabs(SCREEN_HEIGHT / \
	data->rc->perpendicular_wall_dist); // Calculamos a altura da linha da parede a ser renderizada.
	//  Essa altura é determinada pela distância perpendicular da câmera até a parede e é
	//  proporcional à altura da tela (SCREEN_HEIGHT). A função utiliza a função fabs para obter
	//  o valor absoluto da altura.
	data->rc->init_draw = -data->rc->line_height / 2 + SCREEN_HEIGHT / 2; // Calculamos a posição inicial
	//  de desenho da parede na tela. A posição é calculada subtraindo a metade da altura da linha 
	// da parede (line_height) dividida por 2 da metade da altura da tela (SCREEN_HEIGHT / 2). Essa
	//  fórmula centraliza verticalmente a linha da parede na tela. Se o valor resultante for 
	// menor que 0, é ajustado para 0.
	if (data->rc->init_draw < 0) //  Se o valor resultante for menor que 0,
		data->rc->init_draw = 0; //  é ajustado para 0.
	data->rc->finish_draw = data->rc->line_height / 2 + SCREEN_HEIGHT / 2; // Calcula a posição final
	//  de desenho da parede na tela. A posição é calculada somando a metade da altura da linha da
	//  parede (line_height) dividida por 2 à metade da altura da tela (SCREEN_HEIGHT / 2). Essa 
	// fórmula centraliza verticalmente a linha da parede na tela. 
	if (data->rc->finish_draw >= SCREEN_HEIGHT) // Se o valor resultante for maior ou igual à 
	//altura da tela (SCREEN_HEIGHT)
		data->rc->finish_draw = SCREEN_HEIGHT - 1; // é ajustado para o valor máximo permitido de
		//  desenho na tela (SCREEN_HEIGHT - 1).
	render_with_texture(data); // renderizamos a linha da parede utilizando uma textura.
}

// Essa função que realmente dá o efeito 3D para o jogo.
// Ela que é responsável por realizar o lançamento de raios para renderizar a cena 3D do jogo.
void	do_rayscast(t_data *data)
{
	data->rc->ray = 0;
	while (data->rc->ray < SCREEN_WIDTH) // loop que itera sobre cada raio horizontal na tela
	{
		data->rc->cam_plane_x = 2 * data->rc->ray / (double)SCREEN_WIDTH - 1; // Calculamos  a posição
		//  do plano de câmera para o raio atual. O valor é obtido por meio de uma fórmula que mapeia a 
		// posição do raio na tela (data->rc->ray) para um valor entre -1 e 1, representando a posição
		//  no plano de câmera horizontal.
		data->rc->camera_px = data->plane; // Calculamos  o deslocamento do ponto da câmera em 
		// relação ao plano de câmera para o raio atual. O valor é obtido multiplicando o vetor 
		// data->plane pela posição do plano de câmera horizontal.
		vector_scale(&data->rc->camera_px, data->rc->cam_plane_x); // aqui definimos a direção do 
		// raio, que é igual à direção geral do jogador. Em seguida, soma o vetor de deslocamento 
		// da câmera ao vetor de direção do raio para obter a direção final do raio.
		data->rc->ray_dir = data->direction; // definimos a direção do raio, que é igual à direção
		//  geral do jogador.
		vector_sum(&data->rc->ray_dir, &data->rc->camera_px); // somamos o vetor de deslocamento da câmera ao vetor de direção do raio para obter a direção final do raio.
		get_distance_next_square(data); // essa funçao calcula as distâncias dos próximos quadrados
		//  que o raio irá atravessar.
		data->rc->pos_map = (t_coord){.y = (int)data->player.y, \
		.x = (int)data->player.x}; // salvamos a posição inicial do raio no mapa, arredondando as coordenadas do jogador para números inteiros.
		get_distance_near_square(data); // essa função é usada para calcular as distâncias dos quadrados adjacentes mais próximos ao raio.
		algorithm_dda(data); //  algoritmo DDA (Digital Differential Analysis) vai  determinar a 
		// colisão do raio com as paredes do mapa. O algoritmo incrementa a posição do raio ao longo 
		// do mapa até encontrar uma parede representada pelo valor '1'. O tipo de colisão (horizontal 
		// ou vertical) é determinado e armazenado na variável data->rc->touch_side.
		
		// Agora calculamos a distância perpendicular da câmera até a parede atingida pelo raio. 
		// A fórmula utilizada varia dependendo do tipo de colisão (horizontal ou vertical) e 
		// considera a posição do raio no mapa, a posição do jogador e a distância percorrida
		//  pelo raio até atingir a parede.
		if (data->rc->touch_side == 0) 
			data->rc->perpendicular_wall_dist = (fabs(data->rc->pos_map.x - \
			data->player.x + ((1 - data->rc->dist_wall_x) / 2)) / \
			data->rc->ray_dir.x);
		else
			data->rc->perpendicular_wall_dist = (fabs(data->rc->pos_map.y - \
			data->player.y + ((1 - data->rc->dist_wall_y) / 2)) / \
			data->rc->ray_dir.y);
		render_wall(data); // renderizamos a parede atingida pelo raio
		data->rc->ray++; // Incrementamos a variável data->rc->ray para prosseguir para o próximo raio
	}
}
