/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:35:14 by mgorczan          #+#    #+#             */
/*   Updated: 2019/06/23 17:35:15 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	dangare_tilda_assist(char *line, int j, int *i, int *flag2)
{
	int flag1;

	flag1 = 0;
	if (line[j] == '\"' && !flag1)
		flag1 = 1;
	if (line[j] == '\'' && !flag1)
		flag1 = 2;
	if (line[j] == '\"' && flag1 == 1)
	{
		(*i)++;
		(*flag2)++;
	}
	if (line[j] == '\'' && flag1 == 2)
	{
		(*i)++;
		(*flag2)++;
	}
}

static int	dangare_tilda(char *line, int j, int temp)
{
	int flag1;
	int flag2;
	int	i;

	flag1 = 0;
	flag2 = 1;
	i = j + temp;
	while (j < i && line[j] != '~')
	{
		dangare_tilda_assist(line, j, &i, &flag2);
		if (line[j] != '\"' && line[j] != '\'')
			break ;
		j++;
	}
	if (flag2 % 2 == 0 || line[j] != '~')
		return (0);
	++j;
	if (j >= i || line[j] == '/' || (line[j + 1] != '\0' && line[j + 1] == '/'))
		return (j - 1);
	if (ft_isalpha(line[j]) || (line[j + 1] != '\0' && ft_isalpha(line[j + 1])))
		return (j - 1);
	return (0);
}

static void	lenght_word_assist(char *line, int *i, int *lenght, char **environ)
{
	char temp;

	temp = (line[(*i)++] == '\"') ? '\"' : '\'';
	while (line[*i] != '\0' && line[*i] != temp)
	{
		if (line[*i] == '$' && temp == '\"')
		{
			environ_varible(line, i, lenght, environ);
			continue ;
		}
		(*i)++;
		(*lenght)++;
	}
}

static int	lenght_word_no_tild(char *line, char **environ)
{
	int		i;
	int		lenght;

	i = 0;
	lenght = 0;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
	{
		if (line[i] == '$')
			environ_varible(line, &i, &lenght, environ);
		else if (line[i] == '\"' || line[i] == '\'')
		{
			lenght_word_assist(line, &i, &lenght, environ);
			if (line[i++] == '\0')
				return (lenght);
		}
		else if (line[i] != ' ' && line[i] != '\t')
		{
			++lenght;
			++i;
		}
		else
			++i;
	}
	return (lenght);
}

int			lenght_word(t_shell *shell_struct, char *line, int j, int *fl)
{
	int lenght;

	lenght = lenght_word_no_tild(&line[j], ENV);
	if ((*fl = dangare_tilda(line, j, lenght)))
	{
		if (ft_isalpha(line[*fl + 1]) || (((line[*fl + 1] == '\'' ||
		line[*fl + 1] == '\"') && *fl + 2 < lenght)
								&& (ft_isalpha(line[*fl + 2]))))
			lenght += (ft_strlen("/Users/") - 1);
		else if (get_env("HOME", ENV))
			lenght += (ft_strlen(get_env("HOME", ENV)) - 1);
	}
	return (lenght);
}
