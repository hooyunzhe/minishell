/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:22:14 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/27 10:28:19 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cd_error(t_data *data, char *path)
{
	if (errno == ENOTDIR)
		handle_error(data, CD_NOTADIR, path);
	else if (errno == EACCES)
		handle_error(data, CD_NOACCESS, path);
	else
		handle_error(data, CD_NODIR, path);
}

void	mini_cd(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	*param_path;

	if ((cmd->option_count + cmd->arg_count) > 2)
		return (handle_error(data, CD_TOOMANY, NULL));
	else if ((cmd->option_count + cmd->arg_count) == 2)
	{
		if (handle_replaced_path(data, cmd, &path) == 1)
			return ;
	}
	else if ((cmd->option_count + cmd->arg_count) == 1)
	{
		param_path = find_string(cmd->params, 0);
		if (!ft_strncmp(param_path, "-", 2))
			path = mini_getenv(data, "OLDPWD");
		else
			path = param_path;
	}
	else
		path = mini_getenv(data, "HOME");
	if (chdir(path) == -1)
		handle_cd_error(data, path);
	else
		update_env_pwd(data);
}
