/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:48:58 by mac               #+#    #+#             */
/*   Updated: 2021/02/24 13:09:29 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init(t_struct *tmp, int argc, char **argv)
{
	int			fd;

	struct_init(tmp);
	tmp->mlx = mlx_init();
	if (!(tmp->texture_arr = init_intarr(tmp, 64 * 64, 5)))
		return (-1);
	if (check_arg(tmp, argc, argv) == -1)
		return (-1);
	if (!(fd = open(argv[1], O_RDONLY)))
		return (-1);
	if (parse_cub(fd, tmp) == -1)
	{
		ft_putstr("parsing error\n");
		return (-1);
	}
	close(fd);
	init_sprite(tmp);
	if (malloc_buf(tmp) == -1)
		return (-1);
	if (tmp->error == 1)
	{
		ft_putstr("init error\n");
		return (-1);
	}
	return (0);
}

void	draw(t_struct *tmp)
{
	int		i;
	int		j;

	i = -1;
	while (++i < tmp->window_size_y)
	{
		j = -1;
		while (++j < tmp->window_size_x)
			tmp->data[tmp->window_size_x * i + j] = tmp->buf[i][j];
	}
	if (tmp->bmp_flag == 1)
	{
		save_bmp(tmp);
		exit(0);
	}
	else
		mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, 0, 0);
}

int		main_loop(t_struct *tmp)
{
	cal(tmp);
	draw(tmp);
	user_move(tmp);
	return (0);
}

int		ft_tool_close(t_struct *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_struct	tmp;

	if (init(&tmp, argc, argv) == -1)
		return (-1);
	if (tmp.bmp_flag == 0)
		tmp.win = mlx_new_window(tmp.mlx, tmp.window_size_x, tmp.window_size_y,
				"djeon's cub3D");
	tmp.img = mlx_new_image(tmp.mlx, tmp.window_size_x, tmp.window_size_y);
	tmp.data = (int *)mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.size_l,
			&tmp.endian);
	mlx_loop_hook(tmp.mlx, &main_loop, &tmp);
	if (tmp.bmp_flag == 0)
	{
		mlx_hook(tmp.win, 2, 0, &key_press, &tmp);
		mlx_hook(tmp.win, 3, 0, &key_release, &tmp);
		mlx_hook(tmp.win, 17, 0, ft_tool_close, &tmp);
	}
	mlx_loop(tmp.mlx);
}
