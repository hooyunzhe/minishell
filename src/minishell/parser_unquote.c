/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_unquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:45:04 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/29 15:45:11 by hyun-zhe         ###   ########.fr       */
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
