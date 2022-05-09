/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:06:59 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/09 10:50:43 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc(t_data *data, char *delim)
{
	int		pipes[2];
	char	*line;

	pipe(pipes);
	line = readline("heredoc > ");
	while (line && ft_strncmp(line, delim, ft_strlen(delim) + 1))
	{
		line = get_expanded_param(data, line, ft_strlen(line));
		write(pipes[1], line, ft_strlen(line));
		write(pipes[1], "\n", 1);
		free(line);
		line = readline("heredoc > ");
	}
	free(line);
	close(pipes[1]);
	return (pipes[0]);
}

static int	handle_redirection_error(t_data *data, t_param *params)
{
	if (errno == ENOENT)
		handle_error(data, EXE_NOFILE, params->next->param_str);
	if (errno == EACCES)
		handle_error(data, EXE_NOPERM, params->next->param_str);
	return (1);
}

static void	handle_io(t_data *data, t_cmd *cmd, t_param *params)
{
	if (params->redirection_type == S_IN)
		cmd->input_fd = open(params->next->param_str, O_RDONLY);
	else if (params->redirection_type == D_IN)
		cmd->input_fd = handle_heredoc(data, params->next->param_str);
	else if (params->redirection_type == S_OUT)
		cmd->output_fd = open(params->next->param_str,
				O_WRONLY | O_CREAT, 0644);
	else if (params->redirection_type == D_OUT)
		cmd->output_fd = open(params->next->param_str,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
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
				handle_io(data, cmd, params);
				if (cmd->input_fd == -1 || cmd->output_fd == -1)
					return (handle_redirection_error(data, params));
			}
		}
		params = params->next;
	}
	return (0);
}
