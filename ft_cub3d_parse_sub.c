/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_parse_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:47:11 by djeon             #+#    #+#             */
/*   Updated: 2021/02/20 14:27:37 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_color_sub(t_struct *tmp, char *line, int ret_result)
{
	if (line[0] == 'F' && tmp->parse_tmp == 7)
		tmp->floor_color = ret_result;
	else if (line[0] == 'C' && tmp->parse_tmp == 8)
		tmp->ceil_color = ret_result;
	else
		return (-1);
	tmp->parse_tmp++;
	return (1);
}
