/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:42:44 by mgorczan          #+#    #+#             */
/*   Updated: 2019/06/13 19:42:45 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_(t_shell *shell_struct)
{
	int i;

	i = 0;
	while (ENV[i])
		ft_printf("%s\n", ENV[i++]);
}

char	*new_env(t_shell *shell_struct)
{
	char	*new_env;
	char	*temp;

	new_env = NULL;
	if (shell_struct->list->arg[1] == NULL)
		write(2, "setenv: not enough arguments\n", 29);
	if (!ft_strcmp(shell_struct->list->arg[1], "="))
		write(2, "zsh: bad assignment\n", 20);
	if (shell_struct->list->arg[2] == NULL)
	{
		if (ft_strstr(shell_struct->list->arg[1], "="))
			new_env = ft_strdup(shell_struct->list->arg[1]);
		else
			new_env = ft_strjoin(shell_struct->list->arg[1], "=");
	}
	else if (shell_struct->list->arg[3] == NULL)
	{
		temp = ft_strjoin(shell_struct->list->arg[1], "=");
		new_env = ft_strjoin(temp, shell_struct->list->arg[2]);
		free(temp);
	}
	return (new_env);
}

void	setenv_(t_shell *shell_struct)
{
	int		i;
	int		j;
	char	**temp;
	char	*tm;

	i = -1;
	if ((tm = new_env(shell_struct)) == NULL)
		return ;
	while (ENV[++i])
	{
		j = 0;
		while (ENV[i][j] == tm[j] && tm[j] != '=')
			++j;
		if (ENV[i][j] == tm[j])
			CHANGE_ENV;
	}
	j = -1;
	if ((temp = (char**)malloc(sizeof(char*) * (i + 2))) == NULL)
		exit(1);
	temp[i + 1] = NULL;
	while (++j < i)
		temp[j] = ENV[j];
	temp[j] = tm;
	free(ENV);
	ENV = temp;
}

int		remove_env(t_shell *shell_struct)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = -1;
	count = 0;
	while (ENV[++i])
	{
		j = 0;
		while (shell_struct->list->arg[++j])
		{
			k = 0;
			while (ENV[i][k] != '='
			&& shell_struct->list->arg[j][k] == ENV[i][k])
				++k;
			if (ENV[i][k] == '=')
			{
				free(ENV[i]);
				ENV[i] = ft_strdup("\0");
				++count;
			}
		}
	}
	return (i - count);
}

void	unset_(t_shell *shell_struct)
{
	int		j;
	int		k;
	char	**temp;
	int		count;

	if (!shell_struct->list->arg[1])
	{
		write(2, "unset: not enough arguments\n", 28);
		return ;
	}
	count = remove_env(shell_struct);
	if ((temp = (char**)malloc(sizeof(char*) * (count + 1))) == NULL)
		exit(1);
	j = 0;
	k = -1;
	while (ENV[++k])
	{
		if (ENV[k][0] != '\0')
			temp[j++] = ENV[k];
		else
			free(ENV[k]);
	}
	temp[j] = NULL;
	free(ENV);
	ENV = temp;
}
