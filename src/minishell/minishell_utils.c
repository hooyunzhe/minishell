/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:33:50 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/05/20 11:01:09 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_parent_exit(t_data *data, int exit_num)
{
	free_data(data);
	print_outro();
	// system("leaks minishell");
	tcsetattr(0, 0, &data->original_term);
	exit(exit_num);
}

/**
    BELOW IS FALSE  
	supposedly to reset the terminal to its original 
	state but fuck it cause it breaks minishell instead
	tcsetattr(0, 0, &data->original_term);
**/
