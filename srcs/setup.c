/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:47:11 by omanar            #+#    #+#             */
/*   Updated: 2022/11/09 22:57:06 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		exit(EXIT_SUCCESS);
	else if (keycode == W_KEY || keycode == UP_KEY)
		cub->player->ver_dir = +1;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->ver_dir = -1;
	else if (keycode == D_KEY)
		cub->player->hor_dir = +1;
	else if (keycode == A_KEY)
		cub->player->hor_dir = -1;
	else if (keycode == RIGHT_KEY)
		cub->player->turndir = +1;
	else if (keycode == LEFT_KEY)
		cub->player->turndir = -1;
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		cub->player->ver_dir = 0;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->ver_dir = 0;
	else if (keycode == D_KEY)
		cub->player->hor_dir = 0;
	else if (keycode == A_KEY)
		cub->player->hor_dir = 0;
	else if (keycode == RIGHT_KEY)
		cub->player->turndir = 0;
	else if (keycode == LEFT_KEY)
		cub->player->turndir = 0;
	return (0);
}

int	distroy_event(int keycode, t_cub *cub)
{
	(void)cub;
	(void)keycode;
	exit(EXIT_SUCCESS);
	return (0);
}

void	set_hooks(t_cub *cub)
{
	mlx_hook(cub->mlxdata->win, 2, 0, key_press, cub);
	mlx_hook(cub->mlxdata->win, 3, 0, key_release, cub);
	mlx_hook(cub->mlxdata->win, 17, 0, distroy_event, cub);
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
