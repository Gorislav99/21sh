/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:52:27 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/02 15:52:28 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_readkey(int fd)
{
	int		ret;
	char	*b;
	int		res;
	int		i;

	b = ft_strnew(6);
	res = -1;
	if (b != NULL)
	{
		if ((ret = read(fd, &b[0], 6)) > 0)
		{
			res = b[0];
			if (b[0] == KEY_ESC && ret > 1)
			{
				i = 0;
				while (b[++i] != '\0')
					res += b[i];
				res += 1000;
			}
		}
		free(b);
	}
	return (res);
}

int	putchar_(int c)
{
	write(1, &c, 1);
	return (0);
}

static void _commas(t_history_session *h_session, int key)
{

	if ((key == '\"' || key == '\'') && (h_session->comm.fd % 2 == 0))
	{
		++(h_session->comm.fd);
		h_session->comm.ch = key;
	}
	else if (key == h_session->comm.ch  && h_session->comm.fd % 2 != 0)
		++(h_session->comm.fd);
}

void	key_func(t_history_session *h_session, int key)
{

	if (key == KEY_BS)
		_backspace(h_session);
	else if (key == KEY_LEFT)
		_left(h_session);
	else if (key == KEY_RIGHT)
		_right(h_session);
	else if (key < 255 && key >= 32)
		_print(h_session, key, 1);
}



int		_enter(t_history_session *h_session, int key)
{
	int	*temp;
	int	i;
	int sum;

	i = 0;
	sum = 0;
	if (h_session->comm.fd % 2 == 0)
	{
		if (h_session->line && h_session->line[0] == '\0')
		{
			free(h_session->line);
			h_session->line = NULL;
		}
		write(1, "\n", 1);
		return (1);
	}
	while (h_session->victor->curr_arr < h_session->victor->lenght - 1)
	{
		h_session->victor->curr_arr++;
		tputs(term->do_, 1, putchar_);
	}
	h_session->victor->push_back(&(h_session->victor), 0);
	_print(h_session, key, 0);
	(h_session)->fl = 1;
	h_session->left = h_session->lenght;
	ft_printf("%s", "dquote> ");
	return (0);
}

char	*input(t_history_session **h_session)
{
	int		key;

	*h_session = add_history(*h_session);
	while (21)
	{
		key = ft_readkey(0);
		(key == '\"' || key == '\'') ? _commas(*h_session, key) : 0;
		if (key == -1)
			break ;
		if (key == KEY_TAB)
			continue ;
		if (key == KEY_NL && _enter(*h_session, key))
			break ;
		if ((key == KEY_UP || key == KEY_DOWN) && !(*h_session)->fl)
			key_history(*h_session, key);
		else
			(*h_session)->number_hist = 0;
		key_func(*h_session, key);
	}
	ft_printf("(*h_session)->left = %i\n", (*h_session)->left);
	(*h_session)->victor->curr_arr =(*h_session)->victor->lenght - 1;
	(*h_session)->left =(*h_session)->lenght;
	(*h_session)->fl = 0;
	int i; 
	i = 0;
	ft_printf("--------------------------------------\n");
	ft_printf("(*h_session)->victor->lenght = %i\n", (*h_session)->victor->lenght);
	ft_printf("(*h_session)->victor->curr_arr = %i\n", (*h_session)->victor->curr_arr);
	ft_printf("(*h_session)->lenght = %i\n", (*h_session)->lenght);
	ft_printf("--------------------------------------\nvector:\n");
	while (i < (*h_session)->victor->lenght)
		ft_printf("%i\n", (*h_session)->victor->array[i++]);
	ft_printf("--------------------------------------\n");
	
	
	return ((*h_session)->lenght == 0 ? ft_strdup("\0") : ft_strdup((*h_session)->line));
}

