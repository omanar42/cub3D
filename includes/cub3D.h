/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:08 by omanar            #+#    #+#             */
/*   Updated: 2022/11/09 23:40:40 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <limits.h>
# include <math.h>
# include <libft.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <get_next_line.h>

# define ESC_KEY 53
# define A_KEY 0
# define D_KEY 2
# define W_KEY 13
# define S_KEY 1
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define UP_KEY 126
# define DOWN_KEY 125

# define TRUE 1
# define FALSE 0
# define TILE_SIZE 32
# define WINW 1280
# define WINH 720

# define MINIFICATION 0.3

enum {
	DIR_NO,
	DIR_SO,
	DIR_WE,
	DIR_EA,
}	e_dir;

enum {
	TOKEN_NO,
	TOKEN_SO,
	TOKEN_WE,
	TOKEN_EA,
	TOKEN_F,
	TOKEN_C,
	TOKEN_MAP,
	TOKEN_ERROR,
}	e_type;

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
	float	strip_height;
	float	correct_distance;
}	t_wall;

typedef struct s_cast
{
	float	xstep;
	float	ystep;
	float	wall_hit_x;
	float	wall_hit_y;
	float	next_touch_x;
	float	next_touch_y;
	float	hit_distance;
	int		found_wall_hit;
}	t_cast;

typedef struct s_ray
{
	float	angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
}	t_ray;

typedef struct s_mlxdata {
	void	*mlx;
	void	*win;
	void	*no_img;
	void	*so_img;
	void	*we_img;
	void	*ea_img;
}	t_mlxdata;

typedef struct s_assets {
	int		width;
	int		height;
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;
}	t_assets;

typedef struct s_data {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
	int		width;
	int		height;
	int		window_width;
	int		window_height;
	char	**map;
}	t_data;

typedef struct s_cub {
	t_img		*img;
	t_img		*cub;
	t_ray		*rays;
	t_data		*data;
	t_assets	*assets;
	t_player	*player;
	t_mlxdata	*mlxdata;
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
void	check_border(t_cub *cub, char **map);

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
void	draw_3d(t_cub *cub, t_wall wall, t_img *texture, int i);

// ---------------------------  RAYCASTING  --------------------------- //

void	set_rays(t_cub *cub);
void	cast_ray(t_cub *cub, float ray_angle, int i);
void	fill_ray(t_ray *ray, t_cast *dir, int boolean);
t_cast	*cast_vert(t_cub *cub, float ray_angle, int i);
t_cast	*cast_horz(t_cub *cub, float ray_angle, int i);

// ---------------------------  RAYCASTING UTILS --------------------------- //

float	normalize_angle(float angle);
float	get_distance(t_cub *cub, t_cast *dir);
float	distance_between_points(float x1, float y1, float x2, float y2);
void	next_touch_horz(t_cub *cub, t_cast *horz, int i);
void	next_touch_vert(t_cub *cub, t_cast	*vert, int i);

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
float	get_width(char *line);

// -----------------------------  EXITS  ----------------------------- //

void	exit_str(char *str);
void	exit_success(char *str);
void	exit_error(char *str, char *err);
void	exit_strerr(char *str, int err);

#endif
