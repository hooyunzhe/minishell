#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h> //opendir
# include <termios.h> //tcsetattr tcgetattr

# include <curses.h> // tgetent tgetflag tgetnumt getstr tgoto tputs
# include <term.h>

typedef struct s_data
{
	char	**envp;
	char	*command;
	char	*options;
	char	**args;
	char	**params;
	int		arg_count;
}			t_data;

int		minishell(t_data *data);
void	parser(t_data *data, char *line);

#endif