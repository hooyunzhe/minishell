/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:19:15 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 14:20:12 by hyun-zhe         ###   ########.fr       */
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
