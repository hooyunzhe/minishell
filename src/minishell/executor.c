/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:57:34 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/18 17:40:10 by nazrinsha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, t_cmd *cmd, t_param *command_str)
{
	char	**params;
	char	**paths;
	char	**envp;
	char	*fullpath;
	char	*temp;

	signal(SIGINT, SIG_DFL);
	params = get_param_array(cmd);
	if (mini_getenv(data, "PATH"))
		paths = ft_split(mini_getenv(data, "PATH"), ':');
	else
		paths = NULL;
	envp = env_lst_to_arr(data->mini_envp);
	execve(params[0], params, envp);
	while (paths && *paths)
	{
		temp = ft_strjoin(*paths, "/");
		fullpath = ft_strjoin(temp, command_str->param_str);
		free(temp);
		execve(fullpath, params, envp);
		paths++;
	}
	handle_error(data, EXE_NOCMD, command_str->param_str);
	ft_exit(data, 127);
}

void	single_executor(t_data *data, t_cmd *cmd)
{
	int			old_stdin;
	int			old_stdout;
	int			status;
	t_cmdtype	type;
	pid_t		pid;

	swap_old_fd(&old_stdin, &old_stdout, 0);
	swap_new_fd(cmd);
	type = check_builtin(cmd->params);
	tcsetattr(0, 0, &data->original_term);
	if (type != NON_BUILTIN)
		execute_builtin(data, cmd, type);
	else if (type != NO_CMD)
	{
		pid = fork();
		if (pid == 0)
			execute_command(data, cmd, param_lstfind(cmd->params, COMMAND, 0));
		waitpid(pid, &status, 0);
		data->exit_status = WEXITSTATUS(status);
	}
	swap_old_fd(&old_stdin, &old_stdout, 1);
	if (mini_getenv(data, "_"))
		env_lstupdate(data->mini_envp, "_",
			ft_strdup(param_lstlast(cmd->params)->param_str));
}

void	multiple_executor_child(t_data *data, t_cmd *cmd)
{
	t_cmdtype	type;

	type = check_builtin(cmd->params);
	if (handle_redirections(data, cmd, cmd->params))
		ft_exit(data, data->exit_status);
	swap_new_fd(cmd);
	if (type != NON_BUILTIN)
	{
		execute_builtin(data, cmd, type);
		ft_exit(data, data->exit_status);
	}
	else if (type != NO_CMD)
		execute_command(data, cmd, param_lstfind(cmd->params, COMMAND, 0));
}

void	multiple_executor(t_data *data, t_cmd *cmd)
{
	int			status;
	pid_t		pid;
	int			pipes[2];

	while (cmd)
	{
		if (mini_getenv(data, "_"))
			env_lstupdate(data->mini_envp, "_",
				ft_strdup(param_lstlast(cmd->params)->param_str));
		if (cmd != data->cmds)
			cmd->input_fd = pipes[0];
		pipe(pipes);
		pid = fork();
		if ((pid == 0 && cmd->next != NULL))
			cmd->output_fd = pipes[1];
		if (pid == 0)
			multiple_executor_child(data, cmd);
		close(pipes[1]);
		if (param_lstfind(cmd->params, REDIRECTION, 0) != NULL)
			waitpid(-1, &status, 0);
		cmd = cmd->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	data->exit_status = WEXITSTATUS(status);
}

void	executor(t_data *data)
{
	if (data->cmds && data->cmds->params->param_str)
	{
		if (data->cmd_count == 1)
		{
			if (handle_redirections(data, data->cmds, data->cmds->params) != 1)
				single_executor(data, data->cmds);
		}
		else
			multiple_executor(data, data->cmds);
	}
}
