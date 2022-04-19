/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_newfunc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:52:26 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/19 16:04:56 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_param	*new_param(char *param_str, param param_type, redirection redirection_type)
{
	t_param	*params;
	
	params = malloc(sizeof(t_param));
	params->param_str = param_str;
	params->param_type = param_type;
	params->redirection_type = redirection_type;
	params->next = NULL;
	return (params);
}

t_cmd	*new_cmd(void)
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

t_data	*new_data(char **envp)
{
	t_data	*data;
	t_term	original_term;

	data = malloc(sizeof(t_data));
	data->cmds = NULL;
	data->envp = envp;
	data->cmd_count = 0;
	tcgetattr(0, &original_term);
	data->original_term = original_term;
	data->exit_status = 0;
	return (data);
}
