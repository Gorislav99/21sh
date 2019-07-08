/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 18:03:14 by mgorczan          #+#    #+#             */
/*   Updated: 2018/12/02 18:03:15 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *l;

	if (alst != NULL && del != NULL && *alst != NULL)
	{
		while (*alst != NULL)
		{
			l = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = l;
		}
		*alst = NULL;
	}
}
