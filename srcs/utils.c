/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:25:28 by omanar            #+#    #+#             */
/*   Updated: 2022/11/09 19:07:21 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	draw_line(t_cub *cub, int endx, int endy)
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
		my_mlx_pixel_put(cub->img, round(pixelx) * MINIFICATION,
			round(pixely) * MINIFICATION, 0x00FFFFFF);
		pixelx += deltax;
		pixely += deltay;
		pixels--;
	}
}

void	set_cub(t_cub *cub)
{
	cub->img->img = mlx_new_image(cub->mlxdata->mlx, cub->data->window_width
			* MINIFICATION, cub->data->window_height * MINIFICATION);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	cub->img->width = cub->data->window_width * MINIFICATION;
	cub->img->height = cub->data->window_height * MINIFICATION;
	cub->cub->img = mlx_new_image(cub->mlxdata->mlx, WINW, WINH);
	cub->cub->addr = mlx_get_data_addr(cub->cub->img, &cub->cub->bits_per_pixel,
			&cub->cub->line_length, &cub->cub->endian);
	cub->cub->width = WINW;
	cub->cub->height = WINH;
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
			if ((x + i) * MINIFICATION < img->width
				&& (y + j) * MINIFICATION < img->height)
				my_mlx_pixel_put(img, (x + i) * MINIFICATION,
					(y + j) * MINIFICATION, color);
			j++;
		}
		i++;
	}
}

void	set_player(t_cub *cub)
{
	my_mlx_pixel_put(cub->img, cub->player->x * MINIFICATION,
		cub->player->y * MINIFICATION, 0x00203FFF);
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
	if (y < 0 || y > data->window_height)
		return (FALSE);
	if (x < 0 || x > get_width(data->map[y_index]))
		return (FALSE);
	if (data->map[y_index][x_index] != '1')
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
	if (can_move(cub->data, cub->player->x + newx, cub->player->y))
		cub->player->x += newx;
	if (can_move(cub->data, cub->player->x, cub->player->y + newy))
		cub->player->y += newy;
}

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

void	draw_rays(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < WINW)
		draw_line(cub, cub->rays[i].wall_hit_x, cub->rays[i].wall_hit_y);
}

void	draw_3d(t_cub *cub, t_wall wall, t_img *texture, int i)
{
	int		j;
	char	*dst;

	j = 0;
	while (j < wall.top_pixel)
		my_mlx_pixel_put(cub->cub, i, j++, cub->data->ceiling);
	while (j < wall.bottom_pixel)
	{
		wall.dft = j + (wall.strip_height / 2) - (WINH / 2);
		wall.tex_y = (int)(wall.dft
				* (float)texture->height / wall.strip_height)
			% texture->height;
		dst = texture->addr + wall.tex_y * texture->line_length
			+ wall.tex_x * (texture->bits_per_pixel / 8);
		my_mlx_pixel_put(cub->cub, i, j++, *(unsigned int *)dst);
	}
	while (j < WINH)
		my_mlx_pixel_put(cub->cub, i, j++, cub->data->floor);
}

void	render_3d_wall(t_cub *cub, int i, t_wall wall)
{
	t_img	*texture;

	if (cub->rays[i].was_hit_vertical)
	{
		if (cub->rays[i].is_ray_facing_left)
			texture = cub->assets->ea;
		else
			texture = cub->assets->we;
		wall.tex_x = (int)(cub->rays[i].wall_hit_y
				* texture->width / TILE_SIZE) % texture->width;
	}
	else
	{
		if (cub->rays[i].is_ray_facing_up)
			texture = cub->assets->no;
		else
			texture = cub->assets->so;
		wall.tex_x = (int)(cub->rays[i].wall_hit_x
				* texture->width / TILE_SIZE) % texture->width;
	}
	draw_3d(cub, wall, texture, i);
}

void	generate_3d_projection(t_cub *cub)
{
	int		i;
	t_wall	wall;

	i = -1;
	while (++i < WINW)
	{
		wall.correct_distance = cub->rays[i].distance
			* cos(cub->rays[i].angle - cub->player->angle);
		cub->player->dist_proj_plane = (WINW / 2) / tan(cub->player->fov / 2);
		wall.strip_height = (TILE_SIZE / wall.correct_distance)
			* cub->player->dist_proj_plane;
		wall.top_pixel = (WINH / 2) - (wall.strip_height / 2);
		if (wall.top_pixel < 0)
			wall.top_pixel = 0;
		wall.bottom_pixel = (WINH / 2) + (wall.strip_height / 2);
		if (wall.bottom_pixel > WINH)
			wall.bottom_pixel = WINH;
		render_3d_wall(cub, i, wall);
	}
}

void	update(t_cub *cub)
{
	set_map(cub);
	set_player(cub);
	move_player(cub);
	set_rays(cub);
	draw_rays(cub);
	generate_3d_projection(cub);
}

void	render(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlxdata->mlx,
		cub->mlxdata->win, cub->cub->img, 0, 0);
	// mlx_put_image_to_window(cub->mlxdata->mlx,
	// 	cub->mlxdata->win, cub->img->img,
	// 	(WINW - (cub->data->window_width * MINIFICATION) - 10),
	// 	10);
}
