/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:37:34 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/29 16:05:27 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_param(t_data *data, t_cmd *cmd, char *param_str);

char	*get_modified_param(t_data *data, t_cmd *cmd, char *param_str)
{
	int		start_index;
	char	*modified_param;

	start_index = check_redirection_start(param_str);
	if (start_index > 0)
		get_param(data, cmd, ft_substr(param_str, 0, start_index));
	modified_param = ft_substr(param_str, start_index,
			ft_strlen(param_str) - start_index);
	free(param_str);
	return (modified_param);
}

void	get_param(t_data *data, t_cmd *cmd, char *param_str)
{
	param		param_type;
	redirection	redirection_type;
	char		*modified_param;
	t_param		*current_param;

	modified_param = get_modified_param(data, cmd, param_str);
	param_type = get_param_type(modified_param);
	redirection_type = get_redirection_type(modified_param, param_type);
	if ((!cmd->params || (param_lstlast(cmd->params))->redirection_type != D_IN)
		&& has_expand(modified_param))
	{
		param_str = get_expanded_param(data, modified_param,
				ft_strlen(modified_param));
		free(modified_param);
		modified_param = param_str;
	}
	if (modified_param)
	{
		modified_param = get_unquoted_param(modified_param);
		current_param = param_lstnew(modified_param, param_type,
				redirection_type);
		param_lstadd_back(&cmd->params, current_param);
	}
}

t_cmd	*get_cmd(t_data *data, char *line)
{
	int		i;
	int		len;
	enclose	et;
	t_cmd	*cmd;

	i = -1;
	len = 0;
	et = CLOSED;
	cmd = cmd_lstnew();
	while (line[++i])
	{
		len += (line[i] != ' ' || (et && et != NORMAL));
		if ((is_closed(et, line[i]) || get_enclose_type(et, line[i]) == NORMAL)
			&& (line[i + 1] == ' ' || !line[i + 1]) && len > 0)
		{
			get_param(data, cmd, ft_substr(line, i - len + 1, len));
			len = 0;
		}
		et = get_enclose_type(et, line[i]);
	}
	if (cmd->params)
		update_param_type(cmd->params);
	else
		param_lstadd_back(&cmd->params, param_lstnew(NULL, COMMAND, -1));
	return (cmd);
}

void	parser(t_data *data, char *line)
{
	char	**cmd_strs;
	int		i;
	char	err[2];

	err[0] = check_input(line);
	err[1] = '\0';
	if (err[0])
		return ((void)handle_error(data, PARSE_ERR, err));
	i = 0;
	data->cmd_count = get_cmd_count(line);
	cmd_strs = get_cmd_strs(line);
	while (cmd_strs[i])
	{
		cmd_lstadd_back(&data->cmds, get_cmd(data, cmd_strs[i]));
		i++;
	}
	ft_freestrs(cmd_strs);
}
