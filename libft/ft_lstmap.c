/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:19:15 by mgorczan          #+#    #+#             */
/*   Updated: 2018/12/02 17:19:18 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_op(t_list *l, int i)
{
	while (i--)
	{
		free(l);
		l = l->next;
	}
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*l;
	t_list	*lt;
	int		i;

	l = NULL;
	i = 0;
	if (lst != NULL && f != NULL)
	{
		l = f(lst);
		lt = l;
		i++;
		while (lst->next != NULL)
		{
			lt->next = f(lst->next);
			if (lt->next == NULL)
				return (ft_op(l, i));
			lt = lt->next;
			lst = lst->next;
			i++;
		}
		lt = f(lst);
	}
	return (l);
}
