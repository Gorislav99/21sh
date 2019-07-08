/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:44:52 by mgorczan          #+#    #+#             */
/*   Updated: 2019/06/21 13:44:59 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**init_built_in(void)
{
	char **built_in;

	if ((built_in = (char**)malloc(sizeof(char*) * 7)) == NULL)
		exit(1);
	(built_in[0] = ft_strdup("echo")) == NULL ? exit(1) : 0;
	(built_in[1] = ft_strdup("cd")) == NULL ? exit(1) : 0;
	(built_in[2] = ft_strdup("setenv")) == NULL ? exit(1) : 0;
	(built_in[3] = ft_strdup("unsetenv")) == NULL ? exit(1) : 0;
	(built_in[4] = ft_strdup("env")) == NULL ? exit(1) : 0;
	(built_in[5] = ft_strdup("exit")) == NULL ? exit(1) : 0;
	built_in[6] = NULL;
	return (built_in);
}

t_shell		*init_shell(char **environ)
{
	t_shell	*shell_struct;
	int		i;

	if ((shell_struct = (t_shell*)malloc(sizeof(t_shell))) == NULL)
		exit(1);
	i = 0;
	while (environ[i])
		++i;
	if ((shell_struct->environ =
(char**)malloc(sizeof(char *) * (i + 1))) == NULL)
		exit(1);
	shell_struct->environ[i] = NULL;
	while (--i >= 0)
		shell_struct->environ[i] = ft_strdup(environ[i]);
	shell_struct->built_in = init_built_in();
	shell_struct->list = NULL;
	return (shell_struct);
}

t_command	*add_list(t_command *list, char *line)
{
	if (list == NULL)
	{
		if ((list = (t_command*)malloc(sizeof(t_command))) == NULL)
			exit(1);
		list->command = ft_strdup(line);
		list->arg = NULL;
		list->up_command = NULL;
		list->down_command = NULL;
		return (list);
	}
	if ((list->down_command = (t_command*)malloc(sizeof(t_command))) == NULL)
		exit(1);
	list->down_command->command = ft_strdup(line);
	list->down_command->arg = NULL;
	(list->down_command)->up_command = list;
	list->down_command->down_command = NULL;
	return (list->down_command);
}
