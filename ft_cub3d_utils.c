/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:48:37 by mac               #+#    #+#             */
/*   Updated: 2021/02/20 19:48:38 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	double_pointer_free(char **mem, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		free(mem[i]);
	free(mem);
}

int		white_space(char line)
{
	if (line >= 9 && line <= 13)
		return (1);
	return (0);
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < amount)
	{
		j = -1;
		while (++j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sortsprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	i = -1;
	while (++i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	i = -1;
	while (++i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void	load_image(t_struct *tmp, int *texture, char *path)
{
	int		x;
	int		y;

	y = -1;
	if (!(tmp->img = mlx_xpm_file_to_image(tmp->mlx, path, &tmp->image_width,
			&tmp->image_height)))
	{
		ft_putstr("invalid textures path\n");
		exit(-1);
	}
	tmp->data = (int *)mlx_get_data_addr(tmp->img, &tmp->bpp, &tmp->size_l,
			&tmp->endian);
	while (++y < tmp->image_height)
	{
		x = -1;
		while (++x < tmp->image_width)
			texture[tmp->image_width * y + x] =
				tmp->data[tmp->image_width * y + x];
	}
	mlx_destroy_image(tmp->mlx, tmp->img);
}
