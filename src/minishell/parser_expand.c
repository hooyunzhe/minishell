/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:03:14 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 16:54:08 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_param(t_data *data, char *str, char *env_var, int *index)
{
	char	*temp;

	if (!ft_strncmp(env_var, "?", 1))
	{
		temp = ft_itoa(data->exit_status);
		ft_memmove(&(str[*index]), temp, ft_strlen(temp));
		*index += ft_strlen(temp);
		free(temp);
	}
	else
	{	
		if (ft_strchr(mini_getenv(data, env_var), '\"') == NULL)
			str[(*index)++] = '\"';
		else if (ft_strchr(mini_getenv(data, env_var), '\'') == NULL)
			str[(*index)++] = '\'';
		ft_memmove(&(str[*index]), mini_getenv(data, env_var),
			ft_strlen(mini_getenv(data, env_var)));
		*index += ft_strlen(mini_getenv(data, env_var));
		if (ft_strchr(mini_getenv(data, env_var), '\"') == NULL)
			str[(*index)++] = '\"';
		else if (ft_strchr(mini_getenv(data, env_var), '\'') == NULL)
			str[(*index)++] = '\'';
	}
}

static void	handle_expansion(t_data *data, char **line, char *str, int *index)
{
	char	*env_var;

	env_var = get_envvar(*line, 0);
	if (*((*line) + 1) && ft_isdigit(*((*line) + 1)))
		(*line)++;
	else
	{
		expand_param(data, str, env_var, index);
		(*line) += ft_strlen(env_var);
	}
	free(env_var);
}

static char	*get_return_value(char *expanded_line)
{
	if (ft_strlen(expanded_line) != 2)
		return (expanded_line);
	else
	{
		free(expanded_line);
		return (NULL);
	}
}

char	*get_expanded_param(t_data *data, char *line, int len)
{
	int		index;
	char	*expanded_line;
	enclose	enclose_type;

	expanded_line = malloc(get_expanded_len(data, line) * sizeof(char));
	index = 0;
	enclose_type = CLOSED;
	while (*line)
	{
		enclose_type = get_enclose_type(enclose_type, *line);
		if (*line == '$' && *(line + 1) != ' ' && enclose_type != SINGLE)
			handle_expansion(data, &line, expanded_line, &index);
		else if (*line == '~' && (len == 1 || *(line + 1) == '/'))
		{
			ft_memmove(&(expanded_line[index]), mini_getenv(data, "HOME"),
				ft_strlen(mini_getenv(data, "HOME")));
			index += ft_strlen(mini_getenv(data, "HOME"));
		}
		else
			expanded_line[index++] = *line;
		line++;
	}
	expanded_line[index] = '\0';
	return (get_return_value(expanded_line));
}
