/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:29:13 by fgolino           #+#    #+#             */
/*   Updated: 2024/05/14 12:38:38 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <error.h>
# include <string.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include "mlx_linux/mlx.h"

# define X 0
# define Y 1

typedef struct s_player
{
	double	x;
	double	y;
	int		map_x;
	int		map_y;
	char	direction;
	double	camera_x;
	double	camera_y;
	int		found;
	int		space;
	int		m_r;
	int		m_f;
	int		m_l;
	int		m_b;
	int		r_r;
	int		r_l;
}	t_player;

typedef struct s_ray
{
	double	direct_x;
	double	direct_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_x;
	double	delta_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	double	perpwall_dist;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		color;
	int		w;
	int		h;
	char	*path;
}	t_texture;

typedef struct s_data
{
	char		**map;
	int			map_height;
	int			ber_fd;
	int			floor_color;
	int			ceiling_color;
	int			res_h;
	int			res_w;
	void		*mlx;
	void		*window;
	int			def_x;
	int			def_y;
	int			mouse_x;
	int			mouse_y;
	int			z;
	int			hit;
	int			side;
	double		scale;
	double		wall_x;
	int			line_height;
	double		frame_c;
	int			p;
	t_list		*list;
	t_list		*save_list;
	t_player	*player;
	t_texture	frames[15];
	t_texture	ceiling;
	t_texture	floor;
	t_texture	n;
	t_texture	s;
	t_texture	w;
	t_texture	e;
	t_texture	door;
	t_texture	image;
	t_texture	minimap;
	t_ray		ray;

}	t_data;

int		checker(t_data *data, int i, int j);
int		check_input(int argc, char **argv, t_data *data);
int		check_map(t_data *data, int i, char *tmp, int cond);
int		spaces_skipper(char *str, int start);
int		string_to_rgb(char *str, int i, int j, int counter);
int		check_lin(char *str, int i, int raw, t_data *data);
int		color_checker(char *str, int i);
int		comparer(char *tmp, t_data *data, int i);
void	free_matrix(char **matrix);
char	**matrix_crusher(char **matrix, char *str, int i);
void	freerer(t_data *data);
void	initializer(t_data *data);
void	initialize_texture(t_data *data);
int		list_free(t_data *data);
int		check_list(t_data *data, char *str, int len);
int		last_check(t_data *data, int i);
int		find_player(t_data *data, int i, int j);
void	find_direction(t_data *data);
int		check_text_path(t_data *data);
void	image_destroyer(t_data *data, void *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_pixel(t_texture *img, int x, int y);
void	draw_vertical(t_data *data, int start, int end, int color);
void	draw_c_and_f(t_data *data);
int		create_images(t_data *data);
void	raycasting(t_data *data);
void	calcs(t_data *data);
void	get_step(t_data *data);
void	wall_distance(t_data *data);
void	dda(t_data *data);
void	calculate_wall_x(t_data *data);
void	draw_textures(t_data *data);
void	draw_north(t_data *data);
void	draw_east(t_data *data);
void	draw_west(t_data *data);
void	draw_south(t_data *data);
void	draw_door(t_data *data);
void	open_door(t_data *data);
void	get_start_end(t_data *data);
void	turn_right(t_data *data, double rotate);
void	turn_left(t_data *data, double rotate);
void	turn_mouse(t_data *data);
void	check_movement(t_data *data);
void	add_minimap(t_data *data, double i, double j);
void	add_pixel_repeat(t_data *data, int x, int y, int color);
void	initialize_animation(t_data *data);
void	animations_addr(t_data *data);
void	print_ani(t_data *data, int y, int x, int i);
int		nullifiereee(void *data);
int		keys_control_movements(int kc, t_data *data);
int		keys_control_released(int kc, t_data *data);
void	keys_movements(int kc, t_data *data);
int		keys_control(int kc, t_data *data);
int		close_game(void *data);
void	print_map(t_data *data);
void	mlx_handler(t_data *data);
void	move_forward(t_data *data);
void	move_backwards(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);

#endif