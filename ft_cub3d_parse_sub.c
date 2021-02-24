/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_parse_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:27:57 by mac               #+#    #+#             */
/*   Updated: 2021/02/24 12:47:22 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_color_sub(t_struct *tmp, char *line, int ret_result)
{
	if (line[0] == 'F' && tmp->parse_tmp == 6)
		tmp->floor_color = ret_result;
	else if (line[0] == 'C' && tmp->parse_tmp == 7)
		tmp->ceil_color = ret_result;
	else
		return (-1);
	tmp->parse_tmp++;
	return (1);
}
