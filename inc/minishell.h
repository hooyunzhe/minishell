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

# define COMMAND 0
# define OPTION 1
# define ARGUMENT 2

# define CLOSED 0
# define SINGLE 1
# define DOUBLE 2
# define NORMAL 3

typedef struct s_param t_param;
typedef struct s_infile t_infile;
typedef struct s_outfile t_outfile;
typedef	struct s_cmd t_cmd;
typedef struct s_envp t_envp;

typedef struct s_param
{
	int		param_type;
	char	*param_str;
	t_param	*next;
}			t_param;

typedef struct s_cmd
{
	t_param		*params;
	t_cmd		*next;
}				t_cmd;

typedef struct s_envp
{
	char	*key;
	char	*value;
	t_envp	*next;
}			t_envp;

typedef struct s_data
{
	char	**envp;
	t_cmd	*cmds;
	t_envp	*mini_envp;
}			t_data;

t_data		*init_data(char **envp);
t_cmd		*init_cmd(void);
t_param		*init_param(void);
void		append_cmd(t_cmd **cmd, t_cmd *new_cmd);
void		append_param(t_param *param, char *param_str);
void		free_data(t_data *data);
int			minishell(t_data *data);
void		parser(t_data *data, char *line);

#endif