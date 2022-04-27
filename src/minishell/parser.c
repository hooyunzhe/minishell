/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:37:34 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/26 14:16:50 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_data *data)
{
	while (data->cmds)
	{
		while (data->cmds->params)
		{
			printf("%s ", data->cmds->params->param_str);
			data->cmds->params = data->cmds->params->next;
		}
		data->cmds = data->cmds->next;
	}
	printf("\n");
}

enclose	is_closed(enclose enclose_type, char current_char)
{
	return ((enclose_type == 1 && current_char == '\'')
		|| (enclose_type == 2 && current_char == '\"')
		|| (enclose_type == 3 && (current_char == ' ')));
		// || current_char == '\'' || current_char == '\"')));
}

int	get_enclose_type(enclose enclose_type, char current_char)
{
	if (enclose_type == CLOSED || enclose_type == NORMAL)
	{
		if (current_char == '\'')
			return (SINGLE);
		else if (current_char == '\"')
			return (DOUBLE);
		else if (current_char && current_char != ' ' && current_char != '|')
			return (NORMAL);
	}
	else if (is_closed(enclose_type, current_char))
		return (CLOSED);
	return (enclose_type);
}

int	is_valid_var(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

char	check_unclosed(char *str)
{
	int	i;
	int	opened;

	i = 0;
	opened = 0;
	while (str[i])
	{
		if (opened == 0)
		{
			if (str[i] == '\'')
				opened = 1;
			else if (str[i] == '\"')
				opened = 2;
		}
		else if (opened == 1 && str[i] == '\'')
			opened = 0;
		else if (opened == 2 && str[i] == '\"')
			opened = 0;
		i++;
	}
	if (opened == 1)
		return ('\'');
	else if (opened == 2)
		return ('\"');
	return (0);
}

char	check_pipe_err(char *str)
{
	int		i;
	int		has_arg;
	enclose	enclose_type;

	i = 0;
	has_arg = 0;
	enclose_type = CLOSED;
	while (str[i])
	{
		enclose_type = get_enclose_type(enclose_type, str[i]);
		if (enclose_type == NORMAL || enclose_type == CLOSED)
		{
			if (str[i] == '|' || !str[i + 1])
			{
				if (!has_arg)
					break;
				else if (str[i] == '|')
					has_arg = 0;
			}
			if (str[i] != '|' && str[i] != ' ' && str[i] != '<' && str[i] != '>')
				has_arg = 1;
		}
		i++;
	}
	if (!has_arg)
		return ('|');
	return (0);
}

char	check_redirection_err(char *str)
{
	int		i;
	int		has_arrow;
	enclose	enclose_type;

	i = 0;
	has_arrow = 0;
	enclose_type = CLOSED;
	while (str[i])
	{
		enclose_type = get_enclose_type(enclose_type, str[i]);
		if (enclose_type == NORMAL || enclose_type == CLOSED)
		{
			if (str[i] == '<')
				has_arrow = 1;
			else if (str[i] == '>')
				has_arrow = 2;
			else if (str[i] != ' ')
				has_arrow = 0;
		}
		i++;
	}
	if (has_arrow == 1)
		return ('<');
	if (has_arrow == 2)
		return ('>');
	return (0);	
}

char	check_input(char *str)
{
	char	error;

	error = 0;
	error = check_unclosed(str);
	if (!error && ft_strchr(str, '|'))
		error = check_pipe_err(str);
	if (!error)
		error = check_redirection_err(str);
	return (error);
}

// int	get_envlen(t_data *data, char *line, int index)
// {
// 	int		i;
// 	int 	len;
// 	char	*temp;

// 	//(*index)++;
// 	i = index + 1;
// 	while (line[i] && is_valid_var(line[i]))
// 		i++;
// 	temp = ft_substr(line, index + 1, i - index - 1);
// 	printf("temp = %s\n", temp);
// 	len = ft_strlen(mini_getenv(data, temp));
// 	//(*index) = i - 1;
// 	free(temp);
// 	return (len);
// }

char	*get_envvar(char *line, int index)
{
	int		i;

	// printf("line: %s, index: %d\n", line, index);
	i = index + 1;
	while (line[i] && is_valid_var(line[i]))
		i++;
	// printf("after valid skip %s\n", line);
	// printf("index = %d, i = %d\n", index, i);
	// printf("temp = [%s]\n", ft_substr(line, index + 1, i - index - 1));
	return (ft_substr(line, index + 1, i - index - 1));
}

int	get_expanded_len(t_data *data, char *line)
{
	int		i;
	int		len;
	int		enclose_type;
	char	*temp;

	i = 0;
	len = 0;
	enclose_type = CLOSED;
	while (line[i])
	{
		enclose_type = get_enclose_type(enclose_type, line[i]);
		if (line[i] == '$' && line[i + 1] != ' ' && enclose_type != SINGLE)
		{
			temp = get_envvar(line, i);
			len += ft_strlen(mini_getenv(data, temp)) + 2;
			i += ft_strlen(temp);
			free(temp);
		}
		else
			len++;
		if (line[i] == '~')
			len += ft_strlen(mini_getenv(data, "HOME"));
		i++;
	}
	return (len + 1);
}

char	*get_expanded_param(t_data *data, char *line)
{
	int		i;
	int		j;
	char	*expanded_line;
	char	*env_var;
	char	*temp;
	enclose	enclose_type;

	expanded_line = malloc(get_expanded_len(data, line) * sizeof(char));
	i = 0;
	j = 0;
	enclose_type = CLOSED;
	while (line[i])
	{
		enclose_type = get_enclose_type(enclose_type, line[i]);
		if (line[i] == '$' && line[i + 1] != ' ' && enclose_type != SINGLE)
		{
			// printf("type: %d\n", enclose_type);
			env_var = get_envvar(line, i);
			// printf("env_var = [%s]\n", env_var);
			if (line[i + 1] && ft_isdigit(line[i + 1]))
				i++;
			else if (!ft_strncmp(env_var, "?", 1))
			{
				temp = ft_itoa(data->exit_status);
				ft_memmove(&(expanded_line[j]), temp, ft_strlen(temp));
				j += ft_strlen(temp);
				free(temp);
				i += ft_strlen(env_var);
			}
			else
			{	
				if (ft_strchr(mini_getenv(data, env_var), '\"') == NULL)
					expanded_line[j++] = '\"';
				else if (ft_strchr(mini_getenv(data, env_var), '\'') == NULL)
					expanded_line[j++] = '\'';
				ft_memmove(&(expanded_line[j]), mini_getenv(data, env_var), ft_strlen(mini_getenv(data, env_var)));
				j += ft_strlen(mini_getenv(data, env_var));
				if (ft_strchr(mini_getenv(data, env_var), '\"') == NULL)
					expanded_line[j++] = '\"';
				else if (ft_strchr(mini_getenv(data, env_var), '\'') == NULL)
					expanded_line[j++] = '\'';
				i += ft_strlen(env_var);
			}
			free(env_var);
		}
		else if (line[i] == '~' && (ft_strlen(line) == 1 || line[i + 1] == '/'))
		{
			ft_memmove(&(expanded_line[j]), mini_getenv(data, "HOME"), ft_strlen(mini_getenv(data, "HOME")));
			j += ft_strlen(mini_getenv(data, "HOME"));
		}
		else
			expanded_line[j++] = line[i];
		i++;
	}
	expanded_line[j] = '\0';
	free(line);
	if (ft_strlen(expanded_line) != 2)
		return (expanded_line);
	else
	{
		free(expanded_line);
		return (NULL);
	}
}

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

param	get_param_type(char *param_str)
{
	int	i;

	i = 0;
	if ((param_str[i] == '\'' || param_str[i] == '\"')
		&& param_str[i + 1] == '-')
		i++;
	if (param_str[i] == '-' && param_str[i + 1] && param_str[i + 1] != '-')
		return (OPTION);
	else if (!ft_strncmp(param_str, "<", ft_strlen(param_str))
		|| !ft_strncmp(param_str, ">", ft_strlen(param_str))
		|| !ft_strncmp(param_str, "<<", ft_strlen(param_str))
		|| !ft_strncmp(param_str, ">>", ft_strlen(param_str)))
		return (REDIRECTION);
	return (ARGUMENT);
}

void	update_param_type(t_param *params)
{
	int	has_command;

	has_command = 0;
	if (params->param_type == ARGUMENT || params->param_type == OPTION)
	{
		params->param_type = COMMAND;
		has_command = 1;
	}
	while (params->next != NULL)
	{
		if (params->param_type == COMMAND)
			has_command = 1;
		else if (params->param_type == REDIRECTION)
			params->next->param_type = IO_FILE;
		else if (params->param_type == ARGUMENT)
		{
			if (params->next->param_type == OPTION)
				params->next->param_type = ARGUMENT;
		}
		if (!has_command && params->next->param_type == ARGUMENT)
		{
			params->next->param_type = COMMAND;
			has_command = 1;
		}
		params = params->next;
	}
}

redirection	get_redirection_type(char *param_str, param param_type)
{
	if (param_type == REDIRECTION)
	{
		if (!ft_strncmp(param_str, "<", ft_strlen(param_str)))
			return (S_IN);
		else if (!ft_strncmp(param_str, ">", ft_strlen(param_str)))
			return (S_OUT);
		else if (!ft_strncmp(param_str, "<<", ft_strlen(param_str)))
			return (D_IN);
		else if (!ft_strncmp(param_str, ">>", ft_strlen(param_str)))
			return (D_OUT);
	}
	return (-1);
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
	param_type = get_param_type(modified_param);
	redirection_type = get_redirection_type(modified_param, param_type);
	// printf("line = %s\n", modified_param);
	if ((!cmd->params || (param_lstlast(cmd->params))->redirection_type != D_IN)
		&& has_expand(modified_param))
	{
		modified_param = get_expanded_param(data, modified_param);
		//printf("expanded param: %s\n", modified_param);
	}
	if (modified_param)
	{
		//printf("END\n");
		modified_param = get_unquoted_param(modified_param);
		// printf("unquoted param: [%d]\n", modified_param[0]);
		// printf("param: [%s]\n", modified_param);
		current_param = new_param(modified_param, param_type, redirection_type);
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
	cmd = new_cmd();
	while (line[i])
	{
		// printf("i: %d, len: %d, line[i]: %c, enclose_type: %d\n", i, len, line[i], enclose_type);
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
		param_lstadd_back(&cmd->params, new_param(NULL, COMMAND, -1));
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
		// printf("cmd_str: %s\n", cmd_strs[i]);
		cmd_lstadd_back(&data->cmds, get_cmd(data, cmd_strs[i]));
		i++;
	}
	i = 0;
	while (cmd_strs[i])
		free(cmd_strs[i++]);
	free(cmd_strs);
}
