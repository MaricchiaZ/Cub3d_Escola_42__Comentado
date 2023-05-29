/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:05:53 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/24 14:01:22 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
{
	free_matrix(aux);
	free(gnl_line);
}

char	**read_maps(char **argv)
{
	t_rm	rm;

	rm.fd = open (argv[1], O_RDONLY);
	rm.gnl_line = get_next_line(rm.fd);
	rm.map = ft_strdup("");
	rm.ck_line = ft_strlen(rm.gnl_line);
	while (rm.gnl_line)
	{
		rm.aux = ft_split(rm.gnl_line, ' ');
		if (!ft_strchr(*rm.aux, '1'))
		{
			free_read_maps(rm.aux, rm.gnl_line);
			rm.gnl_line = get_next_line(rm.fd);
			continue ;
		}
		rm.map = ft_strjoin(rm.map, rm.gnl_line);
		free_read_maps(rm.aux, rm.gnl_line);
		rm.gnl_line = get_next_line(rm.fd);
		if ((rm.ck_line < 3 && rm.gnl_line != NULL) || rm.gnl_line == NULL )
			continue ;
		rm.ck_line = ft_strlen(rm.gnl_line);
	}
	free(rm.gnl_line);
	close(rm.fd);
	return (make_map(rm.map, rm.ck_line));
}
