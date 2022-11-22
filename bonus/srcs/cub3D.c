/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:31 by omanar            #+#    #+#             */
/*   Updated: 2022/11/22 17:33:18 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->win = mlx_new_window(cub->mlx,
			WINW, WINH, "Cub3D");
	if (!cub->win)
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
	generate_2d_map(cub);
	generate_2d_player(cub);
	mouse_move(cub);
}

void	render(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx,
		cub->win, cub->cub->img, 0, 0);
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
	mlx_loop_hook(cub->mlx, loop_hook, cub);
	mlx_loop(cub->mlx);
	return (0);
}
