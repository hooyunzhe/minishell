/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_lstutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:22:56 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 14:23:11 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_param	*param_lstfind(t_param *node, param type, int index)
{
	while (node)
	{
		if (node->param_type == type && index-- == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_param	*param_lstlast(t_param *param)
{
	while (param && param->next != NULL)
		param = param->next;
	return (param);
}
