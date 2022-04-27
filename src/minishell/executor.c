/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:57:34 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 14:04:08 by hyun-zhe         ###   ########.fr       */
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

int	ft_strncasecmp(char *s1, char *s2, int n)
{
	if (n == 0)
		return (0);
	while (*s1 && ft_tolower(*s1) == ft_tolower(*s2) && --n)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)ft_tolower(*s1) - (unsigned char)ft_tolower(*s2));
}

builtin_cmd		check_builtin(t_param *param)
{
	t_param	*command;

	command = param_lstfind(param, COMMAND, 0);
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
	return (FAKE);
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

int	handle_heredoc(t_data * data, char *delim)
{
	int		pipes[2];
	char	*line;

	pipe(pipes);
	line = readline("heredoc > ");
	while (line && ft_strncmp(line, delim, ft_strlen(delim) + 1))
	{
		line = get_expanded_param(data, line);
		write(pipes[1], line, ft_strlen(line));
		write(pipes[1], "\n", 1);
		free(line);
		line = readline("heredoc > ");
	}
	free(line);
	close(pipes[1]);
	return (pipes[0]);
}

int	handle_redirections(t_data *data, t_cmd *cmd, t_param *params)
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
				else if (params->redirection_type == D_IN)
					cmd->input_fd = handle_heredoc(data, params->next->param_str);
				else if (params->redirection_type == S_OUT)
					cmd->output_fd = open(params->next->param_str, O_WRONLY | O_CREAT, 0644);
				else if (params->redirection_type == D_OUT)
					cmd->output_fd = open(params->next->param_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (cmd->input_fd == -1 || cmd->output_fd == -1)
				{
					if (errno == ENOENT)
						handle_error(data, EXE_NOFILE, params->next->param_str);
					if (errno == EACCES)
						handle_error(data, EXE_NOPERM, params->next->param_str);
					return (1);
				}
			}
		}
		params = params->next;
	}
	return (0);
}

void	handle_pipes(t_data *data, t_cmd *cmd, int *pipes, int index)
{
	// if (index > 0)
	// 	cmd->input_fd = pipes[0];
	if (index < data->cmd_count - 1)
		cmd->output_fd = pipes[1];
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
		res[i++] = ft_strjoin(temp, envp->value);
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

	params = get_param_array(cmd);
	if (mini_getenv(data, "PATH"))
		paths = ft_split(mini_getenv(data, "PATH"), ':');
	else
		paths = NULL;
	envp = env_lst_to_arr(data->mini_envp);
	execve(params[0], params, envp);
	i = 0;
	while (paths && paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		fullpath = ft_strjoin(temp, command_str->param_str);
		execve(fullpath, params, envp);
		i++;
	}
	handle_error(data, EXE_NOCMD, command_str->param_str);
	ft_exit(data, 127);
}

void	swap_old_fd(int *old_stdin, int *old_stdout, int type)
{
	if (type == 0)
	{
		*old_stdin = dup(0);
		*old_stdout = dup(1);
	}
	else if (type == 1)
	{
		dup2(*old_stdin, 0);
		dup2(*old_stdout, 1);
		close(*old_stdin);
		close(*old_stdout);
	}
}

void	swap_new_fd(t_cmd *cmd)
{
	if (cmd->input_fd != 0)
	{
		// dprintf(2, "input_fd: %d\n", cmd->input_fd);
		dup2(cmd->input_fd, 0);
		close(cmd->input_fd);
	}
	if (cmd->output_fd != 1)
	{
		// dprintf(2, "output_fd: %d\n", cmd->output_fd);
		dup2(cmd->output_fd, 1);
		close(cmd->output_fd);
	}
}

void	single_executor(t_data *data, t_cmd *cmd)
{
	int			old_stdin;
	int			old_stdout;
	int			status;
	builtin_cmd	type;
	pid_t		pid;


	if (handle_redirections(data, cmd, cmd->params) == 1)
		return ;
	swap_old_fd(&old_stdin, &old_stdout, 0);
	swap_new_fd(cmd);
	type = check_builtin(cmd->params);
	if (type != FAKE)
		execute_builtin(data, cmd, type);
	else
	{
		pid = fork();
		if (pid == 0)
			execute_command(data, cmd, param_lstfind(cmd->params, COMMAND, 0));
		waitpid(pid, &status, 0);
		// printf("Exited with code %d\n", WEXITSTATUS(status));
		data->exit_status = WEXITSTATUS(status);
	}
	swap_old_fd(&old_stdin, &old_stdout, 1);
}

void	multiple_executor(t_data *data, t_cmd *cmd)
{
	int			i;
	int			status;
	builtin_cmd	type;
	pid_t		pid;
	int			pipes[2];

	i = 0;
	while (cmd)
	{
		if (i > 0)
			cmd->input_fd = pipes[0];
		if (cmd->next)
			pipe(pipes);
		pid = fork();
		if (pid == 0)
		{
			type = check_builtin(cmd->params);
			// dprintf(2, "[in_fd: %d, out_fd: %d]\n", cmd->input_fd, cmd->output_fd);
			handle_pipes(data, cmd, pipes, i);
			// dprintf(2, "[in_fd: %d, out_fd: %d]\n", cmd->input_fd, cmd->output_fd);
			handle_redirections(data, cmd, cmd->params);
			swap_new_fd(cmd);
			if (type != FAKE)
			{
				execute_builtin(data, cmd, type);
				ft_exit(data, data->exit_status);
			}
			else
			{
				// dprintf(2,"[in_fd: %d, out_fd: %d]\n", cmd->input_fd, cmd->output_fd);
				execute_command(data, cmd, param_lstfind(cmd->params, COMMAND, 0));
			}
		}
		waitpid(-1, &status, 0);
		close(pipes[1]);
		data->exit_status = WEXITSTATUS(status);
		// printf("Exited with code %d\n", WEXITSTATUS(status));
		i++;
		cmd = cmd->next;
	}
}

void	executor(t_data *data)
{
	if (data->cmds && data->cmds->params->param_str)
	{
		if (data->cmd_count == 1)
		{
			// printf("type: %d\n", data->cmds->params->param_type);
			single_executor(data, data->cmds);
		}
		else
			multiple_executor(data, data->cmds);
	}
}
