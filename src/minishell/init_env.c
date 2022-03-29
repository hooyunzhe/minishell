/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:37:55 by nfernand          #+#    #+#             */
/*   Updated: 2022/03/29 11:39:37 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*env_lstnew(char *key, char *value)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	node->key = ft_strdup(key);
	node->value = ft_substr(value, 1, ft_strlen(value));
	printf("%s", node->key);
	printf("=%s\n", node->value);
	node->next = NULL;

	return (node);
}

t_envp	*env_lstlast(t_envp *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		else
			lst = lst->next;
	}
	return (lst);
}

void	env_lstadd_back(t_envp **lst, t_envp *new)
{
	if (lst)
	{
		if (*lst)
			env_lstlast(*lst)->next = new;
		else
			*lst = new;
	}
}

void	init_env(t_data *data)
{
	int		i;
	char	*key;
	char	*value;
	t_envp	*head;

	i = 0;
	while (data->envp[i])
	{
		value = ft_strnstr(data->envp[i], "=", ft_strlen(data->envp[i]));
		key = ft_substr(data->envp[i], 0 ,ft_strlen(data->envp[i]) - ft_strlen(value));
		if (i == 0)
			head = env_lstnew(key, value);
		else
			env_lstadd_back(&head, env_lstnew(key, value));
		i++;
	}
	printf("passed\n");
}
