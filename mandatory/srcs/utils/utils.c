/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:25:28 by omanar            #+#    #+#             */
/*   Updated: 2022/11/18 21:46:16 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float	get_width(char *line)
{
	int	len;

	len = ft_strlen(line);
	return (len * TILE_SIZE);
}

int	can_move(t_data *data, float x, float y)
{
	int	x_index;
	int	y_index;

	x_index = floor(x / TILE_SIZE);
	y_index = floor(y / TILE_SIZE);
	if (y < 0 || y > data->map_height)
		return (FALSE);
	if (x < 0 || x > get_width(data->map[y_index]))
		return (FALSE);
	if (data->map[y_index][x_index] != '1')
		return (TRUE);
	return (FALSE);
}

void	move_player(t_cub *cub)
{
	float	xstep;
	float	ystep;
	float	ver_step;
	float	hor_step;

	xstep = 0;
	ystep = 0;
	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	ver_step = cub->player->ver_dir * cub->player->movespeed;
	hor_step = cub->player->hor_dir * (cub->player->movespeed - 2);
	xstep += (cos(cub->player->angle) * ver_step);
	xstep += (cos(cub->player->angle + M_PI / 2) * hor_step);
	ystep += (sin(cub->player->angle) * ver_step);
	ystep += (sin(cub->player->angle + M_PI / 2) * hor_step);
	xstep *= 5;
	ystep *= 5;
	if (can_move(cub->data, cub->player->x + xstep, cub->player->y))
		cub->player->x += xstep / 5;
	if (can_move(cub->data, cub->player->x, cub->player->y + ystep))
		cub->player->y += ystep / 5;
}

void	setup(t_cub *cub)
{
	set_hooks(cub);
	set_cub(cub);
}
