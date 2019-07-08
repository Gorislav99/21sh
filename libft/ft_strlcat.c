/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:59:17 by mgorczan          #+#    #+#             */
/*   Updated: 2018/11/28 17:59:21 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const char	*s;
	char		*d;
	size_t		l;
	size_t		d_l;

	d = dst;
	s = src;
	l = size;
	while (l-- != 0 && *d != '\0')
		d++;
	d_l = d - dst;
	l = size - d_l;
	if (l == 0)
		return (d_l + ft_strlen(s));
	while (*s != '\0')
	{
		if (l != 1)
		{
			*d++ = *s;
			l--;
		}
		s++;
	}
	*d = '\0';
	return (d_l + (s - src));
}
