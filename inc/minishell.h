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
# include <term.h>
# include <termios.h>
# include <errno.h> 

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

# define B_RED		"\e[1;91m"

typedef enum e_paramtype
{
	COMMAND,
	OPTION,
	ARGUMENT,
	REDIRECTION,
	IO_FILE
}	t_paramtype;

typedef enum e_redirectiontype
{	
	S_IN,
	S_OUT,
	D_IN,
	D_OUT
}	t_redirectiontype;

typedef enum e_enclosetype
{
	CLOSED,
	SINGLE,
	DOUBLE,
	NORMAL
}	t_enclosetype;

typedef enum e_error_id
{
	PARSE_ERR,
	EXE_NOCMD,
	EXE_NOFILE,
	EXE_NOPERM,
	CD_NODIR,
	CD_TOOMANY,
	CD_STRNOTIN,
	CD_NOTADIR,
	CD_NOACCESS,
	EXP_NOTVALID,
	UNS_NOTVALID,
	EXIT_NONUM,
	EXIT_TOOMANY
}	t_error_id;

typedef enum e_cmdtype
{
	NO_CMD,
	NON_BUILTIN,
	MINI_ECHO,
	MINI_CD,
	MINI_PWD,
	MINI_EXPORT,
	MINI_UNSET,
	MINI_ENV,
	MINI_EXIT
}	t_cmdtype;

typedef struct s_param		t_param;
typedef struct s_infile		t_infile;
typedef struct s_outfile	t_outfile;
typedef struct s_cmd		t_cmd;
typedef struct s_envp		t_envp;

typedef struct termios		t_term;

typedef struct s_param
{
	t_paramtype			param_type;
	t_redirectiontype	redirection_type;
	char				*param_str;
	t_param				*next;
}						t_param;

typedef struct s_cmd
{
	int			param_count;
	int			arg_count;
	int			option_count;
	int			input_fd;
	int			output_fd;
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
	t_envp	*mini_envp;
	t_cmd	*cmds;
	int		cmd_count;
	int		exit_status;
	t_term	original_term;
}			t_data;

// ---------- minishell functions ---------------

int					minishell(t_data *data);

// utils -----------------------------

void				handle_error(t_data *data, t_error_id id, char *param);
t_data				*new_data(char **envp);
void				free_data(t_data *data);
void				count_args(t_cmd *cmd);
char				*mini_getenv(t_data *data, char *key);
void				ft_freestrs(char **strs);
void				ft_exit(t_data *data, int exit_num);
void				print_intro(void);
void				print_outro(void);

// ---------- parser functions ---------------

void				parser(t_data *data, char *line);

// utils -----------------------------

char				**get_cmd_strs(char *line);
int					get_cmd_count(char *line);
int					check_redirection_start(char *str);

// check -----------------------------

char				check_input(char *str);

// type -----------------------------

t_enclosetype		is_closed(t_enclosetype enclose_type, char current_char);
t_enclosetype		get_enclose_type(t_enclosetype enclose_type,
						char current_char);
t_paramtype			get_param_type(char *param_str);
void				update_param_type(t_param *params);
t_redirectiontype	get_redirection_type(char *param_str,
						t_paramtype param_type);

// expansion -----------------------------

char				*get_expanded_param(t_data *data, char *line, int len);
char				*get_envvar(char *line, int index);
int					get_expanded_len(t_data *data, char *line);
int					has_expand(char *line);

// unquotation -----------------------------

int					get_unquoted_len(char *line);
char				*get_unquoted_param(char *line);

// ---------- command linked list functions ---------

t_cmd				*cmd_lstnew(void);
void				cmd_lstclear(t_cmd **cmds);
void				cmd_lstadd_back(t_cmd **cmd, t_cmd *new_cmd);

// ---------- param linked list functions ---------

t_param				*param_lstnew(char *param_str, t_paramtype param_type,
						t_redirectiontype redirection_type);
t_param				*param_lstfind(t_param *node, t_paramtype type, int index);
t_param				*param_lstlast(t_param *param);
void				param_lstadd_back(t_param **param, t_param *param_lstnew);
void				param_lstclear(t_param **params);

// ---------- env linked list functions ---------

t_envp				*env_lstfind(t_envp *lst, char *key);
t_envp				*env_lstnew(char *key, char *value);
int					env_lstupdate(t_envp *lst, char *key, char *value);
int					env_lst_getlen(t_envp *envp);
void				env_lstadd_back(t_envp **lst, t_envp *new);
void				env_lstdel(t_envp **head, t_envp *to_del);
void				env_lstclear(t_envp **envp);

// ---------- builtin functions ------------

void				mini_export(t_data *data, t_cmd *cmd);
void				mini_unset(t_data *data, t_cmd *cmd);
void				mini_echo(t_param *param);
void				mini_env(t_data *data);
void				mini_exit(t_data *data, t_cmd *cmd);
void				mini_pwd(void);
void				mini_cd(t_data *data, t_cmd *cmd);
void				mini_pwd(void);

// export and unset utils --------------

int					check_valid_key(char *key);

// cd utils -----------------------------

char				*replace_str(char *str, char *s1, char *s2);
void				update_env_pwd(t_data *data);
char				*find_string(t_param *param, int count);
int					handle_replaced_path(t_data *data, t_cmd *cmd, char **path);

//----------- signal functions -------------

void				read_signals(t_data *data);

//----------- execute functions -------------

void				executor(t_data *data);
int					handle_redirections(t_data *data, t_cmd *cmd,
						t_param *params);

// execute utils -----------------------

char				*ft_strtolower(char *str);
int					ft_strncasecmp(char *s1, char *s2, int n);
char				**get_param_array(t_cmd *cmd);
char				**env_lst_to_arr(t_envp *envp);

// fd utils ----------------------------

void				swap_old_fd(int *old_stdin, int *old_stdout, int type);
void				swap_new_fd(t_cmd *cmd);

// execute builtin ---------------------

t_cmdtype			check_builtin(t_param *param);
void				execute_builtin(t_data *data, t_cmd *cmd, t_cmdtype type);

#endif
