/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:20:16 by adiouane          #+#    #+#             */
/*   Updated: 2022/11/18 18:09:38 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	file_checker(char *str, char *extension)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		exit_error("No extension found", str);
	else if (ft_strncmp(ext, extension, 5))
		exit_error("Invalid file extension", ext);
}

void	file_parsing(t_cub *cub, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (line_parsing(cub, line))
			{
				map_parsing(cub, line, fd);
				return ;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	parsing(t_cub *cub, char *str)
{
	int		fd;

	file_checker(str, ".cub\0");
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_strerr(str, errno);
	initialize(cub);
	file_parsing(cub, fd);
	close(fd);
	checker(cub, cub->data->map);
	if_something_missing(cub);
	check_borders(cub->data->map);
}
