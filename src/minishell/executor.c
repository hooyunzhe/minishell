/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:57:34 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/11 16:22:08 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtolower(char *str)
{
	int 	i;
	char	*res;

	i = -1;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[++i])
		res[i] = ft_tolower(str[i]);
	res[i] = '\0';
	return (res);
}

int		check_builtin(t_param *param)
{
	t_param	*command;
	char	*lower_str;

	command = param_lstfind(param, COMMAND, 0);
	lower_str = ft_strtolower(command->param_str);
	if (!ft_strncmp(lower_str, "echo", 4))
		return (MINI_ECHO);
	if (!ft_strncmp(lower_str, "cd", 2))
		return (MINI_CD);
	if (!ft_strncmp(lower_str, "pwd", 3))
		return (MINI_PWD);
	if (!ft_strncmp(lower_str, "export", 6))
		return (MINI_EXPORT);
	if (!ft_strncmp(lower_str, "unset", 5))
		return (MINI_UNSET);
	if (!ft_strncmp(lower_str, "env", 3))
		return (MINI_ENV);
	if (!ft_strncmp(lower_str, "exit", 4))
		return (MINI_EXIT);
	free(lower_str);
	return (-1);
}

void	execute_builtin(t_data *data, t_cmd *cmd, builtin_cmd type)
{
	if (type == MINI_ECHO)
		mini_echo(cmd->params);
	else if (type == MINI_CD)
		mini_chdir(data, cmd);
	else if (type == MINI_PWD)
		mini_pwd();
	else if (type == MINI_EXPORT)
		mini_export(data, cmd);
	else if (type == MINI_UNSET)
		mini_unset(data, cmd);
	else if (type == MINI_ENV)
		mini_env(data);
	else if (type == MINI_EXIT)
		exit(0);
}

void	executor(t_data *data)
{
	t_cmd		*node;
	builtin_cmd	type;

	node = data->cmds;
	while (node)
	{
		check_redirection();
		type = check_builtin(node->params);
		if (type >= 0)
			execute_builtin(data, node->params, type);
		// else
		// 	execute();
		node = node->next;
	}
}