/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_session.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 18:17:28 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/02 18:17:29 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_history_session *add_history(t_history_session *h_session)
{
	t_history_session *temp;
	
	if (!h_session)
	{
		if ((h_session = (t_history_session*)malloc(sizeof(t_history_session))) == NULL)
			exit(1);
		h_session->up = NULL;
		h_session->number_hist = 0;
	}
	else
	{
		if (h_session->line)
		{
			if ((h_session->down = (t_history_session*)malloc(sizeof(t_history_session))) == NULL)
					exit(1);
			temp = h_session;
			h_session = h_session->down;
			h_session->up = temp;
		}
	}
	h_session->comm.ch = '\0';
	h_session->comm.fd = 0;
	h_session->left = 0;
	h_session->lenght = 0;
	h_session->line = NULL;
	h_session->down = NULL;
	h_session->victor = init_vector();
	h_session->victor->push_back(&h_session->victor, 0);
	h_session->number_hist = 0;
	h_session->fl = 0;
	return (h_session);
}


void			clear_line(t_history_session *h_session)
{
	int i;
	int j;

	if (h_session->victor->lenght > 1)
	{
		i = 0;
		j = h_session->victor->lenght;
		while (++h_session->victor->curr_arr < h_session->victor->lenght)
			tputs(term->do_, 1, putchar_);
		h_session->victor->curr_arr--;
		while (--j > 0)
		{
			i = 0;
			while (i++ < h_session->victor->array[j])
				tputs(term->le, 1, putchar_);
			tputs(term->cd, 1, putchar_);
			tputs(term->up, 1, putchar_);
		}
		tputs(term->nd, 1, putchar_);
		tputs(term->nd, 1, putchar_);
			tputs(term->cd, 1, putchar_); // no work
	}
	else
	{
		i = 0;
		while (i++ < h_session->left)
			tputs(term->le, 1, putchar_);
		tputs(term->cd, 1, putchar_);
	}
}

void	_key_up(t_history_session *h_session)
{
	int					i;
	t_history_session	*temp;

	i = 0;
	temp = h_session;
	while (temp && i++ <= h_session->number_hist)
		temp = temp->up;
	if (!temp || !(temp->line))
		return ;
	clear_line(h_session);
	(h_session->number_hist)++;
	free(h_session->line);
	h_session->line = ft_strdup(temp->line);
	h_session->comm = temp->comm;
	h_session->left = temp->left;
	h_session->lenght = temp->lenght;
	h_session->victor = h_session->victor->copy(temp->victor);
	ft_printf("%s", h_session->line);

}

void	_key_down(t_history_session *h_session)
{
	int					i;
	t_history_session	*temp;
	char	tmp;
	i = 0;
	temp = h_session;
	while (temp && ++i < h_session->number_hist)
		temp = temp->up;
	if (!temp || !(temp->line))
		return ;
	clear_line(h_session);
	(h_session->number_hist)--;
	free(h_session->line);
	h_session->line = ft_strdup(temp->line);
	h_session->comm = temp->comm;
	h_session->left = temp->left;
	h_session->lenght = temp->lenght;
	h_session->victor = h_session->victor->copy(temp->victor);
	ft_printf("%s", h_session->line);
}


void	key_history(t_history_session *h_session, int key)
{
	int i;
	t_history_session *temp;

	i = 0;
	temp = h_session;
	if (key == KEY_UP)
		_key_up(h_session);
	else if (key == KEY_DOWN && h_session->number_hist > 1)
		_key_down(h_session);
}