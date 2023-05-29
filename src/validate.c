/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:11:54 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/24 13:34:18 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_args(int argc, char **argv)
{
	size_t	len;
	char	*ver_ext;
	int		fd;

	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments.\n");
		exit(1);
	}
	ver_ext = argv[1];
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(&ver_ext[len - 4], ".cub", 4) != 0)
	{
		printf("Error\nInvalid file extension.\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nAn problem occurred while trying to open file.\n");
		exit (1);
	}
	close (fd);
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
