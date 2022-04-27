/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_lstfunc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:33:08 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 14:23:55 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_param	*param_lstnew(char *param_str, param param_type, redirection redirection_type)
{
	t_param	*params;
	
	params = malloc(sizeof(t_param));
	params->param_str = param_str;
	params->param_type = param_type;
	params->redirection_type = redirection_type;
	params->next = NULL;
	return (params);
}

void	param_lstadd_back(t_param **param, t_param *param_lstnew)
{
	t_param	*current;

	if (param)
	{
		if (*param)
		{
			current = *param;
			while (current->next != NULL)
				current = current->next;
			current->next = param_lstnew;
		}
		else
			*param = param_lstnew;
	}
}

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
