/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:22:40 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/03/29 10:37:13 by nfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_data *data)
{
	char	*line;

	line = readline("minishell % ");
	while (line != NULL)
	{
		parser(data, line);
		free(line);
		data->arg_count = 0;
		line = readline("minishell % ");
	}
	return (0);
}
