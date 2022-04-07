/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:22:40 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/07 15:48:43 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_args(t_cmd *cmd)
{
	t_param	*node;

	while(cmd)
	{
		node = cmd->params;
		while (node)
		{
			if (node->param_type == ARGUMENT)
				cmd->arg_count++;
			cmd->param_count++;
			node = node->next;
		}
		cmd = cmd->next;
	}
}

int	minishell(t_data *data)
{
	char	*line;

	read_signals();
	line = readline("minishell % ");
	while (line != NULL)
	{
		parser(data, line);
		count_args(data->cmds);
		mini_echo(data->cmds);
		while (data->cmds)
		{
			//printf("params: ");
			while (data->cmds->params != NULL)
			{
				//printf("[[%s], %d, %d] \n", data->cmds->params->param_str, data->cmds->params->param_type, data->cmds->params->redirection_type);
				//printf("here = [%s]\n", data->cmds->params->param_str);
				data->cmds->params = data->cmds->params->next;
			}
			//printf("param_count: %d\n", data->cmds->param_count);
			//printf("\n");
			data->cmds = data->cmds->next;
		}
		free(line);
		line = readline("minishell % ");
	}
	if (!line)
	{
		printf("exit\n");
		exit(0); //change to our own exit function later
	}
	return (0);
}
