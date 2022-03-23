/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:33:06 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/03/23 14:02:15 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		ft_isspace(char c)
// {
// 	return (c == ' ');
// }


int	ft_cmdlen(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != ' ')
		len++;
	return (len + 1);
}

void	check_command(t_data *data, char **line)
{
	int		i;

	i = 0;
	data->command = malloc(ft_cmdlen(*line) * sizeof(char));
	if (!data->command)
		return ;
		// return (0);
	while (**line && **line == ' ')
		(*line)++;
	while (**line && **line != ' ')
		data->command[i++] = *(*line)++;
	data->command[i] = '\0';
}

void	save_options(t_data *data, char **line, int option_count)
{
	int		i;
	int		j;
	int		has_option;

	i = 0;
	j = 0;
	has_option = 0;
	data->options = malloc((option_count + 2) * sizeof(char *));
	data->options[j++] = '-';
	while (**line && **line == ' ')
		(*line)++;
	while ((*line)[i])
	{
		if ((*line)[i + 1] && (*line)[i] == ' ' && (*line)[i + 1] != '-')
			break ;
		if (has_option && (*line)[i] == ' ')
			has_option = 0;
		if (has_option)
			data->options[j++] = (*line)[i];
		else if ((*line)[i] == '-')
			has_option = 1;
		i++;
	}
	data->options[j] = '\0';
}

void	check_options(t_data *data, char **line)
{
	int	i;
	int	has_option;
	int option_count;

	i = 0;
	has_option = 0;
	option_count = 0;
	while (**line && **line == ' ')
		(*line)++;
	if (**line != '-')
		return ;
	while ((*line)[i])
	{
		if ((*line)[i + 1] && (*line)[i] == ' ' && (*line)[i + 1] != '-')
			break ;
		if (has_option && (*line)[i] == ' ')
			has_option = 0;
		if (has_option)
			option_count++; 
		else if ((*line)[i] == '-')
			has_option = 1;
		i++;
	}
	if (option_count)
		save_options(data, line, option_count);
	(*line) += i;
}

void	check_arguments(t_data *data, char **line)
{
	int	i;
	int	arg_count;
	int	is_argument;
	int	is_quotes;

	i = 0;
	is_argument = 0;
	is_quotes = 0;
	arg_count = 0;
	while ((*line)[i] && (*line)[i] == ' ')
		i++;
	while ((*line)[i])
	{
		if (((is_quotes == 1 && (*line)[i] == '\'') || (is_quotes == 2 && (*line)[i] == '\"')) && !is_argument)
		{
			arg_count++;
			is_quotes = 0;
		}
		else if ((*line)[i] == '\'' && !is_argument && !is_quotes)
			is_quotes = 1;
		else if ((*line)[i] == '\"' && !is_argument && !is_quotes)
		{
			is_quotes = 2;
		}
		else if ((!is_argument && (*line)[i] != ' ') && !is_quotes)
			is_argument = 1;
		else if ((is_argument && ((*line)[i] == ' ' || !(*line)[i + 1])) && !is_quotes)
		{
			arg_count++;
			is_argument = 0;
		}
		i++;
	}
	data->arg_count = arg_count;
}

int		is_quotations(char **line)
{
	if ((*line)[0] == '\'' || (*line)[0] == '\"')
	{
		if ((*line)[0] == '\"')
		{
			(*line)++;
			return (2);
		}
		else
		{	
			(*line)++;
			return (1);
		}
	}
	return (3);
}

int	get_envlen(char *line, int *index, int is_args)
{
	int		env_len;
	char	*env_var;
	
	env_len = 0;
	// printf("===========================\n");
	// printf("get_evnlen entered %s\n", line);
	while (line[*index] && line[*index] != '$' && line[*index] != ' ' &&
		((is_args == 2 && line[*index] != '\"') || (is_args == 3)))
	{ 
		env_len++;
		(*index)++;
	}
	// printf("env_len = %d\n", env_len);
	// printf("get_evnlen passed %s\n", line);
	env_var = malloc(sizeof(char) * (env_len + 1));
	env_var[env_len] = '\0';
	ft_memmove(env_var, &(line[*index - env_len]), env_len);
	// if (getenv(env_var))
	env_len = ft_strlen(getenv(env_var));
	// printf("===========================\n");
	return (env_len);
}

