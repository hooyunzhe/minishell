/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:56:13 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/26 11:26:27 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// change dprintf to std_err

void	handle_exe_error(t_data *data, error_id id, char *param)
{
	if (id == EXE_NOCMD)
	{
		dprintf(2, "minishell: command not found: %s\n", param);
		data->exit_status = 127;
	}
	else if (id == EXE_NOFILE)
		dprintf(2, "minishell: no such file or directory: %s\n", param);
	else if (id == EXE_NOPERM)
		dprintf(2, "minishell: permission denied: %s\n", param);
}

void	handle_cd_error(error_id id, char *param)
{
	if (id == CD_NODIR)
		dprintf(2, "cd: no such file or directory: %s\n", param);
	else if (id == CD_TOOMANY)
		dprintf(2, "cd: too many arguments\n");
	else if (id == CD_STRNOTIN)
		dprintf(2, "cd: string not in pwd: %s\n", param);
	else if (id == CD_NOTADIR)
		dprintf(2, "cd: not a directory: %s\n", param);
	else if (id == CD_NOACCESS)
		dprintf(2, "cd: permission denied: %s\n", param);
}

void	handle_exit_error(error_id id, char *param)
{
	if (id == EXIT_NONUM)
		dprintf(2, "exit: numeric argument required: %s\n", param);
	else if (id == EXIT_TOOMANY)
		dprintf(2, "exit: too many arguments\n");
}

void	handle_error(t_data *data, error_id id, char *param)
{
	data->exit_status = 1;
	if (id <= PARSE_ERR)
	{
		data->exit_status = 2;
		dprintf(2, "minishell: parse error near [%s]\n", param);
	}
	else if (id <= EXE_NOPERM)
		handle_exe_error(data, id, param);
	else if (id <= CD_NOACCESS)
		handle_cd_error(id, param);
	else if (id == EXP_NOTVALID)
		dprintf(2, "export: not a valid identifier: %s\n", param);
	else if (id == UNS_NOTVALID)
		dprintf(2, "unset: not a valid identifier: %s\n", param);
	else if (id <= EXIT_TOOMANY)
		handle_exit_error(id, param);
}