/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:24:20 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/03/30 14:45:20 by nfernand         ###   ########.fr       */
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
	//minishell(&data);

	//mini_env(&data);
	//printf("\n\n");
	//mini_export(&data, "test", "motherfucker");
	//mini_export(&data, "test2", "motherfucker2");
	//mini_env(&data);
	//printf("\n\n");
	//mini_unset(&data, "test2");
	//mini_env(&data);
	//printf("%s\n", get_mini_env(&data, "COLORTERM"));
	
	//mini_env(&data);
	//printf("\n");
	//char	*test = "\"../\" \"src\"";
	//printf("PWD=%s\n", get_mini_env(&data, "PWD"));
	//printf("OLDPWD=%s\n", get_mini_env(&data, "OLDPWD"));
	//mini_chdir(&data, "../");
	//printf("PWD=%s\n", get_mini_env(&data, "PWD"));
	//printf("OLDPWD=%s\n", get_mini_env(&data, "OLDPWD"));
	//mini_chdir(&data, "\'-\'");
	////printf("\n");
	//printf("PWD=%s\n", get_mini_env(&data, "PWD"));
	//printf("OLDPWD=%s\n", get_mini_env(&data, "OLDPWD"));
	
	mini_chdir(&data, "");
	//printf("\n");
	printf("PWD=%s\n", get_mini_env(&data, "PWD"));
	printf("OLDPWD=%s\n", get_mini_env(&data, "OLDPWD"));
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
