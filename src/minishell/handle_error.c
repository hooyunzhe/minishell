/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:56:13 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/04/19 11:31:22 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// we need to change the fd to 2 to print to stderror
int	handle_error(error_id id, char *param)
{
	if (id == EXE_NOCMD)
		printf("minishell: command not found: %s\n", param);
	else if (id == EXE_NOFILE)
		printf("minishell: no such file or directory: %s\n", param);
	else if (id == EXE_NOPERM)
		printf("minishell: permission denied: %s\n", param);
	else if (id == CD_NODIR)
		printf("cd: no such file or directory: %s\n", param);
	else if (id == CD_TOOMANY)
		printf("cd: too many arguments\n");
	else if (id == CD_STRNOTIN)
		printf("cd: string not in pwd: %s\n", param);
	else if (id == CD_NOTADIR)
		printf("cd: not a directory: %s\n", param);
	else if (id == CD_NOACCESS)
		printf("cd: permission denied: %s\n", param);
	else if (id == EXP_NOTVALID)
		printf("export: not a valid identifier: %s\n", param);
	else if (id == EXIT_NONUM)
		printf("exit: numeric argument required: %s\n", param);
	else if (id == EXIT_TOOMANY)
		printf("exit: too many arguments\n");
	return (1);
}