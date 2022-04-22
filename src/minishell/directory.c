/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:22:14 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/21 16:16:58 by hyun-zhe         ###   ########.fr       */
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

static char	*find_string(t_param *param, int count)
{
	int	i;

	i = 0;
	while (param)
	{
		if (param->param_type == OPTION || param->param_type == ARGUMENT)
		{
			if (i == count)
				return (param->param_str);
			i++;
		}
		param = param->next;
	}
	return (NULL);
}

static int	handle_replaced_path(t_data *data, t_cmd *cmd, char **path)
{
	char	*old;
	char	*new;
	char	*pwd;

	old = find_string(cmd->params, 0);
	new = find_string(cmd->params, 1);
	pwd = mini_getenv(data, "PWD");
	*path = replace_str(pwd, old, new);
	if (!(*path))
	{
		handle_error(data, CD_STRNOTIN, old);
		return (1);
	}
	return (0);
}	

void	mini_chdir(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	*param_path;

	if ((cmd->option_count + cmd->arg_count) > 2)
		return (handle_error(data, CD_TOOMANY, NULL));
	else if ((cmd->option_count + cmd->arg_count) == 2)
	{
		if (handle_replaced_path(data, cmd, &path) == 1)
			return ;
	}
	else if ((cmd->option_count + cmd->arg_count) == 1)
	{
		param_path = find_string(cmd->params, 0);
		if (!ft_strncmp(param_path, "-", 2))
			path = mini_getenv(data, "OLDPWD");
		else
			path = param_path;
	}
	else
		path = mini_getenv(data, "HOME");
	if (chdir(path) == -1)
	{
		if (errno == ENOTDIR)
			handle_error(data, CD_NOTADIR, path);
		else if (errno == EACCES)
			handle_error(data, CD_NOACCESS, path);
		else
			handle_error(data, CD_NODIR, path);
	}
	else
		update_env_pwd(data);
}

void	mini_pwd(void)
{
	char	buff[200];

	printf("%s\n", getcwd(buff, 200));
}
