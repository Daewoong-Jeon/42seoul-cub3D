/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:48:17 by mac               #+#    #+#             */
/*   Updated: 2021/02/24 12:54:36 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(int fd, t_struct *tmp, char *line)
{
	int			i;

	i = 0;
	if (!(tmp->map_tmp1 = (char**)malloc(sizeof(char*) * 2)))
		exit(-1);
	first_last_line(line, tmp, "\0");
	tmp->map_size_x = ft_strlen(line);
	tmp->map_tmp1[i++] = ft_strdup(line);
	tmp->map_tmp1[i] = "\0";
	parse_map_sub(tmp, fd, &i, line);
	if (tmp->map_size_y % 2 == 1)
	{
		first_last_line(line, tmp, tmp->map_tmp1[i - 1]);
		tmp->map = ft_strdup_2(tmp->map_tmp1, i);
		free(tmp->map_tmp1);
	}
	else
	{
		first_last_line(line, tmp, tmp->map_tmp2[i - 1]);
		tmp->map = ft_strdup_2(tmp->map_tmp2, i);
		free(tmp->map_tmp2);
	}
}

int		parse_color(char *line, t_struct *tmp)
{
	char	**ret;
	char	*ret_tmp;
	char	*hexa;
	int		ret_result;
	int		i;

	if (!(ret_tmp = (char*)malloc(7)))
		return (-1);
	ret = ft_split(&line[2], ',');
	i = 0;
	while (i < 6)
	{
		if (!(hexa = to_hexa(ft_atoi(ret[i / 2]))))
			return (-1);
		ft_strlcpy(&ret_tmp[i], hexa, 3);
		free(hexa);
		i += 2;
	}
	double_pointer_free(ret, 4);
	ret_result = hexa_to_int(ret_tmp);
	free(ret_tmp);
	if (parse_color_sub(tmp, line, ret_result) == -1)
		return (-1);
	return (0);
}

void	load_texture(int index, char *line, t_struct *tmp)
{
	char	**ret;

	ret = ft_split(line, ' ');
	if (index == -1)
	{
		if (ret[1] == 0 || ret[2] == 0)
		{
			ft_putstr("parsing error\n");
			exit(-1);
		}
		tmp->window_size_x = ft_atoi(ret[1]);
		tmp->window_size_y = ft_atoi(ret[2]);
		if (tmp->window_size_x > 1920 || tmp->window_size_y > 1080)
		{
			tmp->window_size_x = 1920;
			tmp->window_size_y = 1080;
		}
		double_pointer_free(ret, 4);
	}
	else
	{
		load_image(tmp, tmp->texture_arr[index], ret[1]);
		double_pointer_free(ret, 3);
	}
}

int		load_texture_sub(char *line, t_struct *tmp)
{
	if (ft_strncmp("R ", line, 2) == 0 && tmp->parse_tmp == 0)
		load_texture(-1, line, tmp);
	else if (ft_strncmp("NO ", line, 3) == 0 && tmp->parse_tmp == 1)
		load_texture(0, line, tmp);
	else if (ft_strncmp("SO ", line, 3) == 0 && tmp->parse_tmp == 2)
		load_texture(1, line, tmp);
	else if (ft_strncmp("S ", line, 2) == 0 && tmp->parse_tmp == 5)
		load_texture(4, line, tmp);
	else if (ft_strncmp("WE ", line, 3) == 0 && tmp->parse_tmp == 3)
		load_texture(2, line, tmp);
	else if (ft_strncmp("EA ", line, 3) == 0 && tmp->parse_tmp == 4)
		load_texture(3, line, tmp);
	else
		return (-1);
	if (tmp->error == 1)
		return (-1);
	tmp->parse_tmp++;
	return (0);
}

int		parse_cub(int fd, t_struct *tmp)
{
	char		*line;

	while (get_next_line(fd, &line, &tmp->tem) > -1)
	{
		if (line[0] == 'R' || line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
				|| line[0] == 'E')
		{
			if (load_texture_sub(line, tmp) == -1)
				return (-1);
		}
		else if (line[0] == 'F' || line[0] == 'C')
		{
			if (parse_color(line, tmp) == -1 || line[1] != ' ')
				return (-1);
		}
		else if (tmp->parse_tmp == 8 && line[0] != '\0')
			parse_map(fd, tmp, line);
		free(line);
	}
	free(line);
	if (tmp->error == 1 || tmp->pos_tmp == 0 || tmp->parse_tmp != 8)
		return (-1);
	return (0);
}
