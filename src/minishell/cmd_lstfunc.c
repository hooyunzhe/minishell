/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:20:37 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 14:21:49 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_lstnew(void)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	cmds->params = NULL;
	cmds->next = NULL;
	cmds->param_count = 0;
	cmds->arg_count = 0;
	cmds->option_count = 0;
	cmds->input_fd = 0;
	cmds->output_fd = 1;
	return (cmds);
}

void	cmd_lstadd_back(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (cmd)
	{
		if (*cmd)
		{
			last = *cmd;
			while (last->next != NULL)
				last = last->next;
			last->next = new_cmd;
		}
		else
			*cmd = new_cmd;
	}
}

void	cmd_lstclear(t_cmd **cmds)
{
	t_cmd	*temp;
	
	while (*cmds != NULL)
	{
		temp = (*cmds)->next;
		param_lstclear(&((*cmds)->params));
		free(*cmds);
		*cmds = temp;
	}
}
