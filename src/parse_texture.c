/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:28:20 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/24 12:54:20 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_filled_tex(t_data *data)
{
	if (ft_strlen(data->tex->north->name) == 0)
		return (0);
	if (ft_strlen(data->tex->south->name) == 0)
		return (0);
	if (ft_strlen(data->tex->east->name) == 0)
		return (0);
	if (ft_strlen(data->tex->west->name) == 0)
		return (0);
	if (data->ceil == -1)
		return (0);
	if (data->floor == -1)
		return (0);
	return (1);
}

static int	compare_textures(t_data *data, char **tex_wall)
{
	if (tex_wall[0] == NULL || tex_wall[0][0] == '\n' || \
	!ft_strncmp(tex_wall[0], "1", ft_strlen(tex_wall[0])))
		return (1);
	if (ft_strnstr(tex_wall[0], "NO", 3) && data->tex->north->name == NULL)
		data->tex->north->name = ft_strdup_no_nl(tex_wall[1]);
	else if (ft_strnstr(tex_wall[0], "SO", 3) && data->tex->south->name == NULL)
		data->tex->south->name = ft_strdup_no_nl(tex_wall[1]);
	else if (ft_strnstr(tex_wall[0], "EA", 3) && data->tex->east->name == NULL)
		data->tex->east->name = ft_strdup_no_nl(tex_wall[1]);
	else if (ft_strnstr(tex_wall[0], "WE", 3) && data->tex->west->name == NULL)
		data->tex->west->name = ft_strdup_no_nl(tex_wall[1]);
	else if (ft_strnstr(tex_wall[0], "F", 2) && data->floor == -1 \
	&& ft_strlen(tex_wall[1]))
		data->floor = make_rgb(tex_wall[1]);
	else if (ft_strnstr(tex_wall[0], "C", 2) && data->ceil == -1 \
	&& ft_strlen(tex_wall[1]))
		data->ceil = make_rgb(tex_wall[1]);
	else
		return (-1);
	return (0);
}

void	check_error_texture(t_data *data, char *gnl_line)
{
	char	**tex_wall;
	int		check_tex;

	tex_wall = ft_split(gnl_line, ' ');
	check_tex = compare_textures(data, tex_wall);
	free_matrix(tex_wall);
	if (check_tex == -1)
	{
		printf("Error\nTexture fill failed\n");
		free(gnl_line);
		free_game(data);
	}
	if (data->floor == -2 || data->ceil == -2)
	{
		free(gnl_line);
		free_game(data);
	}
}

void	parse_texture(t_data *data, char *file_name)
{
	char	*gnl_line;

	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)
	{
		printf("Error\nAn problem occurred while trying to open file.\n");
		return ;
	}
	gnl_line = get_next_line(data->fd);
	while (gnl_line != NULL)
	{
		if (ft_strncmp(gnl_line, "1111", ft_strlen(gnl_line)) && \
		check_filled_tex(data) == 1)
		{
			free(gnl_line);
			gnl_line = get_next_line(data->fd);
			continue ;
		}
		check_error_texture(data, gnl_line);
		free(gnl_line);
		gnl_line = get_next_line(data->fd);
	}
	close(data->fd);
	free(gnl_line);
}
