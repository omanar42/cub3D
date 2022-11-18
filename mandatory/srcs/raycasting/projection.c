/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:45:35 by omanar            #+#    #+#             */
/*   Updated: 2022/11/18 18:28:41 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_img	*new_sprite(void *mlx, char *path)
{
	t_img	*sprite;

	sprite = malloc(sizeof(t_img));
	if (!sprite)
		exit_strerr("malloc", errno);
	sprite->img = mlx_xpm_file_to_image(mlx, path,
			&sprite->width, &sprite->height);
	if (!sprite->img)
		exit_strerr(path, errno);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->line_length, &sprite->endian);
	return (sprite);
}

void	init_textures(t_cub *cub)
{
	cub->sprites->no = new_sprite(cub->mlx, cub->data->no);
	cub->sprites->so = new_sprite(cub->mlx, cub->data->so);
	cub->sprites->we = new_sprite(cub->mlx, cub->data->we);
	cub->sprites->ea = new_sprite(cub->mlx, cub->data->ea);
}

void	draw_wall(t_cub *cub, t_wall wall, t_img *texture, int i)
{
	int		j;
	char	*dst;

	j = 0;
	while (j < wall.top_pixel)
		my_mlx_pixel_put(cub->cub, i, j++, cub->data->ceiling);
	while (j < wall.bottom_pixel)
	{
		wall.dft = j + (wall.wall_height / 2) - (WINH / 2);
		wall.tex_y = (int)(wall.dft
				* (float)texture->height / wall.wall_height)
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

	if (cub->rays[i].hit_vertical)
	{
		if (cub->rays[i].is_facing_left)
			texture = cub->sprites->we;
		else
			texture = cub->sprites->ea;
		wall.tex_x = (int)(cub->rays[i].yhit
				* texture->width / TILE_SIZE) % texture->width;
	}
	else
	{
		if (cub->rays[i].is_facing_up)
			texture = cub->sprites->no;
		else
			texture = cub->sprites->so;
		wall.tex_x = (int)(cub->rays[i].xhit
				* texture->width / TILE_SIZE) % texture->width;
	}
	draw_wall(cub, wall, texture, i);
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
		wall.wall_height = (TILE_SIZE / wall.correct_distance)
			* cub->player->dist_proj_plane;
		wall.top_pixel = (WINH / 2) - (wall.wall_height / 2);
		if (wall.top_pixel < 0)
			wall.top_pixel = 0;
		wall.bottom_pixel = (WINH / 2) + (wall.wall_height / 2);
		if (wall.bottom_pixel > WINH)
			wall.bottom_pixel = WINH;
		render_3d_wall(cub, i, wall);
	}
}
