/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing_utls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:01:58 by adiouane          #+#    #+#             */
/*   Updated: 2022/11/18 23:38:56 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	set_lines(t_cub *cub)
{
	if (cub->data->no == NULL || cub->data->so == NULL
		|| cub->data->we == NULL || cub->data->ea == NULL
		|| cub->data->floor == -1 || cub->data->ceiling == -1)
		exit_str("Error: Invalid file");
	return (0);
}

void	check_lenght(char *line)
{
	int		i;
	char	**f;

	i = 0;
	f = ft_split(line, ',');
	if (!f)
		exit_str("Error");
	while (f[i])
		i++;
	if (i != 3)
		exit_error("Invalid color", line);
	free_loop(f);
}
