/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:53:32 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/26 10:33:29 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!key || ft_isdigit(key[i]) || key[i] == '=')
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_key(char *str)
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

void	mini_unset(t_data *data, t_cmd *cmd)
{
	t_envp	*curr;
	t_param	*node;

	node = cmd->params;
	while (node)
	{
		curr = data->mini_envp;
		if (ft_strchr(node->param_str, '=') || !check_valid_key(node->param_str))
			handle_error(data, EXP_NOTVALID, node->param_str);
		while (curr)
		{
			if (node)
				if (!ft_strncmp(node->param_str, curr->key, ft_strlen(node->param_str) + 1))
					env_lstdel(&data->mini_envp, curr);
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
}

char	*mini_getenv(t_data *data, char *key)
{
	t_envp	*node;

	node = data->mini_envp;
	while (node)
	{
		if (!ft_strncmp(key, node->key, ft_strlen(key) + 1))
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
