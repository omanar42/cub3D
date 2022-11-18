/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:43:10 by omanar            #+#    #+#             */
/*   Updated: 2022/11/18 13:07:57 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	control_hundler(t_cub *cub)
{
	if (!cub->mouse)
	{
		cub->mouse = TRUE;
		mlx_mouse_show();
	}
	else
	{
		cub->mouse = FALSE;
		mlx_mouse_hide();
	}
}

int	mouse_move(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->mouse)
		return (0);
	mlx_mouse_get_pos(cub->win, &x, &y);
	if (x >= 0 && x <= WINW && y >= 0 && y <= WINH)
	{
		if (x < (WINW / 2))
			cub->player->angle -= 3 * (M_PI / 180);
		else if (x > (WINW / 2))
			cub->player->angle += 3 * (M_PI / 180);
	}
	mlx_mouse_move(cub->win, WINW / 2, WINH / 2);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_cub *cub)
{
	if (button == 1)
	{
		if (cub->mouse && x >= 0 && x <= WINW && y >= 0 && y <= WINH)
		{
			cub->mouse = FALSE;
			mlx_mouse_hide();
		}
	}
	return (0);
}
