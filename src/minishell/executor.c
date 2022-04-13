/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:57:34 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/13 14:56:43 by hyun-zhe         ###   ########.fr       */
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

builtin_cmd		check_builtin(t_param *param)
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
	return (FAKE);
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
		mini_exit(data, cmd);
}

void	handle_redirections(t_cmd *cmd, t_param *params)
{
	while (params)
	{
		if (params->param_type == REDIRECTION)
		{
			if (params->next && params->next->param_type == IO_FILE)
			{
				if (cmd->input_fd && params->redirection_type == S_IN)
					close(cmd->input_fd);
				if (cmd->output_fd != 1 && (params->redirection_type == S_OUT
					|| params->redirection_type == D_OUT))
					close(cmd->output_fd);
				if (params->redirection_type == S_IN)
					cmd->input_fd = open(params->next->param_str, O_RDONLY);
				if (params->redirection_type == S_OUT)
					cmd->output_fd = open(params->next->param_str, O_WRONLY | O_CREAT, 0644);
				if (params->redirection_type == D_OUT)
					cmd->output_fd = open(params->next->param_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
		}
		params = params->next;
	}
}

char	**get_param_array(t_cmd *cmd)
{
	char 	**res;
	t_param	*node;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (cmd->arg_count + 2));
	node = cmd->params;
	while(node)
	{
		if (node->param_type != REDIRECTION && node->param_type != IO_FILE)
			res[i++] = ft_strdup(node->param_str);
		node = node->next;
	}
	res[i] = NULL;
	return (res);
}

char	**env_lst_to_arr(t_envp *envp)
{
	char	**res;
	char	*temp;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (env_lst_getlen(envp) + 1));
	while (envp)
	{
		temp = ft_strjoin(envp->key, "=");
		res[i] = ft_strjoin(temp, envp->value);
		free(temp);
		envp = envp->next;
	}
	res[i] = NULL;
	return (res);
}

void	execute_command(t_data *data, t_cmd *cmd, t_param *command_str)
{
	int		i;
	char	**params;
	char	**paths;
	char	**envp;
	char	*fullpath;
	char	*temp;
	pid_t	pid;

	params = get_param_array(cmd);
	paths = ft_split(mini_getenv(data, "PATH"), ':');
	envp = env_lst_to_arr(data->mini_envp);
	pid = fork();
	i = 0;
	if (pid == 0)
	{
		while (paths[i])
		{
			temp = ft_strjoin(paths[i], "/");
			fullpath = ft_strjoin(temp, command_str->param_str);
			// printf("full path = %s\n", fullpath);
			// int j = 0;
			// printf("params{");
			// while (params[j])
			// 	printf("%s ", params[j++]);
			// printf("}\n");
			// j = 0;
			// printf("envp{");
			// while (envp[j])
			// 	printf("%s ", envp[j++]);
			// printf("}\n");
			execve(fullpath, params, envp);
			i++;
		}
		handle_error(EXE_NOCMD, command_str->param_str);
		exit(127);
	}
	int	status;
	waitpid(pid, &status, 0);
	printf("Exited with code %d\n", WEXITSTATUS(status));
}

void	single_executor(t_data *data, t_cmd *cmd)
{
	int			old_stdin;
	int			old_stdout;
	builtin_cmd	type;

	old_stdin = dup(0);
	old_stdout = dup(1);
	type = check_builtin(cmd->params);
	handle_redirections(cmd, cmd->params);
	dup2(cmd->input_fd, 0);
	dup2(cmd->output_fd, 1);
	if (type != FAKE)
		execute_builtin(data, cmd, type);
	else
		execute_command(data, cmd, param_lstfind(cmd->params, COMMAND, 0));
	dup2(old_stdin, 0);
	dup2(old_stdout, 1);
	close(old_stdin);
	close(old_stdout);
}

void	multiple_executor(t_data *data, t_cmd *cmd)
{
	builtin_cmd	type;

	while (cmd)
	{
		type = check_builtin(cmd->params);
		if (type >= 0)
			execute_builtin(data, cmd, type);
		else
		{
			
		}
		cmd = cmd->next;
	}
}

void	executor(t_data *data)
{
	if (data->cmd_count == 1)
		single_executor(data, data->cmds);
	else
		multiple_executor(data, data->cmds);
}