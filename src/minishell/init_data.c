/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:37:55 by nfernand          #+#    #+#             */
/*   Updated: 2022/05/04 15:28:25 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_envspecial(char *key, char *value)
{
	char	*temp;

	if (!ft_strncmp(key, "SHLVL", 6))
	{
		temp = ft_itoa(ft_atoi(value) + 1);
		free(value);
		value = temp;
	}
	else if (!ft_strncmp(key, "_", 2))
	{
		free(value);
		value = ft_strdup("./minishell");
	}
	return (value);
}

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
		key = ft_substr(data->envp[i], 0,
				ft_strlen(data->envp[i]) - ft_strlen(value) - 1);
		value = set_envspecial(key, value);
		env_lstadd_back(&head, env_lstnew(key, value));
		i++;
	}
	data->mini_envp = head;
}

t_data	*new_data(char **envp)
{
	t_data	*data;
	t_term	original_term;

	data = malloc(sizeof(t_data));
	data->cmds = NULL;
	data->envp = envp;
	data->cmd_count = 0;
	tcgetattr(0, &original_term);
	data->original_term = original_term;
	data->exit_status = 0;
	init_env(data);
	return (data);
}

void	free_data(t_data *data)
{
	cmd_lstclear(&(data->cmds));
	env_lstclear(&(data->mini_envp));
}
