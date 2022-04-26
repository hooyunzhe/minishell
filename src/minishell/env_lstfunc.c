/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:50:54 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/25 16:45:47 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*env_lstfind(t_envp *lst, char *key)
{
	while (lst)
	{
		if (!ft_strncmp(lst->key, key, ft_strlen(key) + 1))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
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

t_envp	*env_lstnew(char *key, char *value)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	node->key = key;
	node->value = value;
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

int		env_lst_getlen(t_envp *envp)
{
	int	count;

	count = 0;
	while (envp)
	{
		count++;
		envp = envp->next;
	}
	return (count);
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

void	env_lstdelnext(t_envp *head)
{
	t_envp	*to_del;

	if (head)
	{
		if (head->next)
		{
			to_del = head->next;
			head->next = to_del->next;
			free(to_del->key);
			free(to_del->value);
			free(to_del);
		}
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