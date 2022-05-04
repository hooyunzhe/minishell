/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:14:48 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/04 15:15:17 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

builtin_cmd		check_builtin(t_param *param)
{
	t_param	*command;

	command = param_lstfind(param, COMMAND, 0);
	if (!command)
		return (NO_CMD);
	if (!ft_strncasecmp(command->param_str, "echo", 5))
		return (MINI_ECHO);
	if (!ft_strncasecmp(command->param_str, "cd", 3))
		return (MINI_CD);
	if (!ft_strncasecmp(command->param_str, "pwd", 4))
		return (MINI_PWD);
	if (!ft_strncasecmp(command->param_str, "export", 7))
		return (MINI_EXPORT);
	if (!ft_strncasecmp(command->param_str, "unset", 6))
		return (MINI_UNSET);
	if (!ft_strncasecmp(command->param_str, "env", 4))
		return (MINI_ENV);
	if (!ft_strncasecmp(command->param_str, "exit", 5))
		return (MINI_EXIT);
	return (NON_BUILTIN);
}

void	execute_builtin(t_data *data, t_cmd *cmd, builtin_cmd type)
{
	if (type == MINI_ECHO)
		mini_echo(cmd->params);
	else if (type == MINI_CD)
		mini_cd(data, cmd);
	else if (type == MINI_PWD)
		mini_pwd();
	else if (type == MINI_EXPORT)
		mini_export(data, cmd);
	else if (type == MINI_UNSET)
		mini_unset(data, cmd);
	else if (type == MINI_ENV)
		mini_env(data);
	else if (type == MINI_EXIT)
		mini_exit(data, cmd);
}
