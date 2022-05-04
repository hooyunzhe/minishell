/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:34:52 by nfernand          #+#    #+#             */
/*   Updated: 2022/05/04 12:37:03 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (num == SIGQUIT)
	{
		write(1, "minishell % ", ft_strlen("minishell % "));
		write(1, rl_line_buffer, ft_strlen(rl_line_buffer));
	}
}

static void	handle_signal_test(int num)
{
	if (num == SIGINT) // ctrl-c
	{
		signal_eof = 1;
		write(1, "\n", 1);
		rl_replace_line("\x0d", 1);
	}
	else if (num == SIGQUIT) //ctrl-/
	{
		write(1, "minishell % ", ft_strlen("minishell % "));
		write(1, rl_line_buffer, ft_strlen(rl_line_buffer));
	}
}

void	read_signals(t_data *data, int test)
{
	t_term	new_term;

	//atexit(reset_the_terminal); //change this later illegal funcitno ujst reset the terminal normall on exit
	new_term = data->original_term;
	new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &new_term);
	if (test == 0)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
	}
	if (test == 1)
	{
		signal(SIGINT, handle_signal_test);
		signal(SIGQUIT, handle_signal_test);
	}
}
