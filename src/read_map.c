/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:05:53 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/30 20:01:07 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

606gissomgissom54gissom/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:05:53 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/30 19:29:53 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

gissomgissom30gissom#include "cub3d.h"

static char	**make_map(char *map, int ck_line)
{
	char	**temp;

	temp = NULL;
	if (ck_line >= 3)
		temp = ft_split(map, '\n');
	free(map);
	return (temp);
}

static void	free_read_maps(char **aux, char *gnl_line)
//função responsável por limpar a minha string da gnl e limpar a matriz auxiliar.
{
	free_matrix(aux);//limpo a matriz auxiliar.
	free(gnl_line);//limpo a minha gnb
}

char	**read_maps(char **argv)
//função responsável por ler o mapa e retorná-lo em matriz.
{
	t_rm	rm;
	//struct com as variáveis necessárias para criar o mapa.

	/* Opening the file specified in the command line argument `argv[1]` in read-only mode (`O_RDONLY`)
	and assigning the file descriptor to the variable `rm.fd`. */
	rm.fd = open (argv[1], O_RDONLY);//abre o fd especificado no caso do argumento 1 no modo de leitura apenas.
	rm.gnl_line = get_next_line(rm.fd);//com o fd já aberto, uso a função get_next_line que usa o fd que eu obtive anteriormente. A função get_nex_line pegará a string passada dentro do argumento 1 e a retornará. Neste caso, como eu preciso dessa string, vou salvá-la na minha variável g
	rm.map = ft_strdup("");//faço um dup vazio(para fazer uma alocação).
	rm.ck_line = ft_strlen(rm.gnl_line);//vou utilizar a função strlen para pegar o tamanho total da minha string e salvá-la nesta variável do tipo inteiro rm.ck_line.
	while (rm.gnl_line)//enquanto a 
	{
		rm.aux = ft_split(rm.gnl_line, ' ');//dou split(dividir) nos espaços da minha string gnl_line e salvo na minha matriz auxiliar(rm.aux).
		/* This code block checks if the current line being read from the file contains the character '1'. If
		it doesn't, it means that it's not part of the map and should be skipped. The function `ft_strchr`
		is used to check if the character '1' is present in the current line. If it's not present, the
		memory allocated for the `rm.aux` matrix and the `rm.gnl_line` string is freed, and the function
		`get_next_line` is called again to read the next line. The `continue` statement is used to skip
		the rest of the loop and start the next iteration. */
		if (!ft_strchr(*rm.aux, '1'))
		//essa verificação serve para pegar apenas o mapa e não as texturas que vem antes do mapa. Então ele checa todas as linhas até aparecer a primeira ocorrencia de paredes. Se não for as paredes (valor 1), entra aqui.
		{
			free_read_maps(rm.aux, rm.gnl_line);//limpa o conteúdo das variáveis que não valem para a formação do mapa.
			rm.gnl_line = get_next_line(rm.fd);//faz a variável receber o novo valor sem a parte descartada.
			continue ;//continua até achar as paredes(1).
		}
		rm.map = ft_strjoin(rm.map, rm.gnl_line);//quando o mapa começa a aparecer, eu concateno o mapa na minha variavel map do tipo string criada anteriormente.
		free_read_maps(rm.aux, rm.gnl_line);//limpo a minha matriz auxiliar.
		rm.gnl_line = get_next_line(rm.fd);//faço a minha gnl_line receber um novo valor, sem a linha anterior porque eu já salvei na variável map acima.
		/* This code block is checking if the current line being read from the file is valid for the map. If
		the length of the line is less than 3 characters and it's not the last line of the file, or if
		it's the last line of the file, the loop continues to the next iteration without processing the
		current line. If the line is valid, the length of the line is saved in the `rm.ck_line` variable
		for future use. */
		if ((rm.ck_line < 3 && rm.gnl_line != NULL) || rm.gnl_line == NULL )//essa condição serve para verificarmos se a linha atual que vai ser lida atendem os requisitos necessários para formar o mapa. Se o comprimento for menor que 3 caracteres e e não é a última linha da string gnl_line, ou se é a última linha do arquivo, entra nessa condição.
			continue ;//continua para a próxima repetição.
		rm.ck_line = ft_strlen(rm.gnl_line);//o comprimento da linha é salvo na variavel ck_line.
	}
	free(rm.gnl_line);//limpo a minha string gnl_line
	close(rm.fd);//fecho o meu fd.
	return (make_map(rm.map, rm.ck_line));//retorno uma função que nela retornarei o mapa em formato de matriz, até então, meu mapa tem formato de string.
}
