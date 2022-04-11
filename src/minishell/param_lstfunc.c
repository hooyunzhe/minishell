/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_lstfunc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:33:08 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/11 15:21:44 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_param	*param_lstfind(t_param *node, param type, int index)
{
	while (node && node->next != NULL)
	{
		if (node->param_type == type && index == 0)
			return (node);
		index--;
		node = node->next;
	}
	return (NULL);
}

t_param	*param_lstlast(t_param *param)
{
	while (param && param->next != NULL)
		param = param->next;
	return (param);
}

void	param_lstadd_back(t_param **param, t_param *new_param)
{
	t_param	*current;

	if (param)
	{
		if (*param)
		{
			current = *param;
			while (current->next != NULL)
				current = current->next;
			current->next = new_param;
		}
		else
			*param = new_param;
	}
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
