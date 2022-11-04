/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:25:28 by omanar            #+#    #+#             */
/*   Updated: 2022/11/04 21:27:00 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void draw_line(t_cub *cub, int endx, int endy)
{
	int		pixels;
	float	pixelx;
	float	pixely;
	float	deltax;
	float	deltay;

    deltax = endx - cub->player->x;
    deltay = endy - cub->player->y;
    pixels = sqrt((deltax * deltax) + (deltay * deltay));
    deltax /= pixels;
    deltay /= pixels;
    pixelx = cub->player->x;
    pixely = cub->player->y;
	while (pixels)
	{
		my_mlx_pixel_put(cub->img, round(pixelx) * MINIMAP_SCALE_FACTOR,
			round(pixely) * MINIMAP_SCALE_FACTOR, 0x00FFFFFF);
        pixelx += deltax;
        pixely += deltay;
		pixels--;
    }
}

void	set_cub(t_cub *cub)
{
	cub->img->img = mlx_new_image(cub->mlxdata->mlx, WINW
			* MINIMAP_SCALE_FACTOR, WINH * MINIMAP_SCALE_FACTOR);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	cub->img->width = WINW * MINIMAP_SCALE_FACTOR;
	cub->img->height = WINH * MINIMAP_SCALE_FACTOR;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if ((x + i) * MINIMAP_SCALE_FACTOR < img->width && (y + j) * MINIMAP_SCALE_FACTOR < img->height)
				my_mlx_pixel_put(img, (x + i) * MINIMAP_SCALE_FACTOR, (y + j) * MINIMAP_SCALE_FACTOR, color);
			j++;
		}
		i++;
	}
}

void	set_player(t_cub *cub)
{
	my_mlx_pixel_put(cub->img, cub->player->x * MINIMAP_SCALE_FACTOR,
		cub->player->y * MINIMAP_SCALE_FACTOR, 0x00203FFF);
	draw_line(cub, cub->player->x + (cos(cub->player->angle) * 30),
		cub->player->y + (sin(cub->player->angle) * 30));
}

int	can_move(char **map, float x, float y)
{
	int	x_index;
	int	y_index;

	if (x < 0 || x > WINW || y < 0 || y > WINH)
		return (FALSE);
	x_index = floor(x / TILE_SIZE);
	y_index = floor(y / TILE_SIZE);
	if (map[y_index][x_index] != '1')
		return (TRUE);
	return (FALSE);
}

void	move_player(t_cub *cub)
{
	float	newx;
	float	newy;
	float	ver_step;
	float	hor_step;

	newx = 0;
	newy = 0;
	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	ver_step = cub->player->ver_dir * cub->player->movespeed;
	hor_step = cub->player->hor_dir * cub->player->movespeed;
	
	newx += (cos(cub->player->angle) * ver_step);
	newx += (cos(cub->player->angle + M_PI / 2) * hor_step);
	newy += (sin(cub->player->angle) * ver_step);
	newy += (sin(cub->player->angle + M_PI / 2) * hor_step);

	if (can_move(cub->data->map, cub->player->x + newx, cub->player->y))
		cub->player->x += newx;
	if (can_move(cub->data->map, cub->player->x, cub->player->y + newy))
		cub->player->y += newy;
}

void	cast_ray(t_cub *cub, float	ray_angle)
{
	draw_line(cub, cub->player->x + (cos(ray_angle) * 30),
		cub->player->y + (sin(ray_angle) * 30));
}

void	set_rays(t_cub *cub)
{
	int		i;
	float	ray_angle;

	ray_angle = cub->player->angle - (cub->player->fov / 2);

	i = -1;
	while (++i < 1)
	{
		cast_ray(cub, ray_angle);
		ray_angle += cub->player->fov / WINW;
	}
}

void	update(t_cub *cub) 
{
	set_map(cub);
	set_player(cub);
	move_player(cub);
	set_rays(cub);
}

void	render(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlxdata->mlx,
		cub->mlxdata->win, cub->img->img,
		(WINW - (WINW * MINIMAP_SCALE_FACTOR) - 10) * 0,
		10 * 0);
	// draw_rays(cub);
	// draw_sprites(cub);
}

// void	draw() 
// {
// 	update();
// 	render();
// }