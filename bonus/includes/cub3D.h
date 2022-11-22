/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:08 by omanar            #+#    #+#             */
/*   Updated: 2022/11/22 17:51:40 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <libft.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <get_next_line.h>
# include "../libs/minilibx/mlx.h"

// ----------------------------  KEYCODES  ---------------------------- //

# define ESC_KEY 53
# define A_KEY 0
# define D_KEY 2
# define W_KEY 13
# define S_KEY 1
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define UP_KEY 126
# define DOWN_KEY 125
# define CNTR_KEY 256
# define SPACE_KEY 49

// ----------------------------  CONSTANTS  ---------------------------- //

# define TRUE 1
# define FALSE 0
# define WINW 1280
# define WINH 720
# define TILE_SIZE 32
# define MINIFICATION 0.3

enum e_TOKENS{
	TOKEN_NO,
	TOKEN_SO,
	TOKEN_WE,
	TOKEN_EA,
	TOKEN_DR,
	TOKEN_F,
	TOKEN_C,
	TOKEN_MAP,
	TOKEN_ERROR,
};

typedef struct s_ints {
	int	x_coord;
	int	y_coord;
	int	x_index;
	int	y_index;
}	t_ints;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player {
	float	x;
	float	y;
	float	angle;
	float	fov;
	int		ver_dir;
	int		hor_dir;
	float	movespeed;
	int		turndir;
	float	turnspeed;
	float	dist_proj_plane;
}	t_player;

typedef struct s_wall
{
	int		dft;
	int		tex_x;
	int		tex_y;
	float	top_pixel;
	float	bottom_pixel;
	float	wall_height;
	float	correct_distance;
}	t_wall;

typedef struct s_cast
{
	float	xstep;
	float	ystep;
	float	xhit;
	float	yhit;
	float	touch_x;
	float	touch_y;
	float	hit_distance;
	int		wall_hit;
	int		is_facing_door;
}	t_cast;

typedef struct s_ray
{
	float	angle;
	float	xhit;
	float	yhit;
	float	distance;
	int		hit_vertical;
	int		is_facing_up;
	int		is_facing_down;
	int		is_facing_left;
	int		is_facing_right;
	int		is_facing_door;
}	t_ray;

typedef struct s_sprites {
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;
	t_img	*dr;
}	t_sprites;

typedef struct s_data {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*dr;
	char	**map;
	int		floor;
	int		ceiling;
	int		width;
	int		height;
	int		map_width;
	int		map_height;
}	t_data;

typedef struct s_cub {
	int			mouse;
	void		*mlx;
	void		*win;
	t_img		*cub;
	t_ray		*rays;
	t_data		*data;
	t_player	*player;
	t_sprites	*sprites;
}	t_cub;

// ----------------------------  PARSING  ---------------------------- //

void	parsing(t_cub *cub, char *str);
void	file_checker(char *str, char *extension);
void	file_parsing(t_cub *cub, int fd);
int		line_parsing(t_cub *cub, char *line);
void	color_parsing(t_cub *cub, char *line, int token, int i);
void	texture_parsing(t_cub *cub, char *line, int token, int i);
void	map_parsing(t_cub *cub, char *line, int fd);

// --------------------------  PARSING UTILS ------------------------- //

void	skipe_spaces(char *s, int *i);
int		is_map(char *line);
int		check_name(char *name);
int		argslen(char **args);
void	free_loop(char **args);
char	**advanced_add(char **strs, char *arg);
void	if_something_missing(t_cub *cub);
void	add_player(t_cub *cub, char **map, int y, int x);
void	check_borders(char **map);
void	check_lenght(char *line);
int		set_lines(t_cub *cub);
int		is_player(char c);
void	checker(t_cub *cub, char **map);
void	check_borders(char **map);

// --------------------------  INITIALIZING  ------------------------- //

void	init_data(t_cub *cub);
void	initialize(t_cub *cub);
void	player_config(t_cub *cub);
void	init_window(t_cub *cub);
void	init_textures(t_cub *cub);

// -----------------------------  SETUP  ----------------------------- //

void	setup(t_cub *cub);
void	set_hooks(t_cub *cub);
void	set_cub(t_cub *cub);
void	update(t_cub *cub);
void	render(t_cub *cub);

// ---------------------------  RENDERING  --------------------------- //

void	generate_3d_projection(t_cub *cub);
void	render_3d_wall(t_cub *cub, int i, t_wall wall);
void	draw_wall(t_cub *cub, t_wall wall, t_img *texture, int i);

// --------------------------  RAYCASTING  --------------------------- //

void	set_rays(t_cub *cub);
void	cast_ray(t_cub *cub, float ray_angle, int i);
void	fill_ray(t_ray *ray, t_cast *dir, int boolean);
t_cast	*cast_vert(t_cub *cub, float ray_angle, int i);
t_cast	*cast_horz(t_cub *cub, float ray_angle, int i);

// ------------------------  RAYCASTING UTILS ------------------------ //

float	normalize_angle(float angle);
float	get_distance(t_cub *cub, t_cast *dir);
float	dbp(float x1, float y1, float x2, float y2);
void	get_touch_horz(t_cub *cub, t_cast *horz, int i);
void	get_touch_vert(t_cub *cub, t_cast	*vert, int i);

// -----------------------------  HOOKS ------------------------------ //

int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);
int		distroy_event(int keycode, t_cub *cub);
int		loop_hook(t_cub *cub);

// -----------------------------  UTILS ------------------------------ //

t_img	*new_sprite(void *mlx, char *path);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	move_player(t_cub *cub);
int		can_move(t_data *data, float x, float y);
int		can_ray_move(t_data *data, float x, float y);
float	get_width(char *line);

// -----------------------------  MOUSE ------------------------------ //

int		mouse_move(t_cub *cub);
int		mouse_hook(int button, int x, int y, t_cub *cub);
int		mouse_move(t_cub *cub);
void	control_hundler(t_cub *cub);

// -----------------------------  DOOR ------------------------------- //

int		is_facing_door(t_data *data, float x, float y);
void	change_door(t_data *data, int x, int y);
void	door_hundler(t_cub *cub);
void	fill_dir(t_cast *dir);

// -----------------------------  MINIMAP ------------------------------- //

void	generate_2d_map(t_cub *cub);
void	draw_minimap(t_cub *cub, t_ints ints);
void	draw_2d(t_cub *cub, t_ints ints, int color);
void	generate_2d_player(t_cub *cub);
void	render_line(t_cub *cub, int endx, int endy);

// -----------------------------  EXITS  ----------------------------- //

void	exit_str(char *str);
void	exit_success(char *str);
void	exit_error(char *str, char *err);
void	exit_strerr(char *str, int err);

#endif
