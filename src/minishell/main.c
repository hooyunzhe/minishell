/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:24:20 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/19 17:02:13 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	
	(void)argv;
	(void)argc;
	data = new_data(envp);
	init_env(data);
	minishell(data);
	free_data(data);
	return (0);
}
