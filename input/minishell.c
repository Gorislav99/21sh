/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:25:30 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/01 14:03:14 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <term.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <termios.h>
# include <limits.h>
# include <time.h>
static struct termios	stored_settings;
# include <stdio.h>
# include "term.h"


static int	get_new_line_comm(char **line, char **comm, int i, int j)
{
	char *temp;

	if ((*line)[i] == ';')
	{
		if ((*line)[i + 1] == ';' ||
		(*line)[i + 1] == '&' || (*line)[i + 1] == '|')
		{
			temp = ft_strsub(*line, i, 3);
			temp[2] = '\'';
			print_error("zsh: parse error near `", temp);
			free(temp);
			return (0);
		}
		*comm = ft_strsub(*line, 0, i);
		j = i + 1;
		while ((*line)[j] != '\0')
			++j;
		temp = *line;
		*line = ft_strsub(temp, i + 1, j);
		free(temp);
		return (1);
	}
	*comm = *line;
	*line = ft_strdup("\0");
	return (1);
}

static int	several_arg(char **line, char **comm)
{
	int		i;
	int		j;
	char	temp2;

	i = 0;
	j = 0;
	temp2 = '\"';
	while (21)
	{
		while ((*line)[i] != '\0' && (*line)[i] != ';')
		{
			if (j % 2 == 0 && ((*line)[i] == '\'' || (*line)[i] == '\"'))
			{
				temp2 = (*line)[i];
				++j;
			}
			else if (j != 0 && (j % 2) != 0 && (*line)[i] == temp2)
				++j;
			++i;
		}
		if (j % 2 == 0)
			break ;
		++i;
	}
	return (get_new_line_comm(line, comm, i, j));
}

static void	sigint_(int x)
{
	x = 0;
	if (!g_proc)
	{
		ft_printf("\b\b  \n");
		write(1, "\033[92m$>", ft_strlen("\033[92m$>"));
		// ft_printf("$>");
	}
}
void		loop(t_shell *shell_struct, char **line)
{
	char	*comm;

	while (ft_strcmp(*line, "\0"))
	{
		if (!several_arg(line, &comm))
			break ;
		///////////
		if (!split_line(shell_struct, &comm))
		{
			free(comm);
			continue ;
		}
		if (!launch_built_in(shell_struct))
			launch_command(shell_struct);
		free_strs(shell_struct->list->arg);
		shell_struct->list->arg = NULL;
		free(comm);
	}
}

void	set_keypress(void)
{
	struct termios	new_settings;

	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON & ~ECHO);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
	return ;
}

void	reset_keypress(void)
{
	tcsetattr(0, TCSANOW, &stored_settings);
	return;
}

char		*get_termcap(char **environ)
{
	char	*term;
	char	*term_edit;
	
	if ((term = ft_strnew(2048)))
	{
		if ((term_edit = ft_strdup(get_env("TERM", environ))))
		{
			tgetent(term, term_edit);
			if (tgetent(term, term_edit) == 1)
				return (term);
		}
		free(term);
	}
	return (NULL);
}

void	set_termenv(char *termcap)
{
	term = (t_term *)malloc(sizeof(t_term));
	term->le = tgetstr("le", &termcap);
	term->nd = tgetstr("nd", &termcap);
	term->cd = tgetstr("cd", &termcap);
	term->dc = tgetstr("dc", &termcap);
	term->im = tgetstr("im", &termcap);
	term->ei = tgetstr("ei", &termcap);
	term->so = tgetstr("so", &termcap);
	term->se = tgetstr("se", &termcap);
	term->up = tgetstr("up", &termcap);
	term->do_ = tgetstr("do", &termcap);


}

int			main(int argc, char **argv, char **environ)
{
	char	*line;
	t_shell	*shell_struct;
	char	*termcap;

	shell_struct = init_shell(environ);
	argc = -1;
	argv = NULL;
	//signal(SIGINT, sigint_);
	if ((termcap = get_termcap(shell_struct->environ)))
		set_termenv(termcap);
	set_keypress();
	t_history_session *h_session;

	h_session = NULL;
//	 ft_printf("\nline: %s", input(&h_session))


	while (21)
	{
		g_proc = 0;
		// ft_printf("$>");
		write(1, "\033[36m------------------------------------------------------\n", ft_strlen("\033[36m------------------------------------------------------\n"));
		write(1, "\033[36m$>\033[37m", ft_strlen("\033[36m$>\033[37m"));
		line = input(&h_session);
		if (ft_strcmp(line, "\0"))
			shell_struct->list = add_list(shell_struct->list, line);
		loop(shell_struct, &line);
		free(line);
	}
	reset_keypress();
	return (0);
}
