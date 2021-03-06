/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:20:56 by djeon             #+#    #+#             */
/*   Updated: 2021/02/15 17:59:31 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (src == 0)
		return (-1);
	if (size == 1 || src[0] == '\0')
		dest[0] = '\0';
	else if (size == 0)
		j = 0;
	else
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		if (i < size)
			dest[i] = '\0';
	}
	while (src[j] != 0)
		j++;
	return (j);
}
