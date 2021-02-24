/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:47:10 by mac               #+#    #+#             */
/*   Updated: 2021/02/24 13:09:53 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	input_sprite_texture(t_struct *tmp, t_cal *st_cal, int spriteorder)
{
	int			stripe;
	int			y;
	int			color;

	stripe = st_cal->drawstart_x - 1;
	while (++stripe < st_cal->drawend_x)
	{
		st_cal->tex_x = (int)((256 * (stripe - (-st_cal->spritewidth / 2
				+ st_cal->spritescreen_x)) * 64 / st_cal->spritewidth) / 256);
		if (st_cal->transform_y > 0 && stripe > 0 && stripe < tmp->window_size_x
				&& st_cal->transform_y < tmp->zbuffer[stripe])
		{
			y = st_cal->drawstart_y - 1;
			while (++y < st_cal->drawend_y)
			{
				st_cal->tex_y = ((((y - st_cal->vmovescreen) * 256
					- tmp->window_size_y * 128 + st_cal->spriteheight * 128)
							* 64) / st_cal->spriteheight) / 256;
				color = tmp->texture_arr[tmp->sprite[spriteorder].texture]
					[64 * st_cal->tex_y + st_cal->tex_x];
				if ((color & 0x00FFFFFF) != 0)
					tmp->buf[y][stripe] = color;
			}
		}
	}
}

void	input_sprite_texture_init(t_struct *tmp, t_cal *st_cal, int spriteorder)
{
	st_cal->sprite_x = tmp->sprite[spriteorder].x - tmp->user_x;
	st_cal->sprite_y = tmp->sprite[spriteorder].y - tmp->user_y;
	st_cal->invdet = 1.0 / (tmp->plane_x * tmp->dir_y - tmp->dir_x
			* tmp->plane_y);
	st_cal->transform_x = st_cal->invdet * (tmp->dir_y * st_cal->sprite_x
			- tmp->dir_x * st_cal->sprite_y);
	st_cal->transform_y = st_cal->invdet * (-tmp->plane_y * st_cal->sprite_x
			+ tmp->plane_x * st_cal->sprite_y);
	st_cal->spritescreen_x = (int)((tmp->window_size_x / 2)
			* (1 + st_cal->transform_x / st_cal->transform_y));
	st_cal->vmovescreen = (int)(VMOVE / st_cal->transform_y);
	st_cal->spriteheight = (int)fabs((tmp->window_size_y / st_cal->transform_y)
			/ UDIV);
	st_cal->drawstart_y = -st_cal->spriteheight / 2 + tmp->window_size_y
		/ 2 + st_cal->vmovescreen;
	st_cal->drawend_y = st_cal->spriteheight / 2 + tmp->window_size_y
		/ 2 + st_cal->vmovescreen;
	if (st_cal->drawstart_y < 0)
		st_cal->drawstart_y = 0;
	if (st_cal->drawend_y >= tmp->window_size_y)
		st_cal->drawend_y = tmp->window_size_y - 1;
}

void	cal_dist(int x, t_struct *tmp, t_cal *st_cal)
{
	st_cal->camera_x = 2 * x / (double)tmp->window_size_x - 1;
	st_cal->raydir_x = tmp->dir_x + tmp->plane_x * st_cal->camera_x;
	st_cal->raydir_y = tmp->dir_y + tmp->plane_y * st_cal->camera_x;
	st_cal->map_x = (int)tmp->user_x;
	st_cal->map_y = (int)tmp->user_y;
	st_cal->deltadist_x = fabs(1 / st_cal->raydir_x);
	st_cal->deltadist_y = fabs(1 / st_cal->raydir_y);
	st_cal->hit = 0;
	cal_dist_init(tmp, st_cal);
	cal_dist_sub(tmp, st_cal);
}

void	cal_sprite(t_struct *tmp, t_cal *st_cal, int *spriteorder,
		double *spritedistance)
{
	int		i;

	i = -1;
	while (++i < tmp->num_sprite)
	{
		spriteorder[i] = i;
		spritedistance[i] = ((tmp->user_x - tmp->sprite[i].x)
				* (tmp->user_x - tmp->sprite[i].x) + (tmp->user_y
					- tmp->sprite[i].y) * (tmp->user_y - tmp->sprite[i].y));
	}
	sortsprites(spriteorder, spritedistance, tmp->num_sprite);
	i = -1;
	while (++i < tmp->num_sprite)
	{
		input_sprite_texture_init(tmp, st_cal, spriteorder[i]);
		st_cal->spritewidth = (int)fabs((tmp->window_size_y
					/ st_cal->transform_y) / UDIV);
		st_cal->drawstart_x = -st_cal->spritewidth / 2 + st_cal->spritescreen_x;
		st_cal->drawend_x = st_cal->spritewidth / 2 + st_cal->spritescreen_x;
		if (st_cal->drawstart_x < 0)
			st_cal->drawstart_x = 0;
		if (st_cal->drawend_x >= tmp->window_size_x)
			st_cal->drawend_x = tmp->window_size_x - 1;
		input_sprite_texture(tmp, st_cal, spriteorder[i]);
	}
}

void	cal(t_struct *tmp)
{
	t_cal	st_cal;
	int		x;
	int		spriteorder[tmp->num_sprite];
	double	spritedistance[tmp->num_sprite];

	x = 0;
	tmp->zbuffer = (double*)malloc(sizeof(double) * tmp->window_size_x);
	while (x < tmp->window_size_x)
	{
		cal_dist(x, tmp, &st_cal);
		input_wall_texture(tmp, &st_cal, x);
		tmp->zbuffer[x++] = st_cal.perpwalldist;
	}
	cal_sprite(tmp, &st_cal, spriteorder, spritedistance);
	free(tmp->zbuffer);
}
