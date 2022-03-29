/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:24:20 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/03/29 10:37:47 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argv;
	(void)argc;
	
	data.envp = envp;
	init_env(&data);
	minishell(&data);
	return (0);
}


// #include <unistd.h>
// int	main(int argc, char **argv, char **envp)
// {
// 	// t_data	data;
	
// 	(void)argv;
// 	(void)argc;
	
// 	// data.envp = envp;
// 	// minishell(&data);
// 	char *arr[] = {"cat", "Make", "file", NULL};
// 	execve("/bin/cat", arr, envp);
// 	// dup2(0, open("Makefile", O_RDONLY));
// 	// pid_t pid;
// 	// pid = fork();
// 	// if (pid == 0)
// 	// {
// 	// 	execeve();
// 	// }
// 	return (0);
// }
