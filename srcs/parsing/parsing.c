/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:33:21 by omanar            #+#    #+#             */
/*   Updated: 2022/11/01 18:03:50 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	file_checker(char *str)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		exit_str("No extension found");
	else if (ft_strncmp(ext, ".cub\0", 5))
		exit_error("invalid file extension", ext);
}

void	file_parsing(t_cub *cub, int fd)
{
	int		i;
	char	*line;

	i = 0;
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
		i++;
	}
}

void	parsing(t_cub *cub, char *str)
{
	int		fd;

	file_checker(str);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_strerr(str, errno);
	initialize(cub);
	file_parsing(cub, fd);
	close(fd);
	if_something_missing(cub);
	check_border(cub, cub->data->map);
}
