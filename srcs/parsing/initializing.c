/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:03:25 by omanar            #+#    #+#             */
/*   Updated: 2022/11/10 12:58:19 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_data(t_cub *cub)
{
	cub->data->no = NULL;
	cub->data->so = NULL;
	cub->data->we = NULL;
	cub->data->ea = NULL;
	cub->data->floor = -1;
	cub->data->ceiling = -1;
	cub->data->width = 0;
	cub->data->height = 0;
}

void	player_config(t_cub *cub)
{
	cub->player->x = -1;
	cub->player->y = -1;
	cub->player->ver_dir = 0;
	cub->player->hor_dir = 0;
	cub->player->turndir = 0;
	cub->player->angle = 0;
	cub->player->fov = 60 * (M_PI / 180);
	cub->player->turnspeed = 5 * (M_PI / 180);
	cub->player->movespeed = 5;
	cub->player->dist_proj_plane = (WINW / 2) / tan(cub->player->fov / 2);
}

void	initialize(t_cub *cub)
{
	if (!cub)
		exit_strerr("malloc", errno);
	cub->cub = malloc(sizeof(t_img));
	cub->sprites = malloc(sizeof(t_sprites));
	cub->data = malloc(sizeof(t_data));
	cub->player = malloc(sizeof(t_player));
	cub->data->map = ft_calloc(1, sizeof(char *));
	if (!cub->cub || !cub->sprites || !cub->data
		|| !cub->player || !cub->data->map)
		exit_strerr("malloc", errno);
	init_data(cub);
	player_config(cub);
}
