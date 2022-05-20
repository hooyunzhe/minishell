/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:17:35 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/19 16:58:14 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		dup2(cmd->input_fd, 0);
		close(cmd->input_fd);
	}
	if (cmd->output_fd != 1)
	{
		dup2(cmd->output_fd, 1);
		close(cmd->output_fd);
	}
}

void	close_fds(t_cmd *cmd, int pipes[2])
{
	if (cmd->input_fd != pipes[0] && cmd->input_fd != 0)
		close(cmd->input_fd);
	if (cmd->output_fd != pipes[1] && cmd->output_fd != 1)
		close(cmd->output_fd);
	if (cmd->next == NULL)
		close(pipes[0]);
	close(pipes[1]);
}
