/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:33:08 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/04 15:43:19 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_param(t_param *param, char *param_str)
{
	t_param	*prev_param;
	t_param	*new_param;

	if (param->param_str == NULL)
	{
		param->param_str = param_str;
		param->param_type = COMMAND;
	}
	else
	{
		new_param = init_param();
		new_param->param_str = param_str;
		if (param_str[0] == '-')
			new_param->param_type = OPTION;
		else
			new_param->param_type = ARGUMENT;
		while (param->next != NULL)
		{
			if (param->next->next == NULL)
				prev_param = param;
			param = param->next;
		}
		// if (param_str[0] == )
		param->next = new_param;
	}
}

void	append_cmd(t_cmd **cmd, t_cmd *new_cmd)
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