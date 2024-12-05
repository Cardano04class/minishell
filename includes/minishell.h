# ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1024

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sysexits.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>


typedef enum e_token
{
	WORD,
	INRED,
	OUTRED,
	APPEND,
	HEREDOC,
	PIPE
}						t_token;

typedef enum e_sig
{
	IN_CHILD,
	IN_HEREDOC,
	IN_PARENT,
	IN_PROMPT
}						t_sig;

typedef enum e_state
{
	INITIAL,
	IN_WORD,
	IN_QUOTE,
	IN_SPECIAL,
	IN_WHITESPACE,
	STATE_DEFAULT,
	STATE_REDIRECTION,
	STATE_HEREDOC,
	STATE_PIPE
}						t_state;

typedef struct s_list
{
	char				*content;
	t_token				type;
	struct s_list		*next;
	struct s_list		*prev;
}						t_list;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_file
{
	char				*filename;
	char				*delimiter;
	t_token				type;
	struct s_file		*next;
}						t_file;

typedef struct s_cmd
{
	char				**cmd;
	t_file				*files;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_global
{
	t_cmd				*command;
	int					sig_flag;
	int					heredoc_fd;
}						t_global;

extern t_global			g_mini;

typedef struct s_parse_state
{
	int					in_single_quote;
	int					in_double_quote;
	char				*result;
	size_t				result_size;
	size_t				result_idx;
	char				*line;
	size_t				i;
	t_env				*env;
}						t_parse_state;

typedef struct s_quote_state
{
	char				*str;
	size_t				i;
	size_t				j;
	char				*result;
	int					in_single;
	int					in_double;
}						t_quote_state;

typedef enum e_error_type
{
	NO_ERROR,
	UNCLOSED_QUOTES,
	INVALID_POSITION,
	CONSECUTIVE_SPECIAL,
	PIPE_AT_START,
	MISSING_CONTEXT
}						t_error_type;

typedef struct s_error
{
	t_error_type		type;
	char				*token;
}						t_error;

/*--------shell---------*/
void 					debug_list(t_list *list);
void					lexer(char *str, t_list **lst);
void 					free_array(char **array);
int						syntax_error(t_list *list);
t_error					create_error(t_error_type type, char *token);
void					print_error(t_error error);
void					parser(t_list *lst);
/*--------------Builtins----------*/
int 					run_builtins(t_env **env);
int						echo(char **args);
void					cd(t_env **env,char **args);
void					pwd(t_env **env);
int						export(t_env **env_list, char **args);
int						unset(char **args, t_env **env_list);
void					ft_env(char **env, t_env **env_lst);
int 					exit_shell(t_cmd *arg);
/*-------------CD_functions----------------*/
t_env					*find_env_var(t_env *env, const char *name);
void					update_env_var(t_env **env, const char *name,
							const char *value);
void					cd_home(char *home);
void					cd_oldpwd(t_env *oldpwd_env);
void					cd_path(const char *path);
/*---------------Export_helpers-----------*/
int						find_equals(char *str);
int						is_valid_name(char *str);
int						find_plus(char *str);
t_env					*sort_env(const t_env *env_list);
t_env					*create_env_node(const t_env *current);
t_env					*env_exist(t_env **env_list, const char *name);
void					update_env(t_env **env_list, char *name, char *value,
							bool plus_sign);
t_env					*init_export_node(char *name);
int						set_node_value(t_env *new_node, char *value);
void					insert_sorted_node(t_env **sorted_list,
							t_env *new_node);
int						handle_equal_sign(t_env **lst, char *str,
							int equal_sign, int plus_sign);
int						validate_and_handle(t_env **lst, char *var_name,
							char *var_value, int plus_sign);
int						handle_existing_node(t_env **lst, char *var_name,
							char *var_value, int plus_sign);
/*------------Expand-----------------*/
void					expand(t_env *env, t_list **list);
char					*expand_variables(t_env *env, char *line);
char					*remove_quotes(char *str);
char					*merge_args(char *arg1, char *arg2);
////////////////////..LINKED LIST FUNCTIONS../////////////////////
t_list					*ft_lstnew(char *content, t_token type);
t_env					*ft_env_new(char *key, char *value);
t_cmd					*ft_cmd_new(char **content);
t_file					*ft_file_new(char *filename, t_token type, char *delimiter);
//t_heredoc				*ft_heredoc_new(char *delimiter);
void					ft_env_clear(t_env **lst);
t_list					*ft_lstmax(t_list *stack_a);
t_list					*ft_lstmin(t_list *stack_a);
void					ft_lstaddfront(t_list **lst, t_list *new);
void					ft_lstaddback(t_list **lst, t_list *new);
void					ft_env_addback(t_env **lst, t_env *new);
void					ft_cmd_addback(t_cmd **command, t_cmd *new);
void					ft_file_addback(t_file *new);
//void					ft_heredoc_addback(t_heredoc *new);
int						ft_lstsize(t_list *lst);
int						ft_envsize(t_env *env);
void					ft_lstdisplay(t_list *stack);
void					ft_lstclear(t_list **lst);

int					print_env(t_env *env_lst);
t_env					*env_exist(t_env **env_list, const char *name);
void					print_export(t_env *env);
char					*get_env(t_env *env, const char *name);

void    				run_cmd(t_cmd *command, t_env *env);
void 					run_heredoc(t_cmd	*command);
void					execute(t_cmd *command, t_env *list_env);
void 					signal_handler(int sig);
void					handle_sigint(int signum);
char					*heredoc_filename(void);
# endif