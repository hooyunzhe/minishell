/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:36:26 by nfernand          #+#    #+#             */
/*   Updated: 2022/04/19 10:34:12 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		strncmpn(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return ((unsigned char)str[i] - (unsigned char)c);
		i++;
	}
	return (0);
}

void	print_echo(char *str, int type)
{
	if (type == 0)
		printf("%s", str);
	else if (type == 1)
		printf("%s ", str);
}

void	mini_echo(t_param *param)
{
	t_param	*node;
	int		has_option;
	int		chain_n;

	node = param->next;
	has_option = 0;
	chain_n = 0;
	while (node)
	{
		// printf("[%s]\n", node->param_str);
		if (node->param_type == OPTION)
		{
			if (!strncmpn(node->param_str + 1, 'n') && chain_n == 0)
				has_option = 1;
			else
			{
				chain_n = 1;
				print_echo(node->param_str, node->next != NULL);
			}
		}
		if (node->param_type == ARGUMENT)
			print_echo(node->param_str, node->next != NULL);
		node = node->next;
	}
	if (has_option == 0)
		printf("\n");
}
