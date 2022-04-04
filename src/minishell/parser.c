#include "minishell.h"

void	print_args(t_data *data)
{
	int i;

	i = 0;
	while (i < data->arg_count)
	{
		printf("[%s] ", data->args[i]);
		// if (i != data->arg_count - 1)
		// 	printf(", ");
		i++;
	}
	printf("\n");
}

int		is_quotations(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c && c != ' ')
		return (3);
	return (0);
}

int		is_valid_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void	count_arguments(t_data *data, char *line)
{
	int i;
	int is_quotes;

	i = 0;
	is_quotes = is_quotations(line[0]);
	if (is_quotes == 1 || is_quotes == 2)
		i++;
	while (line[i])
	{
		if ((is_quotes == 1 && line[i] == '\'') || (is_quotes == 2 && line[i] == '\"')
			|| ((is_quotes == 3 && line[i] == ' ') || !line[i + 1]))
		{
			data->arg_count++;
			i += (is_quotes != 3);
			is_quotes = 0;
		}
		else if (!is_quotes)
			is_quotes = is_quotations(line[i]);
		i++;
	}
}

int		get_envlen(char *line, int *index)
{
	int	i;
	int len;
	char	*temp;

	(*index)++;
	i = *index;
	while (line[i] && is_valid_var(line[i]))
		i++;
	temp = ft_substr(line, *index, i - *index);
	len = ft_strlen(getenv(temp));
	(*index) = i - 1;
	free(temp);
	return (len);
}

char	*get_envvar(char *line, int index)
{
	int		i;

	i = index;
	while (line[i] && is_valid_var(line[i]))
		i++;
	return (ft_substr(line, index, i - index));
}

int	get_expanded_len(char *line)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
			len += get_envlen(line, &i);
		else
			len++;
		i++;
	}
	return (len + 1);
}

char	*get_expanded_line(char *line)
{
	int		i;
	int		j;
	char	*expanded_line;
	char	*env_var;
	int		is_quotes;

	expanded_line = malloc(get_expanded_len(line) * sizeof(char));
	i = 0;
	j = 0;
	is_quotes = 0;
	while (line[i])
	{
		if (is_quotes == 0 && is_quotations(line[i]))
			is_quotes = is_quotations(line[i]);
		else if ((is_quotes == 1 && line[i] == '\'') || (is_quotes == 2 && line[i] == '\"')
			|| (is_quotes == 3 && line[i] == ' '))
			is_quotes = 0;
		if (line[i] == '$' && is_quotes != 1)
		{
			if (line[i + 1] && ft_isdigit(line[i + 1]))
			{
				while(line[i + 1] && ft_isdigit(line[i + 1]))
					i++;
			}
			else
			{	
				env_var = get_envvar(line, i + 1);
				ft_memmove(&(expanded_line[j]), getenv(env_var), get_envlen(line, &i));
				j += ft_strlen(getenv(env_var));
				free(env_var);
			}
		}
		else
			expanded_line[j++] = line[i];
		i++;
	}
	expanded_line[j] = '\0';
	return (expanded_line);
}

int	get_unquoted_len(char *line)
{
	int		i;
	int		count;
	int		is_quotes;

	i = 0;
	count = 0;
	is_quotes = 0;
	while (line[i])
	{
		if (is_quotes == 0 && is_quotations(line[i]))
		{
			is_quotes = is_quotations(line[i]);
			if (is_quotes == 1 || is_quotes == 2)
				i++;
		}
		if ((is_quotes == 1 && line[i] == '\'') || (is_quotes == 2 && line[i] =='\"')
			|| (is_quotes == 3 && line[i] == ' '))
		{
			if (is_quotes == 3)
				count++;
			else
				count += 2;
			is_quotes = 0;
		}
		else
			count++;
		i++;
	}
	return (count);
}

char	*get_unquoted_line(char *line)
{
	char	*res;
	int		i;
	int		j;
	int		is_quotes;
	int		is_ended;

	i = 0;
	j = 0;
	is_quotes = 0;
	res = malloc(sizeof(char) * (get_unquoted_len(line) + 1));
	while (line[i])
	{
		if (is_quotes == 0 && is_quotations(line[i]))
		{
			is_quotes = is_quotations(line[i]);
			if ((is_quotes == 1 || is_quotes == 2) && i > 0 && line[i - 1] == ' ')
			{
				res[j++] = line[i];
				is_ended = is_quotes;
			}
			if (is_quotes == 1 || is_quotes == 2)
				i++;
		}
		if ((is_quotes == 1 && line[i] == '\'') || (is_quotes == 2 && line[i] =='\"')
			|| (is_quotes == 3 && line[i] == ' ') || !line[i + 1])
		{
			// printf("[%c] ", line[i]);
			if (is_quotes == 3)
				res[j++] = line[i];
			is_quotes = 0;
		}
		else
			res[j++] = line[i];
		if ((!line[i + 1] && is_quotes == 0) || (line[i + 1] == ' ' && is_quotes == 3))
		{
			if (is_ended == 2)
				res[j++] = '\"';
			else if (is_ended == 1)
				res[j++] = '\'';
			is_ended = 0;
		}
		i++;
	}
	res[j] = '\0';
	free(line);
	return (res);
}

void	save_arguments(t_data *data, char *line)
{
	int i;
	int j;
	int	len;
	int	is_quotes;

	i = -1;
	j = 0;
	len = 0;
	data->args = malloc(data->arg_count * sizeof(char *));
	is_quotes = 0;
	while (line[++i])
	{
		if (is_quotes == 0)
			is_quotes = is_quotations(line[i]);
		else if ((is_quotes == 1 && line[i] == '\'') || (is_quotes == 2 && line[i] == '\"')
			|| (is_quotes == 3 && (line[i] == ' ' || !line[i + 1])))
		{
			if (is_quotes == 1 || is_quotes == 2)
				len--;
			data->args[j++] = ft_substr(line, i - len, len + (!line[i + 1] && is_quotes == 3));
			i += (line[i + 1] && (is_quotes == 1 || is_quotes == 2));
			is_quotes = 0;
			len = 0;
		}
		if (is_quotes != 0)
			len++;
	}
}

void	check_input(t_data *data, char *line)
{
	char	*modified_line;
	// char	*no_redirection;

	count_arguments(data, line);
	modified_line = get_expanded_line(line);
	printf("expanded_line: %s\n", modified_line);
	modified_line = get_unquoted_line(modified_line);
	printf("unquoted line = %s\n", modified_line);
	// no_redirection = save_redirections(data, line);
	save_arguments(data, modified_line);
	print_args(data);
}

void	parser(t_data *data, char *line)
{
	check_input(data, line);
}
