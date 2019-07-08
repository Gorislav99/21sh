/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:54:44 by mgorczan          #+#    #+#             */
/*   Updated: 2018/12/01 15:55:00 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	ch;
	char			buf[2];

	ch = (unsigned char)c;
	if (ch > 127)
	{
		buf[0] = ch >> 6 | 0b11000000;
		buf[1] = ch & 0b10111111;
		write(fd, buf, 2);
	}
	else
		write(fd, &c, 1);
}
