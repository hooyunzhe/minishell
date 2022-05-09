/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:26:31 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/09 14:39:21 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '+' || str[i] == '-')
		i++;
	if (i > 1)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	mini_exit(t_data *data, t_cmd *cmd)
{
	t_param	*params;

	params = cmd->params;
	printf("exit\n");
	if ((cmd->arg_count + cmd->option_count) == 0)
		ft_exit(data, data->exit_status);
	else if ((cmd->arg_count + cmd->option_count) > 1)
	{
		handle_error(data, EXIT_TOOMANY, NULL);
		if (!ft_strisnum(params->next->param_str))
			data->exit_status = 255;
	}
	while (params && (cmd->arg_count + cmd->option_count) == 1)
	{
		if (params->param_type == ARGUMENT || params->param_type == OPTION)
		{
			if (!ft_strisnum(params->param_str))
			{
				handle_error(data, EXIT_NONUM, params->param_str);
				ft_exit(data, 255);
			}
			ft_exit(data, ft_atoi(params->param_str));
		}
		params = params->next;
	}
}
