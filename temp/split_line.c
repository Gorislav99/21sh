/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:20:13 by mgorczan          #+#    #+#             */
/*   Updated: 2019/06/08 17:20:15 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	count_arg_assist(char *line, int *count, int *fl)
{
	if (line[0] != ' ' && line[0] != '\t' && *fl)
	{
		(*count)++;
		*fl = 0;
	}
	if (line[0] == ' ' || line[0] == '\t')
		*fl = 1;
}

static int	count_arg(char *line, int count)
{
	int		i;
	int		fl;
	char	temp;

	i = 0;
	count = 0;
	fl = 1;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			temp = (line[i++] == '\"') ? '\"' : '\'';
			while (line[i] != '\0' && line[i] != temp)
				++i;
			if (line[i++] == '\0' && fl)
				return (++count);
			if ((line[i] == '\0' || line[i] == ' ' || line[i] == '\t') && fl)
				++count;
			if (line[i] == '\0')
				return (count);
		}
		count_arg_assist(&line[i++], &count, &fl);
	}
	return (count);
}

static int	commas_(char **comm, int i, char **environ)
{
	int temp;
	int	lenght;

	lenght = 0;
	temp = 0;
	++i;
	if ((*comm)[i] == '\'')
	{
		while ((*comm)[i] && (*comm)[i] != '\'')
			++i;
		i += (*comm)[i] ? 1 : 0;
	}
	else if ((*comm)[i] == '\"')
	{
		while ((*comm)[i] && (*comm)[i] != '\"')
		{
			lenght = i;
			if ((*comm)[i] == '$' &&
			!ft_strcmp(environ_varible(*comm, &lenght, &temp, environ), " "))
				cut_str(comm, i, lenght);
			else
				++i;
		}
	}
	return (i);
}

void		free_false_env(char **comm, char **environ)
{
	int	i;
	int	lenght;
	int	temp;

	i = 0;
	lenght = 0;
	temp = 0;
	while ((*comm)[i])
	{
		if ((*comm)[i] == '\'' || (*comm)[i] == '\"')
		{
			i = commas_(comm, i, environ);
		}
		else
		{
			lenght = i;
			if ((*comm)[i] == '$' &&
			!ft_strcmp(environ_varible(*comm, &lenght, &temp, environ), " "))
			{
				cut_str(comm, i++, lenght);
			}
			else
				++i;
		}
	}
}

int			split_line(t_shell *shell_struct, char **comm)
{
	int		count;
	int		fd;

	count = 0;
	if (!comm && !(*comm))
		return (0);
	free_false_env(comm, ENV);
	count = count_arg(*comm, count);
	if (count == 0)
	{
		fd = 1;
		return (0);
	}
	fd = 0;
	if ((ARG = (char**)malloc(sizeof(char*) * (count + 1))) == NULL)
		exit(1);
	if (write_args(shell_struct, *comm, count))
	{
		free_strs(ARG);
		ARG = NULL;
		return (0);
	}
	return (1);
}
