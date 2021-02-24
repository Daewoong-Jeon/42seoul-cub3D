/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_moving_sub2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:30:09 by mac               #+#    #+#             */
/*   Updated: 2021/02/22 16:35:01 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		wsad_move(t_struct *tmp)
{
	if (tmp->s_key)
	{
		tmp->user_x -= tmp->dir_x * MOVE_SPEED;
		tmp->user_y -= tmp->dir_y * MOVE_SPEED;
	}
	if (tmp->w_key)
	{
		tmp->user_x += tmp->dir_x * MOVE_SPEED;
		tmp->user_y += tmp->dir_y * MOVE_SPEED;
	}
	if (tmp->a_key)
	{
		tmp->user_x -= tmp->plane_x * MOVE_SPEED;
		tmp->user_y -= tmp->plane_y * MOVE_SPEED;
	}
	if (tmp->d_key)
	{
		tmp->user_x += tmp->plane_x * MOVE_SPEED;
		tmp->user_y += tmp->plane_y * MOVE_SPEED;
	}
}

void		dont_move_sub(t_struct *tmp, double *tmp_x, double *tmp_y)
{
	if (tmp->w_key)
	{
		*tmp_x = tmp->user_x + tmp->dir_x * MOVE_SPEED;
		*tmp_y = tmp->user_y + tmp->dir_y * MOVE_SPEED;
	}
	else if (tmp->s_key)
	{
		*tmp_x = tmp->user_x - tmp->dir_x * MOVE_SPEED;
		*tmp_y = tmp->user_y - tmp->dir_y * MOVE_SPEED;
	}
	else if (tmp->a_key)
	{
		*tmp_x = tmp->user_x - tmp->plane_x * MOVE_SPEED;
		*tmp_y = tmp->user_y - tmp->plane_y * MOVE_SPEED;
	}
	else if (tmp->d_key)
	{
		*tmp_x = tmp->user_x + tmp->plane_x * MOVE_SPEED;
		*tmp_y = tmp->user_y + tmp->plane_y * MOVE_SPEED;
	}
}
