/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:02:37 by mgorczan          #+#    #+#             */
/*   Updated: 2018/12/01 15:02:38 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	unsigned char	ch;
	char			buf[2];

	ch = (unsigned char)c;
	if (ch > 127)
	{
		buf[0] = ch >> 6 | 0b11000000;
		buf[1] = ch & 0b10111111;
		write(1, buf, 2);
	}
	else
		write(1, &c, 1);
}
