/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon </var/mail/djeon>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:51:40 by djeon             #+#    #+#             */
/*   Updated: 2021/02/20 14:26:40 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int			write_bmp_header(int fd, int filesize, t_struct *info)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = info->window_size_x;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = info->window_size_y;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[26] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(32);
	set_int_in_char(bmpfileheader + 38, 5000);
	set_int_in_char(bmpfileheader + 42, 5000);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

void		bmp_pixel_date(int file, t_struct *info)
{
	int				x;
	int				y;
	unsigned int	color;

	y = info->window_size_y;
	x = -1;
	while (--y >= 0)
	{
		while (++x < info->window_size_x)
		{
			color = info->data[info->size_l /
							(info->bpp / 8) * y + x];
			write(file, &color, 4);
		}
		x = -1;
	}
}

int			save_bmp(t_struct *tmp)
{
	t_struct		*w;
	int				filesize;
	int				file;

	w = tmp;
	filesize = 2 + 54 + (tmp->window_size_x * tmp->window_size_y) * 4;
	if (!(file = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)))
		return (0);
	if (!write_bmp_header(file, filesize, tmp))
		return (0);
	bmp_pixel_date(file, w);
	close(file);
	return (1);
}
