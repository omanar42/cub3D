/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:43:53 by omanar            #+#    #+#             */
/*   Updated: 2022/11/09 22:55:10 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

float	normalize_angle(float angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

float	get_distance(t_cub *cub, t_cast *dir)
{
	if (dir->found_wall_hit)
		return (distance_between_points(cub->player->x,
				cub->player->y, dir->wall_hit_x, dir->wall_hit_y));
	else
		return (INT_MAX);
}

void	next_touch_horz(t_cub *cub, t_cast *horz, int i)
{
	while (horz->next_touch_x >= 0
		&& horz->next_touch_x <= cub->data->window_width
		&& horz->next_touch_y >= 0
		&& horz->next_touch_y <= cub->data->window_height)
	{
		if (!can_move(cub->data, horz->next_touch_x,
				horz->next_touch_y - (cub->rays[i].is_ray_facing_up == TRUE)))
		{
			horz->found_wall_hit = TRUE;
			horz->wall_hit_x = horz->next_touch_x;
			horz->wall_hit_y = horz->next_touch_y;
			break ;
		}
		else
		{
			horz->next_touch_x += horz->xstep;
			horz->next_touch_y += horz->ystep;
		}
	}
}

void	next_touch_vert(t_cub *cub, t_cast	*vert, int i)
{
	while (vert->next_touch_x >= 0
		&& vert->next_touch_x <= cub->data->window_width
		&& vert->next_touch_y >= 0
		&& vert->next_touch_y <= cub->data->window_height)
	{
		if (!can_move(cub->data,
				vert->next_touch_x - (cub->rays[i].is_ray_facing_left == TRUE),
				vert->next_touch_y))
		{
			vert->found_wall_hit = TRUE;
			vert->wall_hit_x = vert->next_touch_x;
			vert->wall_hit_y = vert->next_touch_y;
			break ;
		}
		else
		{
			vert->next_touch_x += vert->xstep;
			vert->next_touch_y += vert->ystep;
		}
	}
}
