/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:31:09 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 15:37:20 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sysexits.h>
# include <unistd.h>

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

typedef struct s_lexer
{
	int					start;
	t_state				state;
	char				quote_char;
	int					separated_by_space;
}						t_lexer;

typedef struct s_var
{
	int					i;
	int					j;
	int					status_len;
	int					in_single_quote;
	int					in_double_quote;
	int					name_len;
	int					expanded_len;
	char				*exit_status;
}						t_var;

typedef struct s_list
{
	char				*content;
	char				*non_var;
	t_token				type;
	struct s_list		*next;
	struct s_list		*prev;
	int					separated_by_space;
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

typedef struct s_parser
{
	int					cmd_arg_size;
	int					counter;
	t_state				state;
	t_cmd				*tmp_cmd;
}						t_parser;

typedef struct s_parse_state
{
	int					in_single_quote;
	int					in_double_quote;
	char				*result;
	int					last_exit_status;
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
typedef struct s_global
{
	char				**default_env;
	t_cmd				*command;
	int					sig_flag;
	int					exit_flag;
	int					exit_status;
	int					exit_pipe;
	t_env				*env;
	char				*last_cmd;
}						t_global;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

extern t_global			g_mini;
/*--------shell---------*/
void					init_var(t_var *var);
void					lexer(char *str, t_list **lst);
int						syntax_error(t_list *list);
void					parser(t_list *lst);
/*--------------Builtins----------*/
int						run_builtins(t_env **env, t_cmd *command);
int						echo(char **args);
void					cd(t_env **env, char **args);
void					pwd(t_env **env);
int						export(t_env **env_list, char **args);
int						unset(char **args, t_env **env_list);
void					ft_env(char **env, t_env **env_lst);
t_env					*create_env(t_env **env_list);
void					ft_exit(t_cmd *data);
/*-------------Exit-----------*/
int						is_valid_numeric_arg(const char *arg);
int						is_last_command(t_cmd *current);
void					handle_exit_error(char *arg);
void					handle_too_many_arguments(void);
void					exit_with_status(int status);
int						is_overflow(const char *num_start, const char *limit);
const char					*skip_leading(const char *arg, int *sign);
int						check_overflow(const char *arg, int sign);
int						validate_chars(const char *arg, size_t *num_count);
/*-------------CD----------------*/
t_env					*find_env_var(t_env *env, const char *name);
void					update_env_var(t_env **env, const char *name,
							const char *value);
void					cd_home(char *home);
void					cd_oldpwd(t_env *oldpwd_env);
void					cd_path(const char *path);
/*------------------------------Echo----------------------------*/
bool					is_n_option(char *str);
int						print_argument(char *arg);
void					print_arguments_one_at_a_time(char **args, int i);
/*---------------Export_helpers-----------*/
void					print_export(t_env *env);
t_env					*create_env_node(const t_env *current);
t_env					*sort_env(const t_env *env_list);
t_env					*env_exist(t_env **env_list, const char *name);
t_env					*init_export_node(char *name);
t_env					*env_exist(t_env **env_list, const char *name);
int						set_node_value(t_env *new_node, char *value);
int						is_valid_name(char *str);
int						find_plus(char *str);
int						find_equals(char *str);
int						already_sorted(t_env *lst);
void					insert_sorted_node(t_env **sorted_list,
							t_env *new_node);
int						validate_and_handle(t_env **lst, char *var_name,
							char *var_value, int plus_sign);
int						handle_equal_sign(t_env **lst, char *str,
							int equal_sign, int plus_sign);
void					update_env(t_env **env_list, char *name, char *value,
							bool plus_sign);
t_env					*ft_export_node(t_env **env_env_list, char *name,
							char *value);
int						handle_existing_node(t_env **env_list, char *var_name,
							char *var_value, int plus_sign);
/*------------Expand-----------------*/
void					expand(t_env *env, t_list **list);
char					*remove_quotes_and_expand(t_env *env, char *content);
void					merge_export_assignment(t_list **list);
void					handle_dollar_case(t_var *var, char *content,
							t_env *env);
int						single_quotes_skip(char *content, int *i, t_var *var);
int						double_quotes_skip(char *content, int *i, t_var *var);
int						handle_quotes(t_var *var, char *content);
int						calculate_expand_length(char *content, t_env *env);
void					process_char(t_var *var);
void					name_length(char *content, int *i, t_env *env,
							t_var *var);
int						exit_status_len(char *content, t_var *var, int *i);
int						lone_dollar_case(char *content, t_var *var, int *i);
/*--------------Syntax_error-----------------*/
int						is_special(t_list *token);
t_error					create_error(t_error_type type, char *token);
t_error					check_quotes(char *str);
////////////////////..LINKED LIST FUNCTIONS../////////////////////
t_list					*ft_lstnew(char *content, t_token type);
t_list					*ft_lstnew_2(char *content, t_token type,
							int seperated_by_space);
t_env					*ft_env_new(char *key, char *value);
t_cmd					*ft_cmd_new(char **content);
t_file					*ft_file_new(char *filename, t_token type,
							char *delimiter);
void					ft_env_clear(t_env **lst);
t_list					*ft_lstmax(t_list *stack_a);
t_list					*ft_lstmin(t_list *stack_a);
void					ft_lstaddfront(t_list **lst, t_list *new);
void					ft_lstaddback(t_list **lst, t_list *new);
void					ft_env_addback(t_env **lst, t_env *new);
void					ft_cmd_addback(t_cmd **command, t_cmd *new);
void					ft_file_addback(t_file *new);
int						ft_lstsize(t_list *lst);
int						ft_envsize(t_env *env);
void					ft_lstdisplay(t_list *stack);
void					ft_lstclear(t_list **lst);

int						print_env(t_env *env_lst);
char					*get_env(t_env *env, const char *name);

char					*heredoc_expand(t_env *env, char *content);
char					*expand_variable(t_env *env, const char *var_name);
bool					set_redirections(t_file *file);
void					run_heredoc(t_cmd *command);
int						execution(t_cmd *cmd);
void					signal_handler(int sig);
void					handle_sigint(int signum);
char					*heredoc_filename(void);

int						capture_exit_status(int status);
void					*_malloc(size_t size, char op);
t_env					*set_env_var(t_env *env, char *key, char *value);

/*-------------------Lexer--------------------*/
void					in_initial_state(char *str, int i, t_lexer *vars);
void					in_whitespace_state(char *str, int *i, t_lexer *vars);
void					in_special_state(char *str, t_list **lst, t_lexer *vars,
							int *i);
void					in_word_state(char *str, t_list **lst, t_lexer *vars,
							int *i);
void					in_quote_state(char *str, t_list **lst, t_lexer *vars,
							int *i);
char					*create_token(char *str, int start, int end);
int						is_special_char(char c);
int						quote_found(char *str, t_lexer *vars, int *i);
int						special_char_found(char c, t_lexer *vars);
void					state_checks(char *str, t_list **lst, t_lexer *vars,
							int *i);
void					state_machine_lex(char *str, t_list **lst,
							t_lexer *vars, int *i);
void					initialise_lexer_vars(t_lexer *vars);
void					lexer(char *str, t_list **lst);

/*-----------------Execution------------------*/
char					*ft_getenv(char *name, t_env *env);
t_env					*ft_dashcase(char *name);
char					*find_path(char *cmd, t_env *env);
char					**convert_env(t_env *list_env);
bool					set_redirections(t_file *file);
void					if_executable(char *str);
int						execute_without_path(t_cmd *command);
int						execute_with_path(t_cmd *command);
int						run_command(t_cmd *command);
int						run_builtins(t_env **env, t_cmd *command);
int						execute_command(t_cmd *command);
int						first_child(pid_t *pid, t_cmd *command, int *fd);
int						second_child(pid_t *pid, t_cmd *command, int *fd);
int						execute_pipe(t_cmd *command);
void					check_if_cmd_valid(t_cmd *command);
int						execution(t_cmd *command);
int						is_builtins(t_cmd *command);

/*------------run_heredoc---------------*/

char					*heredoc_filename(void);
char					*find_var_value(t_env *env, const char *var_name);
int						char_is_null(char i_content, int *expanded_len);
int						char_is_exit_holder(char i_content, int *expanded_len,
							int *i);
int						get_var_name_length(char *content, int *i);
int						get_var_value_length(char *content, int name_len,
							int i);
int						calculate_var_expansion_length(char *content);
int						char_is_null_fill(char i_content,
							char **expanded_content, int *j);
int						char_is_exit_holder_fill(char i_content,
							char **expanded_content, int *i, int *j);
char					*get_var_value(char *content, int name_len, int i);
void					fill_expanded_content(char *var_value,
							char **expanded_content, int *j);
char					*copy_expanded_content(char *content, int expanded_len);
char					*expand_in_heredoc(char *content);
void					write_line_fd(char *line, int fd);
int						heredoc_prompt(t_cmd *command, int fd);
void					run_heredoc(t_cmd *command);

/*--------------------parsing----------------*/

char					*heredoc_filename(void);
int						cmd_argument_size(t_list *lst);
void					create_heredoc_file(t_list *lst);
void					create_in_out_file(t_list *lst);
void					process_command_arguments(t_list *lst, t_parser *vars);
void					handle_word_token(t_parser *vars, t_list *lst);
void					create_next_command_tokens(t_parser *vars, t_list *lst);
void					intialise_vars(t_parser *vars, t_list *lst);
void					parser(t_list *lst);
long	ft_atol(char *str);
#endif