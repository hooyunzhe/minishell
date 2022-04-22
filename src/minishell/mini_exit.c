/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:26:31 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/21 16:09:13 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strisnum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str - '0'))
			return (0);
		str++;
	}
	return (1);
}

void	mini_exit(t_data *data, t_cmd *cmd)
{
	t_param	*params;

	params = cmd->params;
	printf("exit\n");
	if (cmd->arg_count == 0)
	{
		tcsetattr(0, 0, &data->original_term);
		exit(0);
	}
	else if (cmd->arg_count > 1)
		handle_error(data, EXIT_TOOMANY, NULL);
	while (params && cmd->arg_count == 1)
	{
		if (params->param_type == ARGUMENT && ft_strisnum(params->param_str))
		{
			handle_error(data, EXIT_NONUM, params->param_str);
			tcsetattr(0, 0, &data->original_term);
			exit(0);
		}
		params = params->next;
	}
}