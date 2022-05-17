/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:22:40 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/17 18:44:47 by nazrinsha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_args(t_cmd *cmd)
{
	t_param	*node;

	while (cmd)
	{
		node = cmd->params;
		while (node)
		{
			if (node->param_type == ARGUMENT)
				cmd->arg_count++;
			if (node->param_type == OPTION)
				cmd->option_count++;
			cmd->param_count++;
			node = node->next;
		}
		cmd = cmd->next;
	}
}

int	minishell(t_data *data)
{
	char	*line;

	read_signals(data);
	line = readline("mini x hell % ");
	while (line != NULL)
	{
		signal(SIGINT, SIG_IGN);
		parser(data, line);
		count_args(data->cmds);
		add_history(line);
		executor(data);
		cmd_lstclear(&(data->cmds));
		data->cmd_count = 0;
		free(line);
		read_signals(data);
		line = readline("mini x hell % ");
	}
	if (!line)
	{
		free(line);
		ft_parent_exit(data, 0);
	}
	return (0);
}
