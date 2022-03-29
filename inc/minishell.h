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

typedef struct s_infile
{
	char		*infile_str;
	t_infile	*next;
}				t_infile;

typedef struct s_outfile
{
	char		*outfile_str;
	t_outfile	*next;
}				t_outfile;

typedef struct s_cmd
{
	t_param		*params;
	t_infile	*infiles;
	t_outfile	*outfiles;
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
	char	**args;
	int		arg_count;
	t_cmd	*cmds;
	t_envp	*mini_envp;
}			t_data;

int		minishell(t_data *data);
void	parser(t_data *data, char *line);
void	init_env(t_data *data);	

#endif
