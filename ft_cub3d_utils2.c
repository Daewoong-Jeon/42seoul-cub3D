/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:48:46 by mac               #+#    #+#             */
/*   Updated: 2021/02/22 13:33:56 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr(char *str)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
		write(1, &str[i], 1);
}

void	middle_line_sub(t_struct *tmp, char *line, char *map_tmp)
{
	int			i;

	if (ft_strlen(line) < ft_strlen(map_tmp))
	{
		i = ft_strlen(line);
		while (map_tmp[i] != '\0')
		{
			if (map_tmp[i] != '1' && map_tmp[i] != ' ')
				tmp->error = 1;
			i++;
		}
	}
	if (line[0] == '\0')
		tmp->error = 1;
}

char	**ft_strdup_2(char **arr, int size)
{
	char		**result;
	int			i;

	i = -1;
	if (!(result = (char**)malloc(sizeof(char*) * (size + 1))))
		return (0);
	while (++i < size)
		result[i] = arr[i];
	result[i] = "\0";
	return (result);
}

void	swap_line(t_struct *tmp, int *i, char *line)
{
	if (*i % 2 == 1)
	{
		tmp->map_tmp2 = ft_strdup_2(tmp->map_tmp1, *i + 1);
		free(tmp->map_tmp1);
		middle_line(line, tmp, tmp->map_tmp2[*i - 1]);
		tmp->map_tmp2[*i] = ft_strdup(line);
		*i += 1;
		tmp->map_tmp2[*i] = "\0";
	}
	else
	{
		tmp->map_tmp1 = ft_strdup_2(tmp->map_tmp2, *i + 1);
		free(tmp->map_tmp2);
		middle_line(line, tmp, tmp->map_tmp1[*i - 1]);
		tmp->map_tmp1[*i] = ft_strdup(line);
		*i += 1;
		tmp->map_tmp1[*i] = "\0";
	}
}

void	parse_map_sub(t_struct *tmp, int fd, int *i, char *line)
{
	while (get_next_line(fd, &line, &tmp->error) > -1)
	{
		tmp->map_size_y = *i;
		tmp->line_len = ft_strlen(line);
		if (tmp->map_size_x < tmp->line_len)
			tmp->map_size_x = tmp->line_len;
		swap_line(tmp, i, line);
		free(line);
	}
	free(line);
	tmp->last_line = 1;
	tmp->map_size_y++;
}
