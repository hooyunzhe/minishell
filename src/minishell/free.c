/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:12:36 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/04 15:12:16 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_params(t_param *params)
{
	t_param	*temp;

	while (params != NULL)
	{
		temp = params;
		free(params->param_str);
		free(params);
		params = temp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*temp;
	
	while (cmds != NULL)
	{
		temp = cmds->next;
		free_params(cmds->params);
		free(cmds);
		cmds = temp;
	}
}

void	free_data(t_data *data)
{
	free_cmds(data->cmds);
}
