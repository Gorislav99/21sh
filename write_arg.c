/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:36:07 by mgorczan          #+#    #+#             */
/*   Updated: 2019/06/24 17:36:09 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*environ_varible(char *line, int *i, int *lenght, char **environ)
{
	int		len;
	char	*temp;
	char	*temp2;

	len = (++(*i));
	if (!ft_isalpha(line[*i]) && !ft_isdigit(line[*i]))
	{
		*lenght += 1;
		return ("$");
	}
	while (ft_isalpha(line[len]) || ft_isdigit(line[len]))
		++len;
	temp = ft_strsub(line, *i, len - *i);
	*i = len;
	if (get_env(temp, environ))
	{
		*lenght += ft_strlen(get_env(temp, environ));
		temp2 = get_env(temp, environ);
		free(temp);
		return (temp2);
	}
	free(temp);
	*lenght += 1;
	return (" ");
}

int		tilda(char *line, char **arg, int *j2, t_shell *shell_struct)
{
	if (ft_isalpha(line[1]) || ((line[1] == '\'' ||
		line[1] == '\"') && (line[2]) && (ft_isalpha(line[2]))))
	{
		ft_strcpy(&((*arg)[*j2]), "/Users/");
		(*j2) += ft_strlen("/Users/");
		return (-1 * (*j2));
	}
	if (get_env("HOME", ENV) != NULL)
	{
		ft_strcpy(&((*arg)[*j2]), get_env("HOME", ENV));
		(*j2) += ft_strlen(get_env("HOME", ENV));
	}
	else
		(*arg)[(*j2)++] = '~';
	return (0);
}

int		commas(char *line, int *j2, char **arg, t_shell *shell_struct)
{
	int j;

	j = 0;
	if (line[(++(j)) - 1] == '\'')
	{
		while (line[j] != '\'')
			(*arg)[(*j2)++] = line[(j)++];
		(j) += (line[j] == '\'') ? 1 : 0;
		return (j);
	}
	else
	{
		while (line[j] != '\"')
		{
			if (line[j] == '$')
				ft_strcpy(&((*arg)[*j2]),
				environ_varible(line, &j, j2, ENV));
			else
			{
				(*arg)[(*j2)++] = line[(j)++];
			}
		}
	}
	(j) += (line[j] == '\"') ? 1 : 0;
	return (j);
}

char	*write_word(t_shell *shell_struct, char *line, int *j, int *fl)
{
	char	*arg;
	int		j2;
	int		temp;

	j2 = 0;
	temp = lenght_word(shell_struct, line, *j, fl);
	if ((arg = ft_strnew(temp)) == NULL)
		exit(1);
	while (j2 < temp)
	{
		if (line[*j] == '$')
			ft_strcpy(&arg[j2], environ_varible(line, j, &j2, ENV));
		if (*fl && *j == *fl)
		{
			*fl = tilda(&line[*j], &arg, &j2, shell_struct);
			(*fl == 0) ? *fl = *j : 0;
			(*j)++;
		}
		else if (line[*j] == '\'' || line[*j] == '\"')
			*j += commas(&line[*j], &j2, &arg, shell_struct);
		else if (j2 < temp)
			arg[j2++] = line[(*j)++];
	}
	arg[j2] = '\0';
	return (arg);
}

int		write_args(t_shell *shell_struct, char *line, int count)
{
	int	i;
	int	j;
	int	fl;

	i = -1;
	j = 0;
	fl = 0;
	while (++i < count)
	{
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		ARG[i] = write_word(shell_struct, line, &j, &fl);
		if (fl < 0 && access(ARG[i], 0) == -1)
		{
			write(2, "zsh: no such user or named directory: ", 38);
			j = -1 * fl;
			while (ARG[i][j] && ARG[i][j] != '/')
				write(2, &ARG[i][j++], 1);
			write(2, "\n", 1);
			ARG[i + 1] = NULL;
			return (1);
		}
	}
	ARG[i] = NULL;
	return (0);
}
