/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:24:20 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/03/23 16:42:12 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	// t_data	data;
	
	(void)argv;
	(void)argc;
	
	// data.envp = envp;
	// minishell(&data);
	char	*args[] = { "-n","test",  NULL};
	execve("/bin/echo", args, envp);
	return (0);
}