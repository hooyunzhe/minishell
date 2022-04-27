/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:34:21 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 16:33:16 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_unclosed_err(char *str)
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

static char	check_pipe_err(char *str)
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
			if ((str[i] == '|' || !str[i + 1]) && !has_arg)
				break ;
			if (str[i] == '|')
				has_arg = 0;
			else if (str[i] != ' ' && str[i] != '<' && str[i] != '>')
				has_arg = 1;
		}
		i++;
	}
	if (!has_arg)
		return ('|');
	return (0);
}

static char	check_redirection_err(char *str)
{
	int		i;
	int		has_arrow;
	enclose	enclose_type;

	i = -1;
	has_arrow = 0;
	enclose_type = CLOSED;
	while (str[++i])
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

	error = check_unclosed_err(str);
	if (!error && ft_strchr(str, '|'))
		error = check_pipe_err(str);
	if (!error)
		error = check_redirection_err(str);
	return (error);
}