int	save_env(t_data *data, char *arg ,char *line, int *index, int is_args)
{
	int		env_len;
	int		str_len;
	// char	*env_var;
	char	*temp_var;

	(void)data;
	str_len = 0;
	// printf("ENTERED\n");
	// printf("line: %s\n", line);
	while (line[*index] && line[*index] != '$' && line[*index] != ' ' &&
		((is_args == 2 && line[*index] != '\"') || (is_args == 3)))
	{
		str_len++;
		(*index)++;
	}
	// printf("line: %s\n", line + *index);
	temp_var = malloc(sizeof(char) * (str_len + 1));
	ft_memmove(temp_var, &(line[*index - str_len]), str_len);
	ft_memmove(arg, getenv(temp_var), ft_strlen(getenv(temp_var)));
	// printf("temp_var = %s\n", temp_var);
	// printf("%s\n", arg);
	// printf("index = %d\n", *index);
	// printf("str_len: %d\n", str_len);
	env_len = ft_strlen(getenv(temp_var));
	// printf("%d\n", env_len);
	return (env_len);
}

int	save_arguments(t_data *data, char **line, int args_index)
{
	int		i;
	int		j;
	int		is_args;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	is_args = is_quotations(line);
	// printf("i: %d\n", i);
	// printf("is_args = %d\n", is_args);
	while ((*line)[i])
	{
		// printf("[%c]\n", (*line)[i]);
		if (is_args == 3 && (*line)[i] == ' ')
			break ;
		if ((is_args == 2 && (*line)[i] == '\"') || (is_args == 1 && (*line)[i] == '\''))
			break ;
		if (is_args != 1 && (*line)[i] == '$')
			len += get_envlen((*line) + 1, &i, is_args);
		else
			len++;
		i++;
	}
	// printf("%s\n", (*line));
	// printf("is_args = %d\n", is_args);
	// printf("len = %d\n", len);
	data->args[args_index] = malloc((len + 1) * sizeof(char));
	data->args[args_index][len] = '\0';
	i = 0;
	// printf("%s\n", (*line));
	while ((*line)[i])
	{
		// printf("i: %d\n", i);
		// printf("[%c]\n", (*line)[i]);
		// printf("arg: [%s]\n", data->args[args_index]);
		if (is_args == 3 && (*line)[i] == ' ')
			break ;
		if ((is_args == 2 && (*line)[i] == '\"') || (is_args == 1 && (*line)[i] == '\''))
		{
			// printf("entered\n");
			break ;
		}
		if (is_args != 1 && (*line)[i] == '$')
			j += save_env(data, data->args[args_index] + j, (*line) + 1, &i, is_args);
		else
			data->args[args_index][j++] = (*line)[i];
		i++;
	}
	// printf("len = %d\n", len);
	// printf("[%s]\n",data->args[args_index]);
	// (void)data;
	// printf("i: %d\n", i);
	return (i + 2 * (is_args == 1 || is_args == 2));
}

void	get_arguments(t_data *data, char **line)
{
	int	args_index;

	args_index = 0;
	data->args = malloc(data->arg_count * sizeof(char *));
	if (!data->args)
		// return (0);
		return ;
	while (**line)
	{
		while (**line && **line == ' ')
			(*line)++;
		(*line) += save_arguments(data, line, args_index++);
		// (*line)++;
	}
}

void	check_input(t_data *data, char *line)
{
	check_command(data, &line);
	check_options(data, &line);
	check_arguments(data, &line);
	get_arguments(data, &line);
	printf("command : \"%s\"\noptions : \"%s\"\narg count : %d\n", data->command, data->options, data->arg_count);
	int i = 0;
	printf("arguments : ");
	while (i < data->arg_count)
	{
		printf("[%s] ",data->args[i]);
		i++;
	}
	printf("\n");
}

void	parser(t_data *data, char *line)
{
	check_input(data, line);
}