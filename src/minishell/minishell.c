/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:22:40 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/04 15:43:09 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int num)
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

	signal(2, handler);
	line = readline("minishell % ");
	while (line != NULL)
	{
		parser(data, line);
		printf("params: ");
		while (data->cmds->params != NULL)
		{
			printf("[%s] ", data->cmds->params->param_str);
			data->cmds->params = data->cmds->params->next;
		}
		printf("\n");
		free(line);
		line = readline("minishell % ");
	}
	return (0);
}
