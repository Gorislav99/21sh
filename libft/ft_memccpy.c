/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:17:20 by mgorczan          #+#    #+#             */
/*   Updated: 2018/11/26 15:17:22 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (((char*)src)[i] == (char)c)
		{
			((char*)dst)[i] = ((char*)src)[i];
			return (dst + i + 1);
		}
		else
			((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	return (NULL);
}
