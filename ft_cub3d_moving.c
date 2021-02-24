/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_moving.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:47:44 by mac               #+#    #+#             */
/*   Updated: 2021/02/22 16:32:27 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_press_ad(int key, t_struct *tmp)
{
	if (key == A_KEY)
	{
		if (tmp->d_key == 1)
		{
			tmp->ad_key = 'd';
			tmp->d_key = 0;
		}
		tmp->a_key = 1;
	}
	if (key == D_KEY)
	{
		if (tmp->a_key == 1)
		{
			tmp->ad_key = 'a';
			tmp->a_key = 0;
		}
		tmp->d_key = 1;
	}
	key_press_rl(key, tmp);
}

int		key_press(int key, t_struct *tmp)
{
	if (key == ESC_KEY)
		exit(0);
	if (key == W_KEY)
	{
		if (tmp->s_key == 1)
		{
			tmp->ws_key = 's';
			tmp->s_key = 0;
		}
		tmp->w_key = 1;
	}
	if (key == S_KEY)
	{
		if (tmp->w_key == 1)
		{
			tmp->ws_key = 'w';
			tmp->w_key = 0;
		}
		tmp->s_key = 1;
	}
	key_press_ad(key, tmp);
	return (0);
}

void	key_release_ad(int key, t_struct *tmp)
{
	if (key == A_KEY)
	{
		if (tmp->ad_key == 'd')
			ft_tool2_keysave_set(&(tmp->d_key), &(tmp->ad_key), 1, 0);
		else if (tmp->ad_key == 'a')
			ft_tool2_keysave_set(&(tmp->a_key), &(tmp->ad_key), 0, 0);
		tmp->a_key = 0;
	}
	if (key == D_KEY)
	{
		if (tmp->ad_key == 'a')
			ft_tool2_keysave_set(&(tmp->a_key), &(tmp->ad_key), 1, 0);
		else if (tmp->ad_key == 'd')
			ft_tool2_keysave_set(&(tmp->d_key), &(tmp->ad_key), 0, 0);
		tmp->d_key = 0;
	}
	key_release_rl(key, tmp);
}

int		key_release(int key, t_struct *tmp)
{
	if (key == ESC_KEY)
		exit(0);
	if (key == W_KEY)
	{
		if (tmp->ws_key == 's')
			ft_tool2_keysave_set(&(tmp->s_key), &(tmp->ws_key), 1, 0);
		else if (tmp->ws_key == 'w')
			ft_tool2_keysave_set(&(tmp->w_key), &(tmp->ws_key), 0, 0);
		tmp->w_key = 0;
	}
	if (key == S_KEY)
	{
		if (tmp->ws_key == 'w')
			ft_tool2_keysave_set(&(tmp->w_key), &(tmp->ws_key), 1, 0);
		else if (tmp->ws_key == 's')
			ft_tool2_keysave_set(&(tmp->s_key), &(tmp->ws_key), 1, 0);
		tmp->s_key = 0;
	}
	key_release_ad(key, tmp);
	return (0);
}

int		user_move(t_struct *tmp)
{
	if (dont_move(tmp) == 0)
	{
		if (tmp->left_arrow)
			rotate_vector(tmp, -ROTATE_SPEED);
		if (tmp->right_arrow)
			rotate_vector(tmp, ROTATE_SPEED);
		wsad_move(tmp);
	}
	return (0);
}
