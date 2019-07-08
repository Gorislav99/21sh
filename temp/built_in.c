/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:13:51 by mgorczan          #+#    #+#             */
/*   Updated: 2019/06/11 15:13:52 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		echo_(t_shell *shell_struct)
{
	int i;
	int	n;

	i = 1;
	n = 0;
	if (shell_struct->list->arg[1] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	while (shell_struct->list->arg[i] &&
	(!ft_strcmp(shell_struct->list->arg[i], "-n")
	|| !ft_strcmp(shell_struct->list->arg[i], "-e")))
		n = !ft_strcmp(shell_struct->list->arg[i++], "-n") ? 1 : 0;
	if (shell_struct->list->arg[i] &&
	!ft_strcmp(shell_struct->list->arg[i], "-"))
		++i;
	if (!shell_struct->list->arg[i] && n)
		return ;
	while (shell_struct->list->arg[i])
	{
		ft_printf("%s", shell_struct->list->arg[i++]);
		shell_struct->list->arg[i] ? write(1, " ", 1) : 0;
	}
	!n ? write(1, "\n", 1) : write(1, "%\n", 2);
}

static void	set_pwd(t_shell *shell_struct)
{
	char	new_dir[100];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ENV[i])
	{
		if (ft_strstr(ENV[i], "PWD"))
			break ;
		++i;
	}
	while (ENV[j])
	{
		if (ft_strstr(ENV[j], "OLDPWD"))
			break ;
		++j;
	}
	free(ENV[j]);
	ENV[j] = ft_strjoin("OLDPWD=", &ENV[i][4]);
	getcwd(new_dir, 100);
	free(ENV[i]);
	ENV[i] = ft_strjoin("PWD=", new_dir);
}

static void	back_to_oldpwd(t_shell *shell_struct)
{
	int	j;

	j = 0;
	while (ENV[j])
	{
		if (ft_strstr(ENV[j], "OLDPWD"))
			break ;
		++j;
	}
	chdir(&ENV[j][7]);
	if (ft_strstr(&ENV[j][7], "/Users/mgorczan"))
		ft_printf("~%s\n", &ENV[j][7 + 15]);
	else
		ft_printf("%s\n", &ENV[j][7]);
	set_pwd(shell_struct);
}

void		cd_(t_shell *shell_struct)
{
	int			i;
	struct stat	buff;

	i = 1;
	ARG[i] && !ft_strcmp(ARG[i], "--") ? ++i : 0;
	if (ARG[i] == NULL)
		chdir(get_home(ENV)) != -1 ? set_pwd(shell_struct) : 0;
	else if (!ft_strcmp(ARG[i], "-") && ARG[i + 1] == NULL)
		back_to_oldpwd(shell_struct);
	else if (ARG[i + 1] != NULL)
		print_error("cd: string not in pwd: ", ARG[i]);
	else
	{
		if (chdir(ARG[i]) == -1)
		{
			if (!lstat(ARG[i], &buff) && access(ARG[i], 0) != 0)
				print_error("cd: no such file or directory: ", ARG[i]);
			else if ((buff.st_mode & S_IFMT) != S_IFDIR)
				print_error("cd: not a directory: ", ARG[i]);
			else
				print_error("cd: permission denied: ", ARG[i]);
		}
		else
			set_pwd(shell_struct);
	}
}

void		exit_(t_shell *shell_struct)
{
	t_command	*temp1;
	int			i;

	while (shell_struct->list)
	{
		i = 0;
		temp1 = shell_struct->list;
		shell_struct->list = shell_struct->list->up_command;
		free_strs(temp1->arg);
		free(temp1->command);
		free(temp1);
	}
	i = 0;
	while (shell_struct->built_in[i])
		free(shell_struct->built_in[i++]);
	free(shell_struct->built_in);
	i = 0;
	while (shell_struct->environ[i])
		free(shell_struct->environ[i++]);
	free(shell_struct->environ);
	free(shell_struct);
	exit(0);
}
