/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:15:21 by mgorczan          #+#    #+#             */
/*   Updated: 2018/11/30 18:15:22 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *s;

	if ((s = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	ft_memset(s, '\0', size + 1);
	return (s);
}
