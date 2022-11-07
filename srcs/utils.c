/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:25:28 by omanar            #+#    #+#             */
/*   Updated: 2022/11/07 12:29:16 by omanar           ###   ########.fr       */
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
	cub->img->img = mlx_new_image(cub->mlxdata->mlx, cub->data->window_width
			* MINIMAP_SCALE_FACTOR, cub->data->window_height * MINIMAP_SCALE_FACTOR);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	cub->img->width = cub->data->window_width * MINIMAP_SCALE_FACTOR;
	cub->img->height = cub->data->window_height * MINIMAP_SCALE_FACTOR;
	cub->cub->img = mlx_new_image(cub->mlxdata->mlx,
			WINW, WINH);
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
	// draw_line(cub, cub->player->x + (cos(cub->player->angle) * 30),
	// 	cub->player->y + (sin(cub->player->angle) * 30));
}

float 	get_width(char *line)
{
	int len;

	len = ft_strlen(line);
	return (len * TILE_SIZE);
}

int	can_move(t_data *data, float x, float y)
{
	int	x_index;
	int	y_index;

	x_index = floor(x / TILE_SIZE);
	y_index = floor(y / TILE_SIZE);
	if ( y < 0 || y > data->window_height)
		return (FALSE);
	if (x < 0 || x > get_width(data->map[y_index]))
		return (FALSE);
	// printf("x = %f, y= %f\n", x, y);
	// printf("x = %d, y= %d\n", x_index, y_index);
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

float get_distance(t_cub *cub, int wall_hit, float wall_hit_x, float wall_hit_y)
{
	if (wall_hit)
		return (distance_between_points(cub->player->x, cub->player->y, wall_hit_x, wall_hit_y));
	else
		return (INT_MAX);
}

void	cast_ray(t_cub *cub, float ray_angle, int i)
{
	ray_angle = normalize_angle(ray_angle);

	int is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	int is_ray_facing_up = !is_ray_facing_down;

	int is_ray_facing_right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
	int is_ray_facing_left = !is_ray_facing_right;

	float xintercept;
	float yintercept;

	float xstep;
	float ystep;

	(void)i;
	int found_horz_wall_hit = FALSE;
	float horz_wall_hit_x = 0;
	float horz_wall_hit_y = 0;
	// int horz_wall_content = 0;

	yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down)
		yintercept += TILE_SIZE;
	xintercept = cub->player->x + (yintercept - cub->player->y) / tan(ray_angle);

	ystep = TILE_SIZE;
	if (is_ray_facing_up)
		ystep *= -1;

	xstep = TILE_SIZE / tan(ray_angle);
	if (is_ray_facing_left && xstep > 0)
		xstep *= -1;
	if (is_ray_facing_right && xstep < 0)
		xstep *= -1;

	float next_horz_touch_x = xintercept;
	float next_horz_touch_y = yintercept;
	// if (is_ray_facing_up)
	// 	next_horz_touch_y--;

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= cub->data->window_width && next_horz_touch_y >= 0 && next_horz_touch_y <= cub->data->window_height)
	{
		if (!can_move(cub->data, next_horz_touch_x, next_horz_touch_y - (is_ray_facing_up == TRUE)))
		{
			found_horz_wall_hit = TRUE;
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			// horz_wall_content = cub->data->map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			
			// draw_line(cub, horz_wall_hit_x, horz_wall_hit_y);
			break;
		}
		else
		{
			next_horz_touch_x += xstep;
			next_horz_touch_y += ystep;
		}
	}

	// Verticals

	int found_vert_wall_hit = FALSE;
	float vert_wall_hit_x = 0;
	float vert_wall_hit_y = 0;

	xintercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right)
		xintercept += TILE_SIZE;

	yintercept = cub->player->y + (xintercept - cub->player->x) * tan(ray_angle);

	xstep = TILE_SIZE;
	if (is_ray_facing_left)
		xstep *= -1;

	ystep = TILE_SIZE * tan(ray_angle);
	if (is_ray_facing_up && ystep > 0)
		ystep *= -1;
	if (is_ray_facing_down && ystep < 0)
		ystep *= -1;

	float next_vert_touch_x = xintercept;
	float next_vert_touch_y = yintercept;

	// if (is_ray_facing_left)
	// 	next_vert_touch_x--;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= cub->data->window_width && next_vert_touch_y >= 0 && next_vert_touch_y <= cub->data->window_height)
	{
		if (!can_move(cub->data, next_vert_touch_x - (is_ray_facing_left == TRUE), next_vert_touch_y))
		{
			found_vert_wall_hit = TRUE;
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			// vert_wall_content = cub->data->map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			break;
		}
		else
		{
			next_vert_touch_x += xstep;
			next_vert_touch_y += ystep;
		}
	}

	float horz_hit_distance = get_distance(cub, found_horz_wall_hit, horz_wall_hit_x, horz_wall_hit_y);
	float vert_hit_distance = get_distance(cub, found_vert_wall_hit, vert_wall_hit_x, vert_wall_hit_y);

	if (vert_hit_distance < horz_hit_distance)
	{
		cub->rays[i].distance = vert_hit_distance;
		cub->rays[i].wall_hit_x = vert_wall_hit_x;
		cub->rays[i].wall_hit_y = vert_wall_hit_y;
		cub->rays[i].was_hit_vertical = TRUE;
	}
	else
	{
		cub->rays[i].distance = horz_hit_distance;
		cub->rays[i].wall_hit_x = horz_wall_hit_x;
		cub->rays[i].wall_hit_y = horz_wall_hit_y;
		cub->rays[i].was_hit_vertical = FALSE;
	}
	if (cub->rays[i].distance == 0)
		cub->rays[i].distance = 0.0001;
	cub->rays[i].angle = ray_angle;
	cub->rays[i].is_ray_facing_down = is_ray_facing_down;
	cub->rays[i].is_ray_facing_up = is_ray_facing_up;
	cub->rays[i].is_ray_facing_left = is_ray_facing_left;
	cub->rays[i].is_ray_facing_right = is_ray_facing_right;
}

