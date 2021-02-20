/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_draw_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:47:21 by mac               #+#    #+#             */
/*   Updated: 2021/02/20 19:47:22 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	input_wall_texture_init_sub(t_struct *tmp, t_cal *st_cal)
{
	if (st_cal->side == 0)
		st_cal->wall_x = tmp->user_y + st_cal->perpwalldist * st_cal->raydir_y;
	else
		st_cal->wall_x = tmp->user_x + st_cal->perpwalldist * st_cal->raydir_x;
	st_cal->wall_x -= floor(st_cal->wall_x);
	st_cal->tex_x = (int)(st_cal->wall_x * (double)tmp->image_width);
	if (st_cal->side == 0 && st_cal->raydir_x > 0)
		st_cal->tex_x = tmp->image_width - st_cal->tex_x - 1;
	if (st_cal->side == 1 && st_cal->raydir_y < 0)
		st_cal->tex_x = tmp->image_width - st_cal->tex_x - 1;
	st_cal->tex_x = 64 - st_cal->tex_x;
}

void	input_wall_texture_init(t_struct *tmp, t_cal *st_cal)
{
	st_cal->lineheight = (int)(tmp->window_size_y / st_cal->perpwalldist);
	st_cal->drawstart = -st_cal->lineheight / 2 + tmp->window_size_y / 2;
	st_cal->drawend = st_cal->lineheight / 2 + tmp->window_size_y / 2;
	if (st_cal->drawstart < 0)
		st_cal->drawstart = 0;
	if (st_cal->drawend >= tmp->window_size_y)
		st_cal->drawend = tmp->window_size_y - 1;
	if (st_cal->side == 0)
	{
		if ((st_cal->raydir_y <= 0 && st_cal->raydir_x <= 0)
				|| (st_cal->raydir_y > 0 && st_cal->raydir_x <= 0))
			st_cal->texnum = 2;
		else
			st_cal->texnum = 3;
	}
	else
	{
		if ((st_cal->raydir_y <= 0 && st_cal->raydir_x <= 0)
				|| (st_cal->raydir_y <= 0 && st_cal->raydir_x > 0))
			st_cal->texnum = 0;
		else
			st_cal->texnum = 1;
	}
	input_wall_texture_init_sub(tmp, st_cal);
}

void	input_wall_texture(t_struct *tmp, t_cal *st_cal, int x)
{
	int			y;
	int			color;

	y = -1;
	input_wall_texture_init(tmp, st_cal);
	st_cal->step = 1.0 * tmp->image_height / st_cal->lineheight;
	st_cal->texpos = (st_cal->drawstart
			- tmp->window_size_y / 2 + st_cal->lineheight / 2) * st_cal->step;
	while (++y < tmp->window_size_y)
	{
		if (y >= st_cal->drawstart && y <= st_cal->drawend)
		{
			st_cal->tex_y = (int)st_cal->texpos & (tmp->image_height - 1);
			st_cal->texpos += st_cal->step;
			color = tmp->texture_arr[st_cal->texnum][tmp->image_height
				* st_cal->tex_y + st_cal->tex_x];
			if (st_cal->side == 1)
				color = (color >> 1) & 8355711;
			tmp->buf[y][x] = color;
		}
		else if (y < st_cal->drawstart)
			tmp->buf[y][x] = tmp->ceil_color;
		else
			tmp->buf[y][x] = tmp->floor_color;
	}
}

void	cal_dist_sub(t_struct *tmp, t_cal *st_cal)
{
	while (st_cal->hit == 0)
	{
		if (st_cal->sidedist_x < st_cal->sidedist_y)
		{
			st_cal->sidedist_x += st_cal->deltadist_x;
			st_cal->map_x += st_cal->step_x;
			st_cal->side = 0;
		}
		else
		{
			st_cal->sidedist_y += st_cal->deltadist_y;
			st_cal->map_y += st_cal->step_y;
			st_cal->side = 1;
		}
		if (tmp->map[st_cal->map_y][st_cal->map_x] == '1')
			st_cal->hit = 1;
	}
	if (st_cal->side == 0)
		st_cal->perpwalldist = (st_cal->map_x - tmp->user_x
				+ (1 - st_cal->step_x) / 2) / st_cal->raydir_x;
	else
		st_cal->perpwalldist = (st_cal->map_y - tmp->user_y
				+ (1 - st_cal->step_y) / 2) / st_cal->raydir_y;
}

void	cal_dist_init(t_struct *tmp, t_cal *st_cal)
{
	if (st_cal->raydir_x < 0)
	{
		st_cal->step_x = -1;
		st_cal->sidedist_x = (tmp->user_x - st_cal->map_x)
			* st_cal->deltadist_x;
	}
	else
	{
		st_cal->step_x = 1;
		st_cal->sidedist_x = (st_cal->map_x + 1.0 - tmp->user_x)
			* st_cal->deltadist_x;
	}
	if (st_cal->raydir_y < 0)
	{
		st_cal->step_y = -1;
		st_cal->sidedist_y = (tmp->user_y - st_cal->map_y)
			* st_cal->deltadist_y;
	}
	else
	{
		st_cal->step_y = 1;
		st_cal->sidedist_y = (st_cal->map_y + 1.0 - tmp->user_y)
			* st_cal->deltadist_y;
	}
}
