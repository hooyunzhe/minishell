/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:55:41 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 09:55:55 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
