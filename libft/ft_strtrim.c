/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 13:10:04 by mgorczan          #+#    #+#             */
/*   Updated: 2018/12/03 13:10:05 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		start;
	int		end;

	start = 0;
	if (s == NULL)
		return (NULL);
	while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		start++;
	if (start == (int)ft_strlen(s))
		return (ft_strnew(1));
	end = ft_strlen(s) - 1;
	while ((s[end] == ' ' || s[end] == '\t' || s[end] == '\n') && (end > start))
		end--;
	str = ft_strnew(end - start + 1);
	if (str == NULL)
		return (NULL);
	ft_strncpy(str, &s[start], (end - start + 1));
	return (str);
}
