/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:19:43 by mgorczan          #+#    #+#             */
/*   Updated: 2018/11/28 16:20:14 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		lenght;
	int		i;
	char	*s;

	i = 0;
	lenght = 0;
	while (s1[lenght])
	{
		lenght++;
	}
	s = (char*)malloc(sizeof(char) * (lenght + 1));
	if (s == NULL)
		return (NULL);
	while (i < lenght)
	{
		s[i] = s1[i];
		i++;
	}
	s[lenght] = '\0';
	return (s);
}
