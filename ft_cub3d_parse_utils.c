/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_parse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:48:26 by mac               #+#    #+#             */
/*   Updated: 2021/02/22 13:26:16 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pos_init(t_struct *tmp, char pos, int i)
{
	tmp->user_x = i;
	tmp->user_y = tmp->map_size_y;
	if (tmp->pos_tmp == 1)
		tmp->error = 1;
	if (pos == 'N' || pos == 'S')
	{
		tmp->plane_x = -0.66;
		tmp->dir_y = 1;
		if (pos == 'N')
		{
			tmp->dir_y = -1;
			tmp->plane_x = 0.66;
		}
	}
	else if (pos == 'W' || pos == 'E')
	{
		tmp->plane_y = 0.66;
		tmp->dir_x = 1;
		if (pos == 'W')
		{
			tmp->dir_x = -1;
			tmp->plane_y = -0.66;
		}
	}
	tmp->pos_tmp = 1;
}

void	first_last_line(char *line, t_struct *tmp, char *map_tmp)
{
	int			i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (!(line[i] == ' ' || line[i] == '1') || white_space(line[i]))
			tmp->error = 1;
		if (tmp->last_line == 1 && line[i] == ' ')
			if (map_tmp[i] == '0')
				tmp->error = 1;
	}
}

void	middle_line(char *line, t_struct *tmp, char *map_tmp)
{
	int			i;

	i = -1;
	while (line[++i] != '\0')
	{
		middle_line_sub(tmp, line, map_tmp);
		if (i == 0 || line[i + 1] == '\0')
			if (line[i] == '0')
				tmp->error = 1;
		if (white_space(line[i]))
			tmp->error = 1;
		if (line[i] == '0')
		{
			if (line[i - 1] == ' ' || line[i + 1] == ' ' || map_tmp[i] == ' ')
				tmp->error = 1;
		}
		else if (line[i] == ' ' && i < (int)ft_strlen(map_tmp))
			if (map_tmp[i] != '1' && map_tmp[i] != ' ')
				tmp->error = 1;
		if (line[i] == '2')
			tmp->num_sprite++;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
				|| line[i] == 'E')
			pos_init(tmp, line[i], i);
	}
}

int		hexa_to_int(char *input)
{
	int		result;
	int		i;
	int		j;
	int		tmp;
	int		num_tmp;

	result = 0;
	i = 5;
	while (i > -1)
	{
		j = -1;
		tmp = 1;
		while (++j < 5 - i)
			tmp *= 16;
		if (input[i] >= '0' && input[i] <= '9')
			num_tmp = input[i] - '0';
		else
			num_tmp = input[i] - 'A' + 10;
		result += tmp * num_tmp;
		i--;
	}
	return (result);
}

char	*to_hexa(int input)
{
	char	*result;
	char	*match;

	match = "0123456789ABCDEF";
	result = (char*)malloc(3);
	if (input / 16 > 15 || input < 0)
		return (0);
	result[0] = match[input / 16];
	result[1] = match[input % 16];
	result[2] = '\0';
	return (result);
}
