/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:22:40 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/04 15:41:54 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define _SVID_SOURCE 1

struct termios	termios_save;	

sig_atomic_t	the_flag = 0;

void	do_stuff(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	minishell(t_data *data)
{
	char	*line;
	signal(2, do_stuff);
	line = readline("minishell % ");
	while (line != NULL)
	{
		parser(data, line);
		free(line);
		data->arg_count = 0;
		line = readline("minishell % ");
	}
	return (0);
}
