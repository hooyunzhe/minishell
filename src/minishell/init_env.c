/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:37:55 by nfernand          #+#    #+#             */
/*   Updated: 2022/03/29 12:28:09 by nfernand         ###   ########.fr       */
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
	while (data->envp[i])
	{
		value = ft_strnstr(data->envp[i], "=", ft_strlen(data->envp[i]));
		key = ft_substr(data->envp[i], 0 ,ft_strlen(data->envp[i]) - ft_strlen(value));
		if (i == 0)
			head = env_lstnew(key, value + 1);
		else
			env_lstadd_back(&head, env_lstnew(key, value + 1));
		i++;
	}
	data->mini_envp = head;
}
