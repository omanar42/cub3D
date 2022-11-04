/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:37:07 by omanar            #+#    #+#             */
/*   Updated: 2022/10/12 00:16:26 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	if_something_missing(t_cub *cub)
{
	if (!cub->data->no || !cub->data->so || !cub->data->we || !cub->data->ea)
		exit_str("Missing texture");
	else if (cub->data->floor == -1 || cub->data->ceiling == -1)
		exit_str("Missing color");
	else if (!cub->data->map[0])
		exit_str("Missing map");
}

void	add_player(t_cub *cub, char **map, int y, int x)
{
	if (cub->player->x != -1 || cub->player->y != -1)
		exit_str("Duplicate player");
	cub->player->x = (x * TILE_SIZE) + 0.5;
	cub->player->y = (y * TILE_SIZE) + 0.5;
	if (map[y][x] == 'N')
		cub->player->angle = 270 * (M_PI / 180);
	else if (map[y][x] == 'S')
		cub->player->angle = 90 * (M_PI / 180);
	else if (map[y][x] == 'W')
		cub->player->angle = 180 * (M_PI / 180);
	else if (map[y][x] == 'E')
		cub->player->angle = 0 * (M_PI / 180);
	cub->data->map[y][x] = '0';
}

void	check_border(t_cub *cub, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (x == 0 || x == (int)ft_strlen(map[y]) - 1
				|| y == 0 || y == cub->data->height - 1)
				if (map[y][x] != '1' && map[y][x] != ' ')
					exit_str("Invalid map");
			if (map[y][x] == '0')
				if (map[y][x + 1] == ' ' || map[y][x - 1] == ' '
					|| map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
					exit_str("Invalid map");
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				add_player(cub, map, y, x);
		}
	}
}

void	map_parsing(t_cub *cub, char *line, int fd)
{
	char	*tmp;

	while (line)
	{
		if (!is_map(line))
			exit_error("Invalid map", line);
		cub->data->height++;
		tmp = ft_strtrim(line, "\n");
		if (cub->data->width < (int)ft_strlen(tmp))
			cub->data->width = ft_strlen(tmp);
		cub->data->map = advanced_add(cub->data->map, tmp);
		free(line);
		free(tmp);
		line = get_next_line(fd);
	}
	free(line);
}
