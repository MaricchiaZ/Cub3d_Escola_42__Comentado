/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:11:54 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/30 18:51:51 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

gissomgissom14gissom#include "cub3d.h"

void	validate_args(int argc, char **argv)
//Esta função verificará se os argumentos passados estão corretos
{
	size_t	len;
	//variavel para pegar o taamnho do argumento mapa passado.
	char	*ver_ext;
	//string responsável por salvar o nome completo para verificação d
	int		fd;
	//file_descriptor

	if (argc != 2)
	//se o número de argumentos passados for diferente de 2 (o executável (./cub3D) e o mapa (mini.cub))
	{
		printf("Error\nInvalid number of arguments.\n");
		//printa um erro
		exit(1);
		//já sai da execução.
	}
	ver_ext = argv[1];
	//verificação de extensão recebe o argumento 1.
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(&ver_ext[len - 4], ".cub", 4) != 0)
	//se o tamanho do nome do mapa for menor que 5(algum caracter + .cub), ou o final for diferente de ./cub
	{
		printf("Error\nInvalid file extension.\n");
		//printo erro relacionado a extensão do mapa.
		exit(1);
		//saio do programa.
	}
	fd = open(argv[1], O_RDONLY);
	//verifico se há algo quando eu abro o argumento 1
	if (fd == -1)
	//Se não tiver nada no argumento 1
	{
		printf("Error\nAn problem occurred while trying to open file.\n");
		//retornamos erro.
		exit (1);
		//saimos do programa.
	}
	close (fd);
	//fecho o fd que abri anteriormente.
}

void	valid_init_game(int argc, char **argv, t_data *data)
//função que chama todas as outras funções para fazer as validações necessárias.
{
	//verificará se os argumentos passados são válidos.
	validate_args(argc, argv);
	//inicializará as structs e fará os mallocs necessários.
	init_struct(data, argv);
	//verificará se as texturas estão corretamente preenchidas para poder abrir o mapa.
	parse_texture(data, argv[1]);
	//analisará o mapa e ver se atende os pré-requisitos do mandatório.
	parse_map(data);
	//pegará a posição, onde o player nasce.
	get_params_respawn_player(data);
}
