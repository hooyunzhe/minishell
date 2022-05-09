/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:56:13 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/09 14:39:42 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_err(char *err_msg, char *param, int type)
{
	ft_putstr_fd(err_msg, 2);
	if (type == 1)
		ft_putchar_fd('[', 2);
	if (param)
		ft_putstr_fd(param, 2);
	if (type == 1)
		ft_putchar_fd(']', 2);
	ft_putstr_fd("\n", 2);
}

void	handle_exe_error(t_data *data, t_error_id id, char *param)
{
	if (id == EXE_NOCMD)
	{
		ft_write_err("minishell: command not found: ", param, 0);
		data->exit_status = 127;
	}
	else if (id == EXE_NOFILE)
		ft_write_err("minishell: no such file or directory: ", param, 0);
	else if (id == EXE_NOPERM)
		ft_write_err("minishell: permission denied: ", param, 0);
}

void	handle_cd_error(t_error_id id, char *param)
{
	if (id == CD_NODIR)
		ft_write_err("cd: no such file or directory: ", param, 0);
	else if (id == CD_TOOMANY)
		ft_write_err("cd: too many arguments", NULL, 0);
	else if (id == CD_STRNOTIN)
		ft_write_err("cd: string not in pwd: ", param, 0);
	else if (id == CD_NOTADIR)
		ft_write_err("cd: not a directory: ", param, 0);
	else if (id == CD_NOACCESS)
		ft_write_err("cd: permission denied: ", param, 0);
}

void	handle_exit_error(t_error_id id, char *param)
{
	if (id == EXIT_NONUM)
		ft_write_err("exit: numeric argument required: ", param, 0);
	else if (id == EXIT_TOOMANY)
		ft_write_err("exit: too many arguments", NULL, 0);
}

void	handle_error(t_data *data, t_error_id id, char *param)
{
	data->exit_status = 1;
	if (id <= PARSE_ERR)
	{
		data->exit_status = 2;
		ft_write_err("minishell: parse error near ", param, 1);
	}
	else if (id <= EXE_NOPERM)
		handle_exe_error(data, id, param);
	else if (id <= CD_NOACCESS)
		handle_cd_error(id, param);
	else if (id == EXP_NOTVALID)
		ft_write_err("export: not a valid identifier: ", param, 0);
	else if (id == UNS_NOTVALID)
		ft_write_err("unset: not a valid identifier: ", param, 0);
	else if (id <= EXIT_TOOMANY)
		handle_exit_error(id, param);
}
