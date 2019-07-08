/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:47:42 by mgorczan          #+#    #+#             */
/*   Updated: 2018/11/26 15:47:47 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*de;
	unsigned char	*sr;
	size_t			i;

	i = 0;
	de = (unsigned char*)dest;
	sr = (unsigned char*)src;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
		while (len--)
			de[len] = sr[len];
	else
		while (i < len)
		{
			de[i] = sr[i];
			i++;
		}
	return (dest);
}
