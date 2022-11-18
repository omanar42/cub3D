/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing_utls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:01:58 by adiouane          #+#    #+#             */
/*   Updated: 2022/11/17 22:33:31 by adiouane         ###   ########.fr       */
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
