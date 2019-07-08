/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:12:53 by mgorczan          #+#    #+#             */
/*   Updated: 2018/11/30 15:12:57 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	j = 0;
	while (haystack[j] && j < len)
	{
		i = 0;
		while (((i + j) <= len) && (haystack[i + j] == needle[i]
					|| needle[i] == '\0'))
		{
			if (!needle[i])
				return ((char*)haystack + j);
			i++;
		}
		j++;
	}
	return (NULL);
}
