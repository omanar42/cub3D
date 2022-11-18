/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:43:53 by omanar            #+#    #+#             */
/*   Updated: 2022/11/17 21:04:46 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

float	normalize_angle(float angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

float	dbp(float x1, float y1, float x2, float y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

float	get_distance(t_cub *cub, t_cast *dir)
{
	if (dir->wall_hit)
		return (dbp(cub->player->x, cub->player->y,
				dir->xhit, dir->yhit));
	else
		return (INT_MAX);
}

void	get_touch_horz(t_cub *cub, t_cast *horz, int i)
{
	while (horz->touch_x >= 0
		&& horz->touch_x <= cub->data->map_width
		&& horz->touch_y >= 0
		&& horz->touch_y <= cub->data->map_height)
	{
		if (!can_move(cub->data, horz->touch_x,
				horz->touch_y - (cub->rays[i].is_facing_up == TRUE)))
		{
			horz->wall_hit = TRUE;
			horz->xhit = horz->touch_x;
			horz->yhit = horz->touch_y;
			break ;
		}
		else
		{
			horz->touch_x += horz->xstep;
			horz->touch_y += horz->ystep;
		}
	}
}

void	get_touch_vert(t_cub *cub, t_cast	*vert, int i)
{
	while (vert->touch_x >= 0
		&& vert->touch_x <= cub->data->map_width
		&& vert->touch_y >= 0
		&& vert->touch_y <= cub->data->map_height)
	{
		if (!can_move(cub->data,
				vert->touch_x - (cub->rays[i].is_facing_left == TRUE),
				vert->touch_y))
		{
			vert->wall_hit = TRUE;
			vert->xhit = vert->touch_x;
			vert->yhit = vert->touch_y;
			break ;
		}
		else
		{
			vert->touch_x += vert->xstep;
			vert->touch_y += vert->ystep;
		}
	}
}
