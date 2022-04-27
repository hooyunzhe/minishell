/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:24:20 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/27 14:02:59 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_launch_minishell(t_data *data, char *line)
{
	parser(data, line);
	count_args(data->cmds);
	add_history(line);
	executor(data);
	cmd_lstclear(&(data->cmds));
	data->cmd_count = 0;
	return (data->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	t_data	*data;
	
	data = new_data(envp);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		exit_status = ft_launch_minishell(data, argv[2]);
		ft_exit(data, exit_status);
  	}
	minishell(data);
	exit_status = data->exit_status;
	free_data(data);
	return (exit_status);
}
