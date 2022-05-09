/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:11:55 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/09 10:43:11 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtolower(char *str)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[++i])
		res[i] = ft_tolower(str[i]);
	res[i] = '\0';
	return (res);
}

int	ft_strncasecmp(char *s1, char *s2, int n)
{
	if (n == 0)
		return (0);
	while (*s1 && ft_tolower(*s1) == ft_tolower(*s2) && --n)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)ft_tolower(*s1) - (unsigned char)ft_tolower(*s2));
}

char	**get_param_array(t_cmd *cmd)
{
	char	**res;
	t_param	*node;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (cmd->arg_count + 2));
	node = cmd->params;
	while (node)
	{
		if (node->param_type != REDIRECTION && node->param_type != IO_FILE)
			res[i++] = ft_strdup(node->param_str);
		node = node->next;
	}
	res[i] = NULL;
	return (res);
}

char	**env_lst_to_arr(t_envp *envp)
{
	char	**res;
	char	*temp;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (env_lst_getlen(envp) + 1));
	while (envp)
	{
		temp = ft_strjoin(envp->key, "=");
		res[i++] = ft_strjoin(temp, envp->value);
		free(temp);
		envp = envp->next;
	}
	res[i] = NULL;
	return (res);
}
