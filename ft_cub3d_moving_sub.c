/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_moving_sub.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:47:54 by mac               #+#    #+#             */
/*   Updated: 2021/02/24 15:00:14 by mac              ###   ########.fr       */
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
	dont_move_sub(tmp, &tmp_x, &tmp_y);
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

void	key_release_rl(int key, t_struct *tmp)
{
	if (key == RIGHT_KEY)
	{
		if (tmp->arrow_key == 'l')
			ft_tool2_keysave_set(&(tmp->left_arrow), &(tmp->arrow_key), 1, 0);
		else if (tmp->arrow_key == 'r')
			ft_tool2_keysave_set(&(tmp->right_arrow), &(tmp->arrow_key), 1, 0);
		tmp->right_arrow = 0;
	}
	if (key == LEFT_KEY)
	{
		if (tmp->arrow_key == 'r')
			ft_tool2_keysave_set(&(tmp->right_arrow), &(tmp->arrow_key), 1, 0);
		else if (tmp->arrow_key == 'l')
			ft_tool2_keysave_set(&(tmp->left_arrow), &(tmp->arrow_key), 1, 0);
		tmp->left_arrow = 0;
	}
}

void	key_press_rl(int key, t_struct *tmp)
{
	if (key == LEFT_KEY)
	{
		if (tmp->right_arrow == 1)
		{
			tmp->arrow_key = 'r';
			tmp->right_arrow = 0;
		}
		tmp->left_arrow = 1;
	}
	if (key == RIGHT_KEY)
	{
		if (tmp->left_arrow == 1)
		{
			tmp->arrow_key = 'l';
			tmp->left_arrow = 0;
		}
		tmp->right_arrow = 1;
	}
}
