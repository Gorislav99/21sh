/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 10:25:35 by mgorczan          #+#    #+#             */
/*   Updated: 2018/12/01 10:25:36 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_lenword(const char *s, char c)
{
	int i;

	i = 0;
	while (*s == c)
		s++;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

static	int		ft_kwords(char const *s, char c)
{
	int len;
	int k;

	k = 1;
	len = 0;
	while (*s)
	{
		if (*s != c && k)
		{
			k = 0;
			len++;
		}
		if (*s == c)
			k = 1;
		s++;
	}
	return (len);
}

static	void	ft_op(char const *s, char c, char **str, int lenght)
{
	int j;
	int i;

	i = 0;
	while (i < lenght)
	{
		j = 0;
		str[i] = ft_strnew(ft_lenword(s, c) + 1);
		if (!str[i])
		{
			while (j <= --i)
				free(str[i]);
			str = NULL;
			return ;
		}
		while (*s == c)
			s++;
		while (*s != c && *s)
			str[i][j++] = *s++;
		i++;
	}
	str[i] = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		lenght;

	if (s != NULL)
		lenght = ft_kwords(s, c);
	else
		return (NULL);
	str = (char**)malloc(sizeof(char*) * (lenght + 1));
	if (str != NULL)
		ft_op(s, c, str, lenght);
	else
		return (NULL);
	return (str);
}
