/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:41:43 by omanar            #+#    #+#             */
/*   Updated: 2022/11/09 22:55:06 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_cast	*cast_horz(t_cub *cub, float ray_angle, int i)
{
	t_cast	*horz;

	horz = (t_cast *)malloc(sizeof(t_cast));
	horz->found_wall_hit = FALSE;
	horz->wall_hit_x = 0;
	horz->wall_hit_y = 0;
	horz->next_touch_y = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (cub->rays[i].is_ray_facing_down)
		horz->next_touch_y += TILE_SIZE;
	horz->next_touch_x = cub->player->x
		+ (horz->next_touch_y - cub->player->y) / tan(ray_angle);
	horz->ystep = TILE_SIZE;
	if (cub->rays[i].is_ray_facing_up)
		horz->ystep *= -1;
	horz->xstep = TILE_SIZE / tan(ray_angle);
	if (cub->rays[i].is_ray_facing_left && horz->xstep > 0)
		horz->xstep *= -1;
	if (cub->rays[i].is_ray_facing_right && horz->xstep < 0)
		horz->xstep *= -1;
	next_touch_horz(cub, horz, i);
	return (horz);
}

t_cast	*cast_vert(t_cub *cub, float ray_angle, int i)
{
	t_cast	*vert;

	vert = (t_cast *)malloc(sizeof(t_cast));
	vert->found_wall_hit = FALSE;
	vert->wall_hit_x = 0;
	vert->wall_hit_y = 0;
	vert->next_touch_x = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	if (cub->rays[i].is_ray_facing_right)
		vert->next_touch_x += TILE_SIZE;
	vert->next_touch_y = cub->player->y
		+ (vert->next_touch_x - cub->player->x) * tan(ray_angle);
	vert->xstep = TILE_SIZE;
	if (cub->rays[i].is_ray_facing_left)
		vert->xstep *= -1;
	vert->ystep = TILE_SIZE * tan(ray_angle);
	if (cub->rays[i].is_ray_facing_up && vert->ystep > 0)
		vert->ystep *= -1;
	if (cub->rays[i].is_ray_facing_down && vert->ystep < 0)
		vert->ystep *= -1;
	next_touch_vert(cub, vert, i);
	return (vert);
}

void	fill_ray(t_ray *ray, t_cast *dir, int boolean)
{
	ray->distance = dir->hit_distance;
	ray->wall_hit_x = dir->wall_hit_x;
	ray->wall_hit_y = dir->wall_hit_y;
	ray->was_hit_vertical = boolean;
}

void	cast_ray(t_cub *cub, float ray_angle, int i)
{
	t_cast	*horz;
	t_cast	*vert;

	ray_angle = normalize_angle(ray_angle);
	cub->rays[i].is_ray_facing_down = (ray_angle > 0 && ray_angle < M_PI);
	cub->rays[i].is_ray_facing_up = !cub->rays[i].is_ray_facing_down;
	cub->rays[i].is_ray_facing_right = (ray_angle < 0.5 * M_PI
			|| ray_angle > 1.5 * M_PI);
	cub->rays[i].is_ray_facing_left = !cub->rays[i].is_ray_facing_right;
	horz = cast_horz(cub, ray_angle, i);
	vert = cast_vert(cub, ray_angle, i);
	horz->hit_distance = get_distance(cub, horz);
	vert->hit_distance = get_distance(cub, vert);
	if (vert->hit_distance < horz->hit_distance)
		fill_ray(&cub->rays[i], vert, TRUE);
	else
		fill_ray(&cub->rays[i], horz, FALSE);
	if (cub->rays[i].distance == 0)
		cub->rays[i].distance = 0.0001;
	cub->rays[i].angle = ray_angle;
	free(horz);
	free(vert);
}

void	set_rays(t_cub *cub)
{
	int		i;
	float	ray_angle;

	i = -1;
	while (++i < WINW)
	{
		ray_angle = cub->player->angle
			+ atan((i - WINW / 2) / cub->player->dist_proj_plane);
		cast_ray(cub, ray_angle, i);
	}
}
