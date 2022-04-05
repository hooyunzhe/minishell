/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:22:40 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/05 15:44:18 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_data *data)
{
	char	*line;

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
