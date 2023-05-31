/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:28:20 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/31 19:47:394 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Essa função verifica se todas as texturas e valores de cor de teto e chão foram preenchidos 
// corretamente na estrutura t_data. 
static int	check_filled_tex(t_data *data)
{
	if (ft_strlen(data->tex->north->name) == 0) // confere se tem algo (nome e caminho para as texturas)
	//  para a textura do norte
		return (0);
	if (ft_strlen(data->tex->south->name) == 0) // confere se tem algo (nome e caminho para as texturas)
	//  para a textura do sul
		return (0);
	if (ft_strlen(data->tex->east->name) == 0)  // confere se tem algo (nome e caminho para as texturas)
	//  para a textura do leste
		return (0);
	if (ft_strlen(data->tex->west->name) == 0)  // confere se tem algo (nome e caminho para as texturas)
	//  para a textura do oeste
		return (0);
	if (data->ceil == -1) // confere se tem algum valor para a cor do teto
		return (0);
	if (data->floor == -1) // confere se tem algum valor para a cor do chão
		return (0);
	return (1);
}

// Aqui compararamos as informações das texturas e cores fornecidas no arquivo de configuração 
// com as informações armazenadas na estrutura t_data.
static int	compare_textures(t_data *data, char **tex_wall)
{
	if (tex_wall[0] == NULL || tex_wall[0][0] == '\n' || \
	!ft_strncmp(tex_wall[0], "1", ft_strlen(tex_wall[0]))) // se for nulo ou quebra de linha
		return (1); // retornamos
	if (ft_strnstr(tex_wall[0], "NO", 3) && data->tex->north->name == NULL) // se na tex_wall[0] tiver "NO"
		data->tex->north->name = ft_strdup_no_nl(tex_wall[1]); // salvamos o endereço da textura em 
		// data->tex->north->name
	else if (ft_strnstr(tex_wall[0], "SO", 3) && data->tex->south->name == NULL) // se na tex_wall[0] tiver "SO"
		data->tex->south->name = ft_strdup_no_nl(tex_wall[1]); // salvamos o endereço da textura em 
		// data->tex->south->name
	else if (ft_strnstr(tex_wall[0], "EA", 3) && data->tex->east->name == NULL) // se na tex_wall[0] tiver "EA"
		data->tex->east->name = ft_strdup_no_nl(tex_wall[1]); // salvamos o endereço da textura em 
		// data->tex->east->name
	else if (ft_strnstr(tex_wall[0], "WE", 3) && data->tex->west->name == NULL) // se na tex_wall[0] tiver "WE"
		data->tex->west->name = ft_strdup_no_nl(tex_wall[1]);  // salvamos o endereço da textura em 
		// data->tex->west->name 
	else if (ft_strnstr(tex_wall[0], "F", 2) && data->floor == -1 \
	&& ft_strlen(tex_wall[1])) // se na tex_wall[0] tiver "F"
		data->floor = make_rgb(tex_wall[1]); // calculamos a cor do chão e salvamos em data->floor 
	else if (ft_strnstr(tex_wall[0], "C", 2) && data->ceil == -1 \
	&& ft_strlen(tex_wall[1])) // se na tex_wall[0] tiver "C"
		data->ceil = make_rgb(tex_wall[1]); // calculamos a cor do chão e salvamos em data->teto
	else
		return (-1);
	return (0);
}

//  Aqui vamos verificar os erros relacionados à leitura e preenchimento das informações de 
// textura e cor no arquivo de configuração.
void	check_error_texture(t_data *data, char *gnl_line)
{
	char	**tex_wall;
	int		check_tex;

	tex_wall = ft_split(gnl_line, ' '); // tiramos os espaços anteriores e posteriores da textura
	check_tex = compare_textures(data, tex_wall); // salvamos a textura nos locais adequados
	free_matrix(tex_wall); //função responsável por limpar a matriz que foi criada anteriormente.
	if (check_tex == -1)//se não existir textura
	{
		printf("Error\nTexture fill failed\n");//avisamos o erro.
		free(gnl_line);//limpo a string gnl_line
		free_game(data);//limpo a struct data.
	}
	if (data->floor == -2 || data->ceil == -2) // se não for salvo um valor para a cor do teto e do chão
	{
		// o erro já foi avisado
		free(gnl_line);//limpo a string gnl_line
		free_game(data);//limpo a struct data.
	}
}

// Essa função analisa o arquivo de texturas especificado pelo parâmetro file_name e
// preencher as informações de textura na estrutura data. 
void	parse_texture(t_data *data, char *file_name)
{
	char	*gnl_line;

	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)//se não tiver nada no fd
	{
		printf("Error\nAn problem occurred while trying to open file.\n");//printo erro ao tentar abrir o arquivo.
		return ;//retorno
	}
	gnl_line = get_next_line(data->fd); // pegamos a primeira linha do arquivo passado por argv[1]
	while (gnl_line != NULL)
	{
		if (ft_strncmp(gnl_line, "1111", ft_strlen(gnl_line)) && \
		check_filled_tex(data) == 1) // verifica se a linha tem algo além de 1 e se a checagem está correta
		{
			free(gnl_line);
			gnl_line = get_next_line(data->fd); // lemos uma nova linha
			continue ; // voltamos para o início do while
		}
		check_error_texture(data, gnl_line); // verificamos os erros de textura da linha atual.
		free(gnl_line);//limpo a string gnl_line
		gnl_line = get_next_line(data->fd); // lemos uma nova linha
	}
	close(data->fd);//fecha o fd.
	free(gnl_line);//limpa a string gnl_line.
}
