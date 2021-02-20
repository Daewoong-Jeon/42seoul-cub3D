/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_moving_sub.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:47:54 by mac               #+#    #+#             */
/*   Updated: 2021/02/20 19:47:56 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_tool2_keysave_set(int *key_adws, char *key_save_adws, int i, char j)
{
	(*key_adws) = i;
	(*key_save_adws) = j;
}

int		dont_move(t_struct *tmp)
{
	double		tmp_x;
	double		tmp_y;

	tmp_x = 0;
	tmp_y = 0;
	if (tmp->w_key)
	{
		tmp_x = tmp->user_x + tmp->dir_x * MOVE_SPEED;
		tmp_y = tmp->user_y + tmp->dir_y * MOVE_SPEED;
	}
	else if (tmp->s_key)
	{
		tmp_x = tmp->user_x - tmp->dir_x * MOVE_SPEED;
		tmp_y = tmp->user_y - tmp->dir_y * MOVE_SPEED;
	}
	if (tmp->map[(int)tmp_y][(int)tmp_x] == '1')
		return (1);
	return (0);
}

void	rotate_vector(t_struct *tmp, double angle)
{
	static double		tmp_x;
	static double		tmp_plane;

	tmp_x = (tmp->dir_x * cos(angle)) - (tmp->dir_y * sin(angle));
	tmp->dir_y = (tmp->dir_x * sin(angle)) + (tmp->dir_y * cos(angle));
	tmp->dir_x = tmp_x;
	tmp_plane = (tmp->plane_x * cos(angle)) - (tmp->plane_y * sin(angle));
	tmp->plane_y = (tmp->plane_x * sin(angle)) + (tmp->plane_y * cos(angle));
	tmp->plane_x = tmp_plane;
}
