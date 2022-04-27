/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:05:43 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 10:26:47 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_str(char *str, char *s1, char *s2)
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

void	update_env_pwd(t_data *data)
{
	char	*buff;
	char	*oldpath;
	t_envp	*node;

	oldpath = ft_strdup(mini_getenv(data, "PWD"));
	node = data->mini_envp;
	while (node)
	{
		if (!ft_strncmp("PWD", node->key, 3))
		{
			buff = getcwd(NULL, 0);
			free(node->value);
			node->value = ft_strdup(buff);
			free(buff);
		}
		if (!ft_strncmp("OLDPWD", node->key, 6))
		{
			free(node->value);
			node->value = oldpath;
		}
		node = node->next;
	}
}

char	*find_string(t_param *param, int count)
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

int	handle_replaced_path(t_data *data, t_cmd *cmd, char **path)
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

int	check_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!key || ft_isdigit(key[i]) || key[i] == '=')
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
