/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:25:07 by omanar            #+#    #+#             */
/*   Updated: 2022/11/22 21:56:27 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	render_line(t_cub *cub, int endx, int endy)
{
	int		pixels;
	double	pixelx;
	double	pixely;
	double	deltax;
	double	deltay;

	deltax = endx - 112;
	deltay = endy - 112;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = 112;
	pixely = 112;
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
	t_ints	ints;

	ints.x_coord = 106;
	ints.y_coord = 106;
	ints.y_index = 1;
	while (++ints.y_index < 10)
	{
		ints.x_index = 1;
		while (++ints.x_index < 10)
			my_mlx_pixel_put(cub->cub, ints.x_coord + ints.x_index,
				ints.y_coord + ints.y_index, 0x00292a);
	}
	render_line(cub,
		ints.x_coord + 6 + (cos(cub->player->angle) * 15),
		ints.y_coord + 6 + (sin(cub->player->angle) * 15));
}

void	draw_2d(t_cub *cub, t_ints ints, int color)
{
	int		i;
	int		j;
	float	radius;

	j = -1;
	while (++j < 12)
	{
		i = -1;
		while (++i < 12)
		{
			radius = dbp(112, 112, ints.x_coord + i, ints.y_coord + j);
			if (radius >= 85 && radius <= 88)
				my_mlx_pixel_put(cub->cub, ints.x_coord + i,
					ints.y_coord + j, 0x000000);
			else if (radius < 85)
				my_mlx_pixel_put(cub->cub, ints.x_coord + i,
					ints.y_coord + j, color);
		}
	}
}

void	draw_minimap(t_cub *cub, t_ints ints)
{
	if (ints.y_index < 0 || ints.y_index >= cub->data->height)
		draw_2d(cub, ints, 0x4b4b4b);
	else if (ints.x_index < 0
		|| ints.x_index >= (int)ft_strlen(cub->data->map[ints.y_index]))
		draw_2d(cub, ints, 0x4b4b4b);
	else
	{
		if (cub->data->map[ints.y_index][ints.x_index] == '1')
			draw_2d(cub, ints, 0x4b4b4b);
		else if (cub->data->map[ints.y_index][ints.x_index] == 'D')
			draw_2d(cub, ints, 0x8B4000);
		else if (cub->data->map[ints.y_index][ints.x_index] == 'O')
			draw_2d(cub, ints, 0x5A5A8B);
		else
			draw_2d(cub, ints, cub->data->floor);
	}
}

void	generate_2d_map(t_cub *cub)
{
	t_ints	ints;

	ints.y_coord = 10;
	ints.y_index = floor(cub->player->y / TILE_SIZE) - 8;
	while (ints.y_index < floor(cub->player->y / TILE_SIZE) + 8)
	{
		ints.x_coord = 10;
		ints.x_index = floor(cub->player->x / TILE_SIZE) - 8;
		while (ints.x_index < floor(cub->player->x / TILE_SIZE) + 8)
		{
			draw_minimap(cub, ints);
			ints.x_coord += 12;
			ints.x_index++;
		}
		ints.y_coord += 12;
		ints.y_index++;
	}
}
