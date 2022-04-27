/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:50:54 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/27 14:22:09 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*env_lstnew(char *key, char *value)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

int	env_lstupdate(t_envp *lst, char *key, char *value)
{
	while (lst)
	{
		if (!ft_strncmp(lst->key, key, ft_strlen(key) + 1))
		{
			free(lst->value);
			lst->value = value;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	env_lstadd_back(t_envp **lst, t_envp *new)
{
	t_envp	*last;

	if (lst)
	{
		if (*lst)
		{
			last = *lst;
			while (last->next != NULL)
				last = last->next;
			last->next = new;
		}
		else
			*lst = new;
	}
}

void	env_lstdel(t_envp **head, t_envp *to_del)
{
	t_envp	*node;

	if (*head)
	{
		node = *head;
		if (*head == to_del)
			*head = to_del->next;
		while (node)
		{
			if (node->next == to_del || node == to_del)
			{
				node->next = to_del->next;
				free(to_del->key);
				free(to_del->value);
				free(to_del);
			}
			node = node->next;
		}
	}
}

void	env_lstclear(t_envp **envp)
{
	t_envp	*temp;

	while (*envp != NULL)
	{
		temp = (*envp)->next;
		free((*envp)->key);
		free((*envp)->value);
		free(*envp);
		*envp = temp;
	}
}
