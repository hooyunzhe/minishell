/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:22:40 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/13 15:50:08 by hyun-zhe         ###   ########.fr       */
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

	read_signals();
	line = readline("minishell % ");
	while (line != NULL)
	{
		parser(data, line);
		count_args(data->cmds);
		add_history(line);
		executor(data);

		// t_cmd	*cmds;

		// cmds = data->cmds;
		// while (cmds)
		// {
		// 	printf("params: \n");
		// 	t_param	*params;

		// 	params = cmds->params;
		// 	while (params != NULL)
		// 	{
		// 		printf("[[%s], %d, %d] \n", params->param_str, params->param_type, params->redirection_type);
		// 		// printf("here = [%s]\n", params->param_str);
		// 		params = params->next;
		// 	}
		// 	//printf("param_count: %d\n", cmds->param_count);
		// 	printf("\n");
		// 	cmds = cmds->next;
		// }
		cmd_lstclear(&(data->cmds));
		data->cmd_count = 0;
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
