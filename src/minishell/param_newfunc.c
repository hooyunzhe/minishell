/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_newfunc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:52:26 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/04 17:29:57 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_param	*new_param(char *param_str, param param_type)
{
	t_param	*params;
	
	params = malloc(sizeof(t_param));
	params->param_str = param_str;
	params->param_type = param_type;
	params->next = NULL;
	return (params);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	cmds->params = NULL;
	cmds->next = NULL;
	return (cmds);
}

t_data	*new_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->cmds = NULL;
	data->envp = envp;
	return (data);
}
