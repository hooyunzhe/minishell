/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:53:32 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/11 16:15:31 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (NULL);
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
		i++;
	}
	return (NULL);
}

void	mini_unset(t_data *data, t_cmd *cmd)
{
	t_envp	*curr;
	t_envp	*prev;
	t_param	*node;

	node = cmd->params;
	while (node)
	{
		curr = data->mini_envp;
		prev = curr;
		while (curr)
		{
			if (curr->next)
				if (!ft_strncmp(node->param_str, curr->key, ft_strlen(node->param_str)))
					env_lstdelnext(prev);
			prev = curr;
			curr = curr->next;
		}
		node = node->next;
	}
}

void	mini_export(t_data *data, t_cmd *cmd)
{
	t_envp	*head;
	t_param	*node;
	char	*key;
	char	*value;

	head = data->mini_envp;
	node = cmd->params;
	if (cmd->arg_count == 0)
	{
		while (head)
		{
			if (ft_strncmp(head->key, "_", 1))
				printf("declare -x %s=\"%s\"\n", head->key, head->value);
			head = head->next;
		}
	}
	else
	{
		while (node)
		{
			if (node->param_type == ARGUMENT)
			{
				key = get_key(node->param_str);
				if (!key)
					return (handle_error(EXP_NOTVALID, node->param_str));
				value = ft_substr(node->param_str, ft_strlen(key),
					ft_strlen(node->param_str) - ft_strlen(key));
				env_lstadd_back(&head, env_lstnew(key, value));
				free(key);
				free(value);
			}
			node = node->next;
		}
	}
}

char	*mini_getenv(t_data *data, char *key)
{
	t_envp	*node;

	node = data->mini_envp;
	while (node)
	{
		if (!ft_strncmp(key, node->key, ft_strlen(key)))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

void	mini_env(t_data *data)
{
	t_envp	*node;

	node = data->mini_envp;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}
