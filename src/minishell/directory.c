/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:40:52 by nfernand          #+#    #+#             */
/*   Updated: 2022/03/29 18:52:34 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_chdir(t_data *data, char *path)
{
	t_envp	*node;
	char	buff[200];
	char	oldpath[200];

	getcwd(oldpath, 200);
	printf("[%s]\n", path);
	if (!ft_strncmp(path, "~", 1))
		path = path + 1;
	if (chdir(path) == -1)
		return ((void)printf("cd: no such file or directory: %s\n", path));
	node = data->mini_envp;
	while (node)
	{
		if (!ft_strncmp("PWD", node->key, 3))
		{
			getcwd(buff, 200);
			free(node->value);
			node->value = ft_strdup(buff);
		}
		if (!ft_strncmp("OLDPWD", node->key, 6))
		{
			free(node->value);
			node->value = ft_strdup(oldpath);
		}
		node = node->next;
	}
}

void	mini_pwd(void)
{
	char	buff[200];

	printf("%s\n", getcwd(buff, 200));
}
