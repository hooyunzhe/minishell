/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:53:32 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/27 10:31:01 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_unset(t_data *data, t_cmd *cmd)
{
	t_envp	*curr;
	t_param	*node;

	node = cmd->params;
	while (node)
	{
		curr = data->mini_envp;
		if (ft_strchr(node->param_str, '=')
			|| !check_valid_key(node->param_str))
			handle_error(data, EXP_NOTVALID, node->param_str);
		while (curr)
		{
			if (node)
				if (!ft_strncmp(node->param_str, curr->key,
						ft_strlen(node->param_str) + 1))
					env_lstdel(&data->mini_envp, curr);
			curr = curr->next;
		}
		node = node->next;
	}
}
