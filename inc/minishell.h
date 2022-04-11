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

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

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

typedef enum enclose
{
	CLOSED,
	SINGLE,
	DOUBLE,
	NORMAL
}	enclose;

typedef enum error_id
{
	CD_NODIR,
	CD_TOOMANY,
	CD_STRNOTIN,
	EXP_NOTVALID,
	EXIT_NONUM,
	EXIT_TOOMANY
}	error_id;

typedef enum builtin_cmd
{
	MINI_ECHO,
	MINI_CD,
	MINI_PWD,
	MINI_EXPORT,
	MINI_UNSET,
	MINI_ENV,
	MINI_EXIT
}	builtin_cmd;

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
	int		cmd_count;
	t_envp	*mini_envp;
}			t_data;

int			handle_error(error_id id, char *param);
void		cmd_lstadd_back(t_cmd **cmd, t_cmd *new_cmd);
t_cmd		*new_cmd(void);
t_data		*new_data(char **envp);
void		free_data(t_data *data);
void		parser(t_data *data, char *line);
int			minishell(t_data *data);
void		init_env(t_data *data);

// ---------- param linked list functions ---------

t_param	*new_param(char *param_str, param param_type, redirection redirection_type);
t_param	*param_lstfind(t_param *node, param type, int index);
t_param	*param_lstlast(t_param *param);
void	param_lstadd_back(t_param **param, t_param *new_param);

// ---------- env linked list functions ---------

t_envp	*env_lstnew(char *key, char *value);
t_envp	*env_lstlast(t_envp *lst);
void	env_lstadd_back(t_envp **lst, t_envp *new);
void	env_lstdelnext(t_envp *head);

// ---------- get env functions ------------

void	mini_env(t_data *data);
char	*mini_getenv(t_data *data, char *key);
void	mini_export(t_data *data, t_cmd *cmd);
void	mini_unset(t_data *data, t_cmd *cmd);


//----------- directory functions ---------

void	mini_pwd(void);
void	mini_chdir(t_data *data, t_cmd *cmd);

//----------- signal functions -------------

void	read_signals();
void	mini_echo(t_param *param);

//----------- execute functions -------------

void	executor(t_data *data);

#endif
