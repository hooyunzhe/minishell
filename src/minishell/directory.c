/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:40:52 by nfernand          #+#    #+#             */
/*   Updated: 2022/03/31 17:37:30 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_str(char *str, char *s1, char *s2)
{
	int 	i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && s1[j] && str[i + j] == s1[j])
			j++;
		if (!s1[j])
			break;
		i++;
	}
	if (i == (int)ft_strlen(str))
		return (NULL);
	printf("\n");
	printf("i = %d\n", i);
	printf("before = [%.*s]\n", i + j - (int)ft_strlen(s1), str);
	printf("after = [%s]\n\n", str + i + j);
	len = ft_strlen(str) - ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * len + 1);
	ft_memmove(res, str , i + j - ft_strlen(s1));
	ft_memmove(res + i + j - ft_strlen(s1), s2 , ft_strlen(s2));
	ft_memmove(res + i + j - ft_strlen(s1) + ft_strlen(s2), str + i + j, ft_strlen(str) - i + j);
	res[len] = '\0';
	printf("res = %s\n", res);
	return (res);
}

void	mini_chdir(t_data *data, char *path)
{
	t_envp	*node;
	char	buff[200];
	char	oldpath[200];
	int		arg_count = 0;

	getcwd(oldpath, 200);
	printf("[%s]\n\n", path);
	if (arg_count == 0)
		path = "~";
	if (arg_count == 2)
	{
		char	*old = "!";
		char	*new = "test";
		char	*PWD;
		PWD = get_mini_env(data, "PWD");
		printf("PWD = %s\nold = %s\nnew = %s\n",PWD, old, new);
		char *temp = replace_str(PWD, old, new);

		printf("combined = %s\n", temp);
		if (!temp)
			return ((void)printf("cd: string not in pwd: %s\n", old));
		//printf("test  = %s\n", ft_strnstr(PWD, old, ft_strlen(PWD)));
		//printf("PWD = [%s]\n", PWD);
		//char *temp = ft_strnstr(PWD, old, ft_strlen(PWD));
		//printf("temp = [%s]\n", temp);
	}
	if (arg_count > 2)
		return ((void)printf("cd: too many arguments\n"));
	if (((path[0] == '\'' || path[0] == '\"') && path[1] == '-') || path[0] == '-')
		path = get_mini_env(data, "OLDPWD");
	if (!ft_strncmp(path, "~", 1))
		path = ft_strjoin(get_mini_env(data, "HOME"), path + 1);
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
