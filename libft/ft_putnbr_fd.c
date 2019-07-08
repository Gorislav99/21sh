/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:13:06 by mgorczan          #+#    #+#             */
/*   Updated: 2018/12/01 16:13:08 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n > -10 && n < 10)
	{
		if (n > -10 && n < 0)
		{
			ft_putchar_fd('-', fd);
			ft_putchar_fd(-1 * (n % 10 - '0'), fd);
		}
		else
			ft_putchar_fd(n % 10 + '0', fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		if (n >= 0)
			ft_putchar_fd(n % 10 + '0', fd);
		else
			ft_putchar_fd(-1 * (n % 10 - '0'), fd);
	}
}
