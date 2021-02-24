/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:47:32 by mac               #+#    #+#             */
/*   Updated: 2021/02/22 15:08:54 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	struct_init(t_struct *tmp)
{
	tmp->dir_x = 0;
	tmp->dir_y = 0;
	tmp->plane_x = 0;
	tmp->plane_y = 0;
	tmp->map_size_x = 0;
	tmp->map_size_y = 0;
	tmp->parse_tmp = 0;
	tmp->num_sprite = 0;
	tmp->error = 0;
	tmp->last_line = 0;
	tmp->w_key = 0;
	tmp->s_key = 0;
	tmp->a_key = 0;
	tmp->d_key = 0;
	tmp->left_arrow = 0;
	tmp->right_arrow = 0;
	tmp->bmp_flag = 0;
	tmp->pos_tmp = 0;
}

void	init_sprite(t_struct *tmp)
{
	int			i;
	int			j;
	int			index;

	if (!(tmp->sprite = (t_sprite*)malloc(sizeof(t_sprite)
					* (tmp->num_sprite + 1))))
		tmp->error = 1;
	index = 0;
	i = -1;
	while (++i < tmp->map_size_y)
	{
		j = -1;
		while (tmp->map[i][++j] != '\0')
		{
			if (tmp->map[i][j] == '2')
			{
				tmp->sprite[index].x = j + 0.5;
				tmp->sprite[index].y = i + 0.5;
				tmp->sprite[index++].texture = 4;
			}
		}
	}
	tmp->sprite[index].x = '\0';
	tmp->sprite[index].y = '\0';
	tmp->sprite[index].texture = '\0';
}

int		**init_intarr(t_struct *tmp, int x, int y)
{
	int			**int_arr;
	int			i;
	int			j;

	if (!(int_arr = (int**)malloc(sizeof(int*) * y)))
	{
		tmp->error = 1;
		return (0);
	}
	i = -1;
	while (++i < y)
		if (!(int_arr[i] = (int*)malloc(sizeof(int) * x)))
		{
			tmp->error = 1;
			return (0);
		}
	i = -1;
	while (++i < y)
	{
		j = -1;
		while (++j < x)
			int_arr[i][j] = 0;
	}
	return (int_arr);
}

int		check_arg(t_struct *tmp, int argc, char **argv)
{
	int			i;

	if (!(argc > 1 && argc < 4))
	{
		ft_putstr("input error\n");
		return (-1);
	}
	i = ft_strlen(argv[1]) - 4;
	if (ft_strncmp(&argv[1][i], ".cub", 4) != 0)
	{
		ft_putstr("input error\n");
		return (-1);
	}
	if (argc > 2)
	{
		if (!ft_strncmp(argv[2], "--save", 6))
			tmp->bmp_flag = 1;
		else
		{
			ft_putstr("invalid arg\n");
			return (-1);
		}
	}
	return (0);
}

int		malloc_buf(t_struct *tmp)
{
	int			i;
	int			j;

	if (!(tmp->buf = (int**)malloc(sizeof(int*) * tmp->window_size_y)))
		return (-1);
	i = -1;
	while (++i < tmp->window_size_y)
		if (!(tmp->buf[i] = (int*)malloc(sizeof(int) * tmp->window_size_x)))
			return (-1);
	i = -1;
	while (++i < tmp->window_size_y)
	{
		j = -1;
		while (++j < tmp->window_size_x)
			tmp->buf[i][j] = 0;
	}
	return (0);
}
