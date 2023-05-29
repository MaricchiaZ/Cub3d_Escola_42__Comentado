/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:57:48 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/22 22:20:53 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_buffers(int fd, char *store_rest, char *buffer)
{
	int		read_bytes;

	read_bytes = 1;
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		if (!store_rest)
			store_rest = ft_strdup("");
		store_rest = ft_strjoin(store_rest, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (store_rest);
}

static char	*separete_line_rest(char *line)
{
	char	*rest_line;
	int		i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	rest_line = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*rest_line == '\0')
	{
		free(rest_line);
		rest_line = NULL;
	}
	line[i + 1] = '\0';
	return (rest_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*store_rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc((sizeof(char)) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_buffers(fd, store_rest, buffer);
	free(buffer);
	if (!line)
		return (line);
	store_rest = separete_line_rest(line);
	return (line);
}
