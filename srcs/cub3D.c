/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:31 by omanar            #+#    #+#             */
/*   Updated: 2022/11/09 23:10:28 by omanar           ###   ########.fr       */
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

void	update(t_cub *cub)
{
	move_player(cub);
	set_rays(cub);
	generate_3d_projection(cub);
}

void	render(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlxdata->mlx,
		cub->mlxdata->win, cub->cub->img, 0, 0);
}

int	loop_hook(t_cub *cub)
{
	update(cub);
	render(cub);
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
	init_textures(cub);
	setup(cub);
	mlx_loop_hook(cub->mlxdata->mlx, loop_hook, cub);
	mlx_loop(cub->mlxdata->mlx);
	return (0);
}
