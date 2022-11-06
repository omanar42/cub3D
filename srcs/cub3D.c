/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:31 by omanar            #+#    #+#             */
/*   Updated: 2022/11/06 13:34:13 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_window(t_cub *cub)
{
	cub->mlxdata->mlx = mlx_init();
	if (!cub->mlxdata->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->mlxdata->win = mlx_new_window(cub->mlxdata->mlx,
			WINW, WINH, "Cub3D");
	if (!cub->mlxdata->win)
		exit_error("mlx_new_window", "Error creating MLX window");
	cub->rays = malloc(sizeof(t_ray) * WINW + 1);
	if (!cub->rays)
		exit_strerr("malloc", errno);
}

int	distroy_event(int keycode, t_cub *cub)
{
	(void)cub;
	(void)keycode;
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		exit(0);
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

void	set_hooks(t_cub *cub)
{
	mlx_hook(cub->mlxdata->win, 2, 0, key_press, cub);
	mlx_hook(cub->mlxdata->win, 3, 0, key_release, cub);
	mlx_hook(cub->mlxdata->win, 17, 0, distroy_event, cub);
}

void	setup(t_cub *cub)
{
	set_hooks(cub);
	set_cub(cub);
}

void	set_map(t_cub *cub)
{
	int		i;
	int		j;
	int		tilex;
	int		tiley;

	j = -1;
	while (cub->data->map[++j])
	{
		i = -1;
		while (cub->data->map[j][++i])
		{
			tilex = i * TILE_SIZE;
			tiley = j * TILE_SIZE;
			if (cub->data->map[j][i] == '1')
				my_pixel_put(cub->img, tilex, tiley, 0xDFCD8B);
			else if (cub->data->map[j][i] == ' ')
				my_pixel_put(cub->img, tilex, tiley, 0x000000);
			else
				my_pixel_put(cub->img, tilex, tiley, 0xB1B3B2);
		}
	}
}

int	loop_hook(t_cub *cub)
{
	if (cub->run)
	{
		update(cub);
		render(cub);
		// display_cub(cub);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_success("Usage: ./cub3D <map.cub>");
	cub = (t_cub *)malloc(sizeof(t_cub));
	parsing(cub, av[1]);
	init_window(cub);
	setup(cub);
	mlx_loop_hook(cub->mlxdata->mlx, loop_hook, cub);
	mlx_loop(cub->mlxdata->mlx);
	return (0);
}
