/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:23:39 by adiouane          #+#    #+#             */
/*   Updated: 2022/11/20 17:09:58 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_name(char *name)
{
	if (!ft_strncmp(name, "NO", 3))
		return (TOKEN_NO);
	else if (!ft_strncmp(name, "SO", 3))
		return (TOKEN_SO);
	else if (!ft_strncmp(name, "WE", 3))
		return (TOKEN_WE);
	else if (!ft_strncmp(name, "EA", 3))
		return (TOKEN_EA);
	else if (!ft_strncmp(name, "DR", 3))
		return (TOKEN_DR);
	else if (!ft_strncmp(name, "F", 2))
		return (TOKEN_F);
	else if (!ft_strncmp(name, "C", 2))
		return (TOKEN_C);
	else
		return (TOKEN_ERROR);
}

int	get_color(char *line, int *i)
{
	int		j;
	char	*rgb;
	int		color;
	int		k;

	if (line[*i] == ',')
		(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	j = *i;
	while (line[*i] && line[*i] != ',' && line[*i] != ' ')
		(*i)++;
	rgb = ft_substr(line, j, *i - j);
	k = -1;
	while (rgb[++k])
		if (!ft_isdigit(rgb[k]))
			exit_error("Invalid color", line);
	if (!rgb[0])
		(free(rgb), exit_error("Invalid color", line));
	color = ft_atoi(rgb);
	free(rgb);
	if (color < 0 || color > 255)
		exit_error("Some element are out of range", line);
	return (color);
}

void	color_parsing(t_cub *cub, char *line, int token, int i)
{
	int		color[3];
	int		n;

	n = -1;
	while (++n < 3)
	{
		skipe_spaces(line, &i);
		color[n] = get_color(line, &i);
	}
	if (line[i])
		exit_error("Invalid color", line);
	check_lenght(line);
	if (token == TOKEN_F && cub->data->floor == -1)
		cub->data->floor = (color[0] << 16) + (color[1] << 8) + color[2];
	else if (token == TOKEN_C && cub->data->ceiling == -1)
		cub->data->ceiling = (color[0] << 16) + (color[1] << 8) + color[2];
	else
		exit_error("duplicate color", line);
	free(line);
}

void	texture_parsing(t_cub *cub, char *line, int token, int i)
{
	char	*path;

	skipe_spaces(line, &i);
	path = ft_strdup(&line[i]);
	file_checker(path, ".xpm\0");
	if (token == TOKEN_NO && !cub->data->no)
		cub->data->no = path;
	else if (token == TOKEN_SO && !cub->data->so)
		cub->data->so = path;
	else if (token == TOKEN_WE && !cub->data->we)
		cub->data->we = path;
	else if (token == TOKEN_EA && !cub->data->ea)
		cub->data->ea = path;
	else if (token == TOKEN_DR && !cub->data->dr)
		cub->data->dr = path;
	else
		exit_error("Duplicate texture", line);
	free(line);
}

int	line_parsing(t_cub *cub, char *line)
{
	int		i;
	int		j;
	int		token;
	char	*name;

	i = 0;
	if (is_map(line))
		return (1);
	skipe_spaces(line, &i);
	j = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	name = ft_substr(line, j, i - j);
	token = check_name(name);
	if (token == TOKEN_ERROR)
		exit_error("Invalid Name", name);
	else if (token == TOKEN_F || token == TOKEN_C)
		color_parsing(cub, ft_strtrim(line, "\n"), token, i);
	else
		texture_parsing(cub, ft_strtrim(line, "\n"), token, i);
	free(name);
	return (0);
}
