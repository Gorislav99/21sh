/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:24:07 by mgorczan          #+#    #+#             */
/*   Updated: 2019/06/21 13:24:16 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strs(char **strs)
{
	int i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	print_error(char *error, char *name)
{
	write(2, error, ft_strlen(error));
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
}

char	*get_env(char *varible, char **environ)
{
	int	i;
	int	j;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] && environ[i][j] != '='
			&& varible[j] && environ[i][j] == varible[j])
			++j;
		if (environ[i][j] == '=')
			return (&environ[i][ft_strlen(varible) + 1]);
		i++;
	}
	return (NULL);
}

char	*get_home(char **environ)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	path = NULL;
	temp = get_env("HOME", environ);
	if (temp)
		path = ft_strjoin("/", temp);
	return (path);
}

void	cut_str(char **comm, int i, int lenght)
{
	char *temp;
	char *temp2;

	if (!comm || !(*comm))
		return ;
	temp = ft_strsub(*comm, 0, i);
	temp2 = ft_strsub(*comm, lenght, ft_strlen(*comm));
	free(*comm);
	*comm = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
}
