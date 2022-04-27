/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:48:25 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 16:33:53 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enclose	is_closed(enclose enclose_type, char current_char)
{
	return ((enclose_type == 1 && current_char == '\'')
		|| (enclose_type == 2 && current_char == '\"')
		|| (enclose_type == 3 && (current_char == ' ')));
}

enclose	get_enclose_type(enclose enclose_type, char current_char)
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
			if (params->next->param_type == OPTION)
				params->next->param_type = ARGUMENT;
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
