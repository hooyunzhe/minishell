/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:52:26 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/04 15:42:19 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_param	*init_param(void)
{
	t_param	*params;
	
	params = malloc(sizeof(t_param));
	params->param_str = NULL;
	params->param_type = 0;
	params->next = NULL;
	return (params);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	cmds->params = init_param();
	cmds->next = NULL;
	return (cmds);
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->cmds = NULL;
	data->envp = envp;
	return (data);
}