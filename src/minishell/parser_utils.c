/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:43:18 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/09 13:42:03 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_cmd_count(char *line)
{
	int				i;
	int				len;
	t_enclosetype	enclose_type;

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
	int				i;
	int				j;
	int				len;
	t_enclosetype	enclose_type;
	char			**cmd_strs;

	i = -1;
	j = 0;
	len = 0;
	enclose_type = CLOSED;
	cmd_strs = malloc((get_cmd_count(line) + 1) * sizeof(char *));
	while (line[++i])
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
	}
	cmd_strs[j] = NULL;
	return (cmd_strs);
}
