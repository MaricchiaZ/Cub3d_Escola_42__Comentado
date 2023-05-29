/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:53:48 by gissao-m          #+#    #+#             */
/*   Updated: 2023/05/24 14:01:46 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include "../vector/vector.h"
# include <stdio.h>
# include <math.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stdlib.h>

# define PI 3.1415926535
# define BUFFER_SIZE 1
# define SIZE_IMG 64
# define OPEN_MAX 256
# define SCREEN_WIDTH 600
# define SCREEN_HEIGHT 600
# define YES 1
# define NO 0
# define W 119
# define A 97
# define S 115
# define D 100
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ESC 65307
# define ROTATE_SPEED 0.02f
# define MOVE_SPEED 0.05f
# define X 1
# define Y 0

typedef struct s_rm
{
	char	*gnl_line;
	char	*map;
	char	**aux;
	int		fd;
	int		ck_line;
}	t_rm;

typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
	char	**b_map;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
}	t_mlx;

typedef struct s_img
{
	char	*name;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		dir;
}	t_img;

typedef struct s_coordinate
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_raycast
{
	int			ray;
	double		cam_plane_x;
	t_vector	camera_px;
	t_vector	ray_dir;
	double		delta_dist_x;
	double		delta_dist_y;
	t_coord		pos_map;
	int			dist_wall_x;
	int			dist_wall_y;
	double		side_dist_x;
	double		side_dist_y;
	int			touch_side;
	int			line_height;
	double		perpendicular_wall_dist;
	int			init_draw;
	int			finish_draw;
	int			texture_x;
	int			texture_y;
	double		texture_pos;
	double		step;
	int			color;
	t_img		*tex;
}	t_ray;

typedef struct s_tex
{
	t_img	*north;
	t_img	*south;
	t_img	*east;
	t_img	*west;
}	t_tex;

typedef struct s_buttons
{
	int	move_up;
	int	move_down;
	int	move_left;
	int	move_right;
	int	rotate_left;
	int	rotate_right;
}	t_btn;

typedef struct s_data
{
	t_mlx		*mlx;
	t_tex		*tex;
	t_map		*map;
	t_img		paint_img;
	t_img		wall;
	t_img		door;
	t_vector	plane;
	t_vector	direction;
	t_vector	player;
	float		player_angle;
	double		old_dir_x;
	double		old_plane_x;
	char		respawn;
	int			fd;
	int			init_image;
	int			ceil;
	int			floor;
	int			wall_height;
	int			wall_width;
	int			step;
	t_btn		*btn;
	t_ray		*rc;
}	t_data;

//	apply_texture.c
void	render_with_texture(t_data *data);

// buttons.c
int		press_keys(int key_code, t_data *data);
int		depress_keys(int key_code, t_data *data);

// draw_base.c
void	put_pixel(t_img *data, t_vector point, int color);
int		put_texture(t_img *data, t_vector point);
void	set_img_background(t_data *data);
void	make_line(t_vector v1, t_vector v2, int color, t_data *data);

//	get_next_line.c
char	*get_next_line(int fd);

//	get_params_respawn.c
void	get_params_respawn_player(t_data *data);

//	get_texture.c
t_img	*get_texture(t_data *data);

// init_free.c
void	init_struct(t_data *data, char **argv);
void	init_images(t_data *data);
void	kill_window(t_data *data);
void	free_game(t_data *data);
int		kill_game(t_data *data);

//	// init_free_utils.c
void	free_matrix(char **matrix);
void	free_img(t_img *img, t_data *data);
void	free_tex(t_data *data);
void	error_more_one_player(t_data *data);
void	error_no_player(t_data *data);

//	main.c
void	init_images(t_data *data);

//	make_image.c
int		make_image(t_data *data);
void	do_rayscast(t_data *data);

// make_rgb.c
int		make_rgb(char *str_color);
int		make_color(int color, double shade);

//	movement.c
void	player_rotate(t_data *data);
void	player_walking(t_data *data);

//	parse_texture.c
void	parse_texture(t_data *data, char *file_name);

//	parse_map.c
void	parse_map(t_data *data);
void	get_params_respawn_player(t_data *data);

//	read_map.c
char	**read_maps(char **argv);

//	validate.c
void	validate_args(int argc, char **argv);
void	valid_init_game(int argc, char **argv, t_data *data);

#endif