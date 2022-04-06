/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfernand <nfernand@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:22:14 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/06 17:45:00 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_str(char *str, char *s1, char *s2)
{
	int		i;
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
			break ;
		i++;
	}
	if (i == (int)ft_strlen(str))
		return (NULL);
	len = ft_strlen(str) - ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * len + 1);
	ft_memmove(res, str, i + j - ft_strlen(s1));
	ft_memmove(res + i + j - ft_strlen(s1), s2, ft_strlen(s2));
	ft_memmove(res + i + j - ft_strlen(s1) + ft_strlen(s2),
		str + i + j, ft_strlen(str) - i + j);
	res[len] = '\0';
	return (res);
}

static void	update_env_pwd(t_data *data)
{
	char	buff[200];
	char	*oldpath;
	t_envp	*node;

	oldpath = ft_strdup(mini_getenv(data, "PWD"));
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
			node->value = oldpath;
		}
		node = node->next;
	}
}

static int	handle_replaced_path(t_data *data, t_cmd *cmd, char **path)
{
	char	*old;
	char	*new;
	char	*pwd;

	old = cmd->params->next->param_str;
	if (!ft_strncmp(old, "~", 1))
		old = ft_strjoin(mini_getenv(data, "HOME"), old + 1);
	new = cmd->params->next->next->param_str;
	if (!ft_strncmp(new, "~", 1))
		new = ft_strjoin(mini_getenv(data, "HOME"), new + 1);
	pwd = mini_getenv(data, "PWD");
	*path = replace_str(pwd, old, new);
	if (!(*path))
		return (printf("cd: string not in pwd: %s\n", old) * 0);
	return (1);
}	

void	mini_chdir(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	*param_path;

	if (cmd->arg_count > 2)
		return ((void)printf("cd: too many arguments\n"));
	else if (cmd->arg_count == 2)
		if (!handle_replaced_path(data, cmd, &path))
			return ;
	if (cmd->arg_count == 1)
	{
		param_path = cmd->params->next->param_str;
		if (!ft_strncmp(param_path, "-", 2))
			path = mini_getenv(data, "OLDPWD");
		else if (!ft_strncmp(param_path, "~", 1))
			path = ft_strjoin(mini_getenv(data, "HOME"), param_path + 1);
		else
			path = param_path;
	}
	else if (cmd->arg_count == 0 && cmd->param_count > 1)
		return ((void)printf("cd: no such file or directory: %s\n",
				cmd->params->next->param_str));
	else if (cmd->arg_count == 0)
		path = mini_getenv(data, "HOME");
	if (chdir(path) == -1)
		return ((void)printf("cd: no such file or directory: %s\n", path));
	update_env_pwd(data);
}

void	mini_pwd(void)
{
	char	buff[200];

	printf("%s\n", getcwd(buff, 200));
}
