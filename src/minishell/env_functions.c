/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:53:32 by nfernand          #+#    #+#             */
/*   Updated: 2022/03/29 17:27:19 by nfernand         ###   ########.fr       */
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

	head = data->mini_envp;
	env_lstadd_back(&head, env_lstnew(key, value));
}

char	*get_mini_env(t_data *data, char *key)
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
