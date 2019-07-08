/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:03:31 by mgorczan          #+#    #+#             */
/*   Updated: 2018/11/30 20:03:33 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *str;

	if (s != NULL)
		str = ft_strnew(len);
	else
		return (NULL);
	if (str != NULL)
	{
		ft_strncpy(str, s + start, len);
		return (str);
	}
	return (NULL);
}
