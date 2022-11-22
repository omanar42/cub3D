/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:25:07 by omanar            #+#    #+#             */
/*   Updated: 2022/11/22 15:11:07 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	draw_2d(t_cub *cub, int x_pos, int y_pos, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < 12)
	{
		i = 0;
		while (i < 12)
		{
			if (dbp(WINW - 200 + 106 - 10 + 6, 112, x_pos + i, y_pos + j) < 90)
				my_mlx_pixel_put(cub->cub, x_pos + i, y_pos + j, color);
			i++;
		}
		j++;
	}
}

void	render_line(t_cub *cub, int sx, int sy, int endx, int endy)
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
		my_mlx_pixel_put(cub->cub, pixelx, pixely, 0x00292a);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	generate_2d_player(t_cub *cub)
{
	int	x_pos;
	int	y_pos;

	x_pos = WINW - 200 + 106 - 10;
	y_pos = 106;
	draw_2d(cub, x_pos, y_pos, 0x00292a);
	render_line(cub, x_pos + 6, y_pos + 6,
		x_pos + 6 + (cos(cub->player->angle) * 20),
		y_pos + 6 + (sin(cub->player->angle) * 20));
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
		x_pos = WINW - 200;
		x_index = floor(cub->player->x / TILE_SIZE) - 8;
		while (x_index < floor(cub->player->x / TILE_SIZE) + 8)
		{
			if (x_index < 0 || y_index < 0 || y_index >= cub->data->height)
				draw_2d(cub, x_pos, y_pos, 0x5A5A5A);
			else if (x_index >= (int)ft_strlen(cub->data->map[y_index]))
				draw_2d(cub, x_pos, y_pos, 0x5A5A5A);
			else
			{
				if (cub->data->map[y_index][x_index] == '1')
					draw_2d(cub, x_pos, y_pos, 0x5A5A5A);
				else if (cub->data->map[y_index][x_index] == 'D')
					draw_2d(cub, x_pos, y_pos, 0x8B4000);
				else
					draw_2d(cub, x_pos, y_pos, cub->data->floor);
			}
			x_pos += 12;
			x_index++;
		}
		y_pos += 12;
		y_index++;
	}
}
