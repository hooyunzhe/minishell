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

typedef enum param
{
	COMMAND,
	OPTION,
	ARGUMENT,
	REDIRECTION,
	IO_FILE
}	param;

typedef enum redirection
{	
	S_IN,
	S_OUT,
	D_IN,
	D_OUT
}	redirection;


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
	param		param_type;
	redirection	redirection_type;
	char		*param_str;
	t_param		*next;
}			t_param;

typedef struct s_cmd
{
	int			param_count;
	int			arg_count;
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

t_param		*param_lstlast(t_param *param);
void		param_lstadd_back(t_param **param, t_param *new_param);
void		cmd_lstadd_back(t_cmd **cmd, t_cmd *new_cmd);
t_param		*new_param(char *param_str, param param_type, redirection redirection_type);
t_cmd		*new_cmd(void);
t_data		*new_data(char **envp);
void		free_data(t_data *data);
void		parser(t_data *data, char *line);
int			minishell(t_data *data);
void		init_env(t_data *data);	

// ---------- env linked list functions ---------

t_envp	*env_lstnew(char *key, char *value);
t_envp	*env_lstlast(t_envp *lst);
void	env_lstadd_back(t_envp **lst, t_envp *new);
void	env_lstdelnext(t_envp *head);

// ---------- get env functions ------------

void	mini_env(t_data *data);
char	*mini_getenv(t_data *data, char *key);
void	mini_export(t_data *data, char *key, char *value);
void	mini_unset(t_data *data, char *key);


//----------- directory functions ---------

void	mini_pwd(void);
void	mini_chdir(t_data *data, t_cmd *cmd);

//----------- signal functions -------------

void	read_signals();
void	mini_echo(t_cmd *cmd);

#endif
