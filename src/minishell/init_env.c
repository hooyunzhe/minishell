/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:37:55 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/19 16:54:17 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_data *data)
{
	int		i;
	char	*key;
	char	*value;
	t_envp	*head;

	i = 0;
	head = NULL;
	while (data->envp[i])
	{
		value = ft_strdup(ft_strchr(data->envp[i], '=') + 1);
		key = ft_substr(data->envp[i], 0, ft_strlen(data->envp[i]) - ft_strlen(value) - 1);
		env_lstadd_back(&head, env_lstnew(key, value));
		i++;
	}
	data->mini_envp = head;
}
