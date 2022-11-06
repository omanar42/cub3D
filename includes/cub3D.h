/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:08 by omanar            #+#    #+#             */
/*   Updated: 2022/11/06 12:36:46 by omanar           ###   ########.fr       */
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

# define MINIMAP_SCALE_FACTOR 0.5

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
}	t_player;

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
	int			run;
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
void	file_checker(char *str);
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

// -----------------------------  SETUP  ----------------------------- //

void	set_cub(t_cub *cub);
void	my_pixel_put(t_img *img, int x, int y, int color);
void	update(t_cub *cub);
void	render(t_cub *cub);
void	set_map(t_cub *cub);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
// ---------------------------  RENDERING  --------------------------- //


// -----------------------------  HOOKS ------------------------------ //


// -----------------------------  UTILS ------------------------------ //


// -----------------------------  EXITS  ----------------------------- //
void	exit_str(char *str);
void	exit_success(char *str);
void	exit_error(char *str, char *err);
void	exit_strerr(char *str, int err);

#endif
