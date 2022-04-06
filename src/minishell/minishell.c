/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:22:40 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/06 10:42:23 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t sigflag = 0;

struct termios	saved;

void	reset_the_terminal()
{
	tcsetattr(0, 0,  &saved);
}

void	handle_signal(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		sigflag = 2;
	}
	else if (num == SIGQUIT)
	{
		write(1, "minishell % ", ft_strlen("minishell % "));
		write(1, rl_line_buffer, ft_strlen(rl_line_buffer));
		sigflag = 3;
	}
}

void	read_signals()
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

int	minishell(t_data *data)
{
	char	*line;
	struct	termios	new;

	tcgetattr(0 , &saved);
	atexit(reset_the_terminal); //change this later illegal funcitno ujst reset the terminal normall on exit

	new = saved;
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &new);
	read_signals();

	line = readline("minishell % ");
	while (line != NULL)
	{
		parser(data, line);
		while (data->cmds)
		{
			printf("params: ");
			while (data->cmds->params != NULL)
			{
				printf("[[%s], %d, %d] ", data->cmds->params->param_str, data->cmds->params->param_type, data->cmds->params->redirection_type);
				data->cmds->params = data->cmds->params->next;
			}
			printf("param_count: %d\n", data->cmds->param_count);
			data->cmds = data->cmds->next;
			printf("\n");
		}
		free(line);
		line = readline("minishell % ");
	}
	return (0);
}
