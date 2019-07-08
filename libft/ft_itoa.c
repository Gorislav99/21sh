/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 13:37:41 by mgorczan          #+#    #+#             */
/*   Updated: 2018/12/01 13:37:43 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_nblen(int n)
{
	if (n / 10 > 0 || n / 10 < 0)
		return (1 + ft_nblen(n / 10));
	else
		return (1);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		len;
	int		k;

	if (n >= 0)
		k = 0;
	else
		k = 1;
	len = ft_nblen(n) + k;
	s = ft_strnew(len);
	if (s == NULL)
		return (NULL);
	while (len--)
	{
		if (!k)
			s[len] = n % 10 + '0';
		else
			s[len] = -1 * (n % 10 - '0');
		n /= 10;
	}
	if (k)
		s[0] = '-';
	return (s);
}