void	set_rays(t_cub *cub)
{
	int		i;
	float	ray_angle;

	ray_angle = cub->player->angle - (cub->player->fov / 2);

	i = -1;
	while (++i < WINW)
	{
		cast_ray(cub, ray_angle, i);
		ray_angle += cub->player->fov / WINW;
	}
}

void	draw_rays(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < WINW)
		draw_line(cub, cub->rays[i].wall_hit_x, cub->rays[i].wall_hit_y);
}

void	render_3d_wall(t_cub *cub, int i, int wall_top_pixel, int wall_bottom_pixel)
{
	int j;

	j = 0;
	while (j < wall_top_pixel)
		my_mlx_pixel_put(cub->cub, i, j++, cub->data->ceiling);
	while (j < wall_bottom_pixel)
		my_mlx_pixel_put(cub->cub, i, j++, 0x00FFFFFF);
	while (j < WINH)
		my_mlx_pixel_put(cub->cub, i, j++, cub->data->floor);
}

void	generate_3d_projection(t_cub *cub)
{
	int		i;
	float distance_proj_plane;
	float correct_distance;
	int wall_strip_height;
	int wall_top_pixel;
	int wall_bottom_pixel;

	i = -1;
	while (++i < WINW)
	{
		correct_distance = cub->rays[i].distance * cos(cub->rays[i].angle - cub->player->angle);
		distance_proj_plane = (WINW / 2) / tan(cub->player->fov / 2);
		wall_strip_height = (TILE_SIZE / correct_distance) * distance_proj_plane;
		
		wall_top_pixel = (WINH / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (WINH / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > WINH)
			wall_bottom_pixel = WINH;
		render_3d_wall(cub, i, wall_top_pixel, wall_bottom_pixel);
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
	// mlx_clear_window(cub->mlxdata->mlx, cub->mlxdata->win);
	mlx_put_image_to_window(cub->mlxdata->mlx,
		cub->mlxdata->win, cub->img->img,
		(WINW - (WINW * MINIMAP_SCALE_FACTOR) - 10) * 0,
		10 * 0);
	mlx_put_image_to_window(cub->mlxdata->mlx,
		cub->mlxdata->win, cub->cub->img, 0, 0);
	// draw_sprites(cub);
}

// void	draw() 
// {
// 	update();
// 	render();
// }