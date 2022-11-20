/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:54:46 by omanar            #+#    #+#             */
/*   Updated: 2022/11/20 17:00:09 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	fill_dir(t_cast *dir)
{
	dir->is_facing_door = TRUE;
	dir->wall_hit = TRUE;
	dir->xhit = dir->touch_x;
	dir->yhit = dir->touch_y;
}

int	is_facing_door(t_data *data, float x, float y)
{
	int	x_index;
	int	y_index;

	x_index = floor(x / TILE_SIZE);
	y_index = floor(y / TILE_SIZE);
	if (y < 0 || y > data->map_height)
		return (FALSE);
	if (x < 0 || x > get_width(data->map[y_index]))
		return (FALSE);
	if (data->map[y_index][x_index] == 'D')
		return (TRUE);
	return (FALSE);
}

void	change_door(t_data *data, int x, int y)
{
	int	x_index;
	int	y_index;

	x_index = floor(x / TILE_SIZE);
	y_index = floor(y / TILE_SIZE);
	if (y < 0 || y > data->map_height)
		return ;
	if (x < 0 || x > get_width(data->map[y_index]))
		return ;
	if (data->map[y_index][x_index] == 'D')
		data->map[y_index][x_index] = 'O';
	else if (data->map[y_index][x_index] == 'O')
		data->map[y_index][x_index] = 'D';
}

void	door_hundler(t_cub *cub)
{
	float	xstep;
	float	ystep;

	xstep = 0;
	ystep = 0;
	xstep += (cos(cub->player->angle) * TILE_SIZE);
	ystep += (sin(cub->player->angle) * TILE_SIZE);
	xstep += cub->player->x;
	ystep += cub->player->y;
	change_door(cub->data, xstep, ystep);
}
