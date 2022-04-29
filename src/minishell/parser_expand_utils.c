/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:20:08 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/29 15:36:06 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_expand(char *line)
{
	if (ft_strchr(line, '?') || ft_strchr(line, '~') || (ft_strchr(line, '$') && ft_strlen(line) > 1))
		return (1);
	return (0);
}

static int	is_valid_var(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

char	*get_envvar(char *line, int index)
{
	int		i;

	i = index + 1;
	while (line[i] && is_valid_var(line[i]))
		i++;
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
