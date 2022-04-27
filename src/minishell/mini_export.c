/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:58:58 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 10:30:12 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
		i++;
	}
	return (ft_strdup(str));
}

static void	handle_noargs(t_envp *head)
{
	while (head)
	{
		if (ft_strncmp(head->key, "_", 1))
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		head = head->next;
	}
}

static void	handle_args(t_data *data, t_envp *head, t_param *node)
{
	char	*key;
	char	*value;

	while (node)
	{
		if (node->param_type == ARGUMENT)
		{
			if (!check_valid_key(node->param_str))
				return (handle_error(data, EXP_NOTVALID, node->param_str));
			key = get_key(node->param_str);
			if (ft_strlen(key) == ft_strlen(node->param_str)
				|| ft_strlen(key) == ft_strlen(node->param_str) - 1)
				value = ft_strdup("");
			else
			{
				value = ft_substr(node->param_str, ft_strlen(key) + 1,
						ft_strlen(node->param_str) - ft_strlen(key));
			}
			if (!env_lstupdate(head, key, value))
				env_lstadd_back(&head, env_lstnew(key, value));
		}
		node = node->next;
	}
}

void	mini_export(t_data *data, t_cmd *cmd)
{
	if (cmd->arg_count == 0)
		handle_noargs(data->mini_envp);
	else
		handle_args(data, data->mini_envp, cmd->params);
}
