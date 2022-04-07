/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:34:52 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/07 11:39:53 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios	saved;

static void	reset_the_terminal()
{
	tcsetattr(0, 0,  &saved);
}

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

void	read_signals()
{
	struct	termios	new;

	tcgetattr(0 , &saved);
	atexit(reset_the_terminal); //change this later illegal funcitno ujst reset the terminal normall on exit
	new = saved;
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &new);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
