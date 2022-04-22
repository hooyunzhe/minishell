/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:12:36 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/22 15:01:03 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	param_lstclear(t_param **params)
{
	t_param	*temp;

	while (*params != NULL)
	{
		temp = (*params)->next;
		if ((*params)->param_str)
			free((*params)->param_str);
		free(*params);
		*params = temp;
	}
}

void	cmd_lstclear(t_cmd **cmds)
{
	t_cmd	*temp;
	
	while (*cmds != NULL)
	{
		temp = (*cmds)->next;
		param_lstclear(&((*cmds)->params));
		free(*cmds);
		*cmds = temp;
	}
}

void	free_data(t_data *data)
{
	cmd_lstclear(&(data->cmds));
}
