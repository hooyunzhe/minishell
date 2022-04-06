/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:53:32 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/06 16:16:51 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_unset(t_data *data, char *key)
{
	t_envp	*node;
	t_envp	*temp;

	node = data->mini_envp;
	while (node)
	{
		if (node->next)
			if (!ft_strncmp(key, node->key, ft_strlen(key)))
				env_lstdelnext(temp);
		temp = node;
		node = node->next;
	}
}

void	mini_export(t_data *data, char *key, char *value)
{
	t_envp	*head;
	int		arg_count;

	arg_count = 0;
	if (arg_count == 0)
	{
		head = data->mini_envp;
		while (head)
		{
			if (ft_strncmp(head->key, "_", 1))
				printf("declare -x %s=\"%s\"\n", head->key, head->value);
			head = head->next;
		}
	}
	else
	{
		head = data->mini_envp;
		env_lstadd_back(&head, env_lstnew(key, value));
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
