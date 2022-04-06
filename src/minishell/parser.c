/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:37:34 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/06 10:37:51 by nfernand         ###   ########.fr       */
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

int	is_closed(int enclose_type, char current_char)
{
	return ((enclose_type == 1 && current_char == '\'')
		|| (enclose_type == 2 && current_char == '\"')
		|| (enclose_type == 3 && (current_char == ' ')));
		// || current_char == '\'' || current_char == '\"')));
}

int	get_enclose_type(int enclose_type, char current_char)
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
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	check_input(char *str)
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
	return (opened == 1 || opened == 2);
}

int	get_envlen(char *line, int *index)
{
	int	i;
	int len;
	char	*temp;

	(*index)++;
	i = *index;
	while (line[i] && is_valid_var(line[i]))
		i++;
	temp = ft_substr(line, *index, i - *index);
	len = ft_strlen(getenv(temp));
	(*index) = i - 1;
	free(temp);
	return (len);
}

char	*get_envvar(char *line, int index)
{
	int		i;

	i = index;
	while (line[i] && is_valid_var(line[i]))
		i++;
	return (ft_substr(line, index, i - index));
}

int	get_expanded_len(char *line)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
			len += get_envlen(line, &i) + 2;
		else
			len++;
		i++;
	}
	return (len + 1);
}

char	*get_expanded_param(char *line)
{
	int		i;
	int		j;
	char	*expanded_line;
	char	*env_var;
	int		enclose_type;

	expanded_line = malloc(get_expanded_len(line) * sizeof(char));
	i = 0;
	j = 0;
	enclose_type = CLOSED;
	while (line[i])
	{
		enclose_type = get_enclose_type(enclose_type, line[i]);
		if (line[i] == '$' && enclose_type != SINGLE)
		{
			if (line[i + 1] && ft_isdigit(line[i + 1]))
			{
				while(line[i + 1] && ft_isdigit(line[i + 1]))
					i++;
			}
			else
			{	
				env_var = get_envvar(line, i + 1);
				if (ft_strchr(getenv(env_var), '\"') == NULL)
					expanded_line[j++] = '\"';
				else if (ft_strchr(getenv(env_var), '\'') == NULL)
					expanded_line[j++] = '\'';
				ft_memmove(&(expanded_line[j]), getenv(env_var), get_envlen(line, &i));
				j += ft_strlen(getenv(env_var));
				if (ft_strchr(getenv(env_var), '\"') == NULL)
					expanded_line[j++] = '\"';
				else if (ft_strchr(getenv(env_var), '\'') == NULL)
					expanded_line[j++] = '\'';
				free(env_var);
			}
		}
		else
			expanded_line[j++] = line[i];
		i++;
	}
	expanded_line[j] = '\0';
	free(line);
	return (expanded_line);
}

int	get_unquoted_len(char *line)
{
	int		i;
	int		count;
	int		enclose_type;

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
	return (count);
}

char	*get_unquoted_param(char *line)
{
	int		i;
	int		j;
	int		enclose_type;
	char	*unquoted_line;

	i = 0;
	j = 0;
	enclose_type = CLOSED;
	unquoted_line = malloc(sizeof(char) * (get_unquoted_len(line) + 1));
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
	if (param_str[0] == '-')
		return (OPTION);
	else if (!ft_strncmp(param_str, "<", ft_strlen(param_str))
		|| !ft_strncmp(param_str, ">", ft_strlen(param_str))
		|| !ft_strncmp(param_str, "<<", ft_strlen(param_str))
		|| !ft_strncmp(param_str, ">>", ft_strlen(param_str)))
		return (REDIRECTION);
	return (ARGUMENT);
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

void	get_param(t_cmd *cmd, char *param_str)
{
	param		param_type;
	redirection	redirection_type;
	char		*modified_param;
	t_param		*current_param;
	
	
	param_type = get_param_type(param_str);
	redirection_type = get_redirection_type(param_str, param_type);
	modified_param = ft_strdup(param_str);
	if (!cmd->params || (param_lstlast(cmd->params))->redirection_type != D_IN)
	{
		modified_param = get_expanded_param(modified_param);
		printf("expanded param: %s\n", modified_param);
	}
	printf("END\n");
	modified_param = get_unquoted_param(modified_param);
	printf("unquoted param: %s\n", modified_param);
	current_param = new_param(modified_param, param_type, redirection_type);
	param_lstadd_back(&cmd->params, current_param); 
	cmd->param_count++;
}

t_cmd	*get_cmd(t_data *data, char *line)
{
	int		i;
	int		len;
	int		enclose_type;
	t_cmd	*cmd;

	i = 0;
	len = 0;
	enclose_type = CLOSED;
	cmd = new_cmd();
	(void)data;
	while (line[i])
	{
		// printf("i: %d, len: %d, line[i]: %c, enclose_type: %d\n", i, len, line[i], enclose_type);
		len += (line[i] != ' ' || (enclose_type && enclose_type != NORMAL));
		if ((is_closed(enclose_type, line[i]) || enclose_type == NORMAL)
			&& (line[i + 1] == ' ' || !line[i + 1]))
		{
			get_param(cmd, ft_substr(line, i - len + 1, len));
			len = 0;
		}
		enclose_type = get_enclose_type(enclose_type, line[i]);
		i++;
	}
	return (cmd);
}

int		get_cmd_count(char *line)
{
	int	i;
	int	len;
	int	enclose_type;

	i = 0;
	len = 0;
	enclose_type = CLOSED;
	while (line[i])
	{
		enclose_type = get_enclose_type(enclose_type, line[0]);
		if (((enclose_type == CLOSED || enclose_type == NORMAL)
			&& line[i] == '|') || !line[i + 1])
			len++;
		i++;
	}
	return (len + (line[i - 1] != '|'));
}

char	**get_cmd_strs(char *line)
{
	int		i;
	int		j;
	int		len;
	int		enclose_type;
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
	int		i;
	char	**cmd_strs;

	(void)data;
	i = 0;
	cmd_strs = get_cmd_strs(line);
	while (cmd_strs[i])
	{
		printf("cmd_str: %s\n", cmd_strs[i]);
		if (check_input(line))
			break ;
		cmd_lstadd_back(&data->cmds, get_cmd(data, cmd_strs[i]));
		i++;
	}
	i = 0;
	while (cmd_strs[i])
		free(cmd_strs[i++]);
	free(cmd_strs);
}
