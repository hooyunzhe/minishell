/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:37:34 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 16:49:06 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_unquoted_len(char *line)
{
	int		i;
	int		count;
	enclose	enclose_type;

	i = 0;
	count = 0;
	enclose_type = CLOSED;
	while (line[i])
	{
		if (is_closed(enclose_type, line[i]) || !line[i + 1])
		{
			if (line[i + 1] != ' ')
				count -= 2 * (enclose_type == SINGLE || enclose_type == DOUBLE);
		}
		count++;
		enclose_type = get_enclose_type(enclose_type, line[i]);
		i++;
	}
	return (count + 1);
}

char	*get_unquoted_param(char *line)
{
	int		i;
	int		j;
	enclose	enclose_type;
	char	*unquoted_line;

	i = 0;
	j = 0;
	enclose_type = CLOSED;
	unquoted_line = malloc(sizeof(char) * get_unquoted_len(line));
	while (line[i])
	{
		if ((line[i] != '\'' && line[i] != '\"')
			|| (enclose_type == SINGLE && line[i] == '\"')
			|| (enclose_type == DOUBLE && line[i] == '\''))
			unquoted_line[j++] = line[i];
		enclose_type = get_enclose_type(enclose_type, line[i]);
		i++;
	}
	unquoted_line[j] = '\0';
	free(line);
	return (unquoted_line);
}

int	check_redirection_start(char *str)
{
	if (str[0] && str[1] && (str[0] == '>' || str[0] == '<'))
	{
		if (str[1] != '>' && str[1] != '<')
			return (1);
		else if (str[2])
			return (2);
	}
	return (0);
}

int		has_expand(char *line)
{
	if (ft_strchr(line, '?') || ft_strchr(line, '~') || (ft_strchr(line, '$') && ft_strlen(line) > 1))
		return (1);
	return (0);
}

void	get_param(t_data *data, t_cmd *cmd, char *param_str)
{
	param		param_type;
	redirection	redirection_type;
	char		*modified_param;
	t_param		*current_param;
	int			start_index;
	
	start_index = check_redirection_start(param_str);
	if (start_index > 0)
		get_param(data, cmd, ft_substr(param_str, 0, start_index));
	modified_param = ft_substr(param_str, start_index, ft_strlen(param_str) - start_index);
	free(param_str);
	param_type = get_param_type(modified_param);
	redirection_type = get_redirection_type(modified_param, param_type);
	if ((!cmd->params || (param_lstlast(cmd->params))->redirection_type != D_IN)
		&& has_expand(modified_param))
	{
		param_str = get_expanded_param(data, modified_param, ft_strlen(modified_param));
		free(modified_param);
		modified_param = param_str;
	}
	if (modified_param)
	{
		modified_param = get_unquoted_param(modified_param);
		current_param = param_lstnew(modified_param, param_type, redirection_type);
		param_lstadd_back(&cmd->params, current_param);
	}
}

t_cmd	*get_cmd(t_data *data, char *line)
{
	int		i;
	int		len;
	enclose	enclose_type;
	t_cmd	*cmd;

	i = 0;
	len = 0;
	enclose_type = CLOSED;
	cmd = cmd_lstnew();
	while (line[i])
	{
		len += (line[i] != ' ' || (enclose_type && enclose_type != NORMAL));
		if ((is_closed(enclose_type, line[i])
			|| get_enclose_type(enclose_type, line[i]) == NORMAL)
			&& (line[i + 1] == ' ' || !line[i + 1]) && len > 0)
		{
			get_param(data, cmd, ft_substr(line, i - len + 1, len));
			len = 0;
		}
		enclose_type = get_enclose_type(enclose_type, line[i]);
		i++;
	}
	if (cmd->params)
		update_param_type(cmd->params);
	else
		param_lstadd_back(&cmd->params, param_lstnew(NULL, COMMAND, -1));
	return (cmd);
}

int		get_cmd_count(char *line)
{
	int	i;
	int	len;
	enclose	enclose_type;

	i = 0;
	len = 0;
	enclose_type = CLOSED;
	while (line[i])
	{
		enclose_type = get_enclose_type(enclose_type, line[i]);
		if (((enclose_type == CLOSED || enclose_type == NORMAL)
			&& line[i] == '|') || !line[i + 1])
			len++;
		i++;
	}
	return (len);
}

char	**get_cmd_strs(char *line)
{
	int		i;
	int		j;
	int		len;
	enclose	enclose_type;
	char	**cmd_strs;

	i = 0;
	j = 0;
	len = 0;
	enclose_type = CLOSED;
	cmd_strs = malloc((get_cmd_count(line) + 1) * sizeof(char *));
	while (line[i])
	{
		enclose_type = get_enclose_type(enclose_type, line[i]);
		if (((enclose_type == CLOSED || enclose_type == NORMAL)
			&& line[i] == '|') || !line[i + 1])
		{
			cmd_strs[j++] = ft_substr(line, i - len, len + (!line[i + 1]));
			len = 0;
		}
		else
			len++;
		i++;
	}
	cmd_strs[j] = NULL;
	return (cmd_strs);
}

void	parser(t_data *data, char *line)
{
	char	**cmd_strs;
	int		i;
	char	err[2];

	err[1] = '\0';
	err[0] = check_input(line);
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
	i = 0;
	while (cmd_strs[i])
		free(cmd_strs[i++]);
	free(cmd_strs);
}
