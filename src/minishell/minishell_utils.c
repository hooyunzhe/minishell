/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:33:50 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/09 17:39:13 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_header(void)
{
	printf(RED " ███▄ ▄███▓    ██▓    ███▄    █     ██▓      "
		"▒██   ██▒       ██░ ██    ▓█████     ██▓        ██▓    \n"RESET);
	printf(RED "▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒      "
		"▒▒ █ █ ▒░      ▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒    \n"RESET);
	printf(RED "▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒      "
		"░░  █   ░      ▒██▀▀██░   ▒███      ▒██░       ▒██░    \n"RESET);
	printf(RED "▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░      "
		" ░ █ █ ▒       ░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░    \n"RESET);
	printf(RED "▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░      "
		"▒██▒ ▒██▒      ░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒\n"RESET);
	printf(RED "░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓        "
		"▒▒ ░ ░▓ ░       ▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░\n"RESET);
	printf(RED "░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░      "
		"░░   ░▒ ░       ▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░\n"RESET);
	printf(RED "░      ░       ▒ ░      ░   ░ ░     ▒ ░      "
		" ░    ░         ░  ░░ ░      ░        ░ ░        ░ ░   \n"RESET);
	printf(RED "       ░       ░              ░     ░        "
		" ░    ░         ░  ░  ░      ░  ░       ░  ░       ░  ░\n"RESET);
}

void	ft_freestrs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	ft_exit(t_data *data, int exit_num)
{
	free_data(data);
	exit(exit_num);
}

/**
	supposedly to reset the terminal to its original state but fuck it cause it breaks minishell instead
	tcsetattr(0, 0, &data->original_term);
**/
