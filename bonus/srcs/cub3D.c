/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:31 by omanar            #+#    #+#             */
/*   Updated: 2022/11/21 23:00:46 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->win = mlx_new_window(cub->mlx,
			WINW, WINH, "Cub3D");
	if (!cub->win)
		exit_error("mlx_new_window", "Error creating MLX window");
	cub->rays = malloc(sizeof(t_ray) * WINW + 1);
	if (!cub->rays)
		exit_strerr("malloc", errno);
}


void	draw_floor(t_cub *cub, int x_pos, int y_pos)
{
	int i;
	int j;

	j = 0;
	while (j < 12)
	{
		i = 0;
		while (i < 12)
		{
			if (dbp(112, 112, x_pos + i, y_pos + j) < 90)
				my_mlx_pixel_put(cub->cub, x_pos + i, y_pos + j, cub->data->floor);
			i++;
		}
		j++;
	}
}

void	draw_wall2d(t_cub *cub, int x_pos, int y_pos, int color)
{
	int i;
	int j;

	j = 0;
	while (j < 12)
	{
		i = 0;
		while (i < 12)
		{
			if (dbp(112, 112, x_pos + i, y_pos + j) < 90)
				my_mlx_pixel_put(cub->cub, x_pos + i, y_pos + j, color);
			i++;
		}
		j++;
	}
}

void	generate_2d_map(t_cub *cub)
{
	int	x_index;
	int	y_index;
	int	x_pos;
	int	y_pos;

	y_pos = 10;
	y_index = floor(cub->player->y / TILE_SIZE) - 8;
	while (y_index < floor(cub->player->y / TILE_SIZE) + 8)
	{
		x_pos = 10;
		x_index = floor(cub->player->x / TILE_SIZE) - 8;
		while (x_index < floor(cub->player->x / TILE_SIZE) + 8)
		{
			if (x_index < 0 || y_index < 0 || x_index >= cub->data->width
				|| y_index >= cub->data->height)
				draw_wall2d(cub, x_pos, y_pos, 0x5A5A5A);
			else
			{
				if (cub->data->map[y_index][x_index] == '1')
					draw_wall2d(cub, x_pos, y_pos, 0x5A5A5A);
				else
					draw_floor(cub, x_pos, y_pos);
			}
			x_pos += 12;
			x_index++;
		}
		y_pos += 12;
		y_index++;
	}
}

void	render_line(t_cub *cub, int sx, int sy, int endx, int endy, int color)
{
	int		pixels;
	double	pixelx;
	double	pixely;
	double	deltax;
	double	deltay;

	deltax = endx - sx;
	deltay = endy - sy;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = sx;
	pixely = sy;
	while (pixels)
	{
		my_mlx_pixel_put(cub->cub, pixelx, pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	generate_2d_player(t_cub *cub)
{
	int	x_pos;
	int	y_pos;

	x_pos = 106;
	y_pos = 106;
	draw_wall2d(cub, x_pos, y_pos, 0x00292a);
	render_line(cub, x_pos + 6, y_pos + 6, x_pos + 6 + (cos(cub->player->angle) * 20),
		y_pos + 6 + (sin(cub->player->angle) * 20), 0x00292a);
}

void	update(t_cub *cub)
{
	move_player(cub);
	set_rays(cub);
	generate_3d_projection(cub);
	generate_2d_map(cub);
	generate_2d_player(cub);
	mouse_move(cub);
}

void	render(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx,
		cub->win, cub->cub->img, 0, 0);
}

int	loop_hook(t_cub *cub)
{
	update(cub);
	render(cub);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_success("Usage: ./cub3D <map.cub>");
	cub = (t_cub *)malloc(sizeof(t_cub));
	parsing(cub, av[1]);
	init_window(cub);
	init_textures(cub);
	setup(cub);
	mlx_loop_hook(cub->mlx, loop_hook, cub);
	mlx_loop(cub->mlx);
	return (0);
}
