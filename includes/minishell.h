#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef enum e_state
{
	INITIAL,
	IN_WORD,
	IN_QUOTE,
	IN_SPECIAL,
	IN_WHITESPACE,
	STATE_DEFAULT,
	STATE_REDIRECTION,
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
	t_token				type;
	struct s_file		*next;
}						t_file;

typedef struct s_heredoc
{
	char				*delimiter;
	char				**content;
	struct s_heredoc	*next;

}						t_heredoc;

typedef struct s_cmd
{
	char				**cmd;
	t_file				*files;
	t_heredoc			*heredoc;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_global
{
	t_cmd				*command;
}						t_global;

extern t_global			g_mini;

typedef struct s_expander
{
	
}						t_expander;
/*--------shell---------*/
void					lexer(char *str, t_list **lst);
void					syntax_error(t_list *list);
void 					ft_env(char **env, t_env **env_lst);
int						echo(char **args);
void					cd(char **args);
void					pwd(void);
int 					export(char **args, t_env **lstvoid);
void					parser(t_list *lst);
int 					unset(char **args, t_env **env_list);
char 					**expand_var(t_env *env,char *line);

////////////////////..LINKED LIST FUNCTIONS../////////////////////
t_list					*ft_lstnew(char *content, t_token type);
t_env					*ft_env_new(char *key, char *value);
t_cmd					*ft_cmd_new(char **content);
t_file					*ft_file_new(char *filename, t_token type);
t_heredoc				*ft_heredoc_new(char *delimiter);
void					ft_env_clear(t_env **lst);
t_list					*ft_lstmax(t_list *stack_a);
t_list					*ft_lstmin(t_list *stack_a);
void					ft_lstaddfront(t_list **lst, t_list *new);
void					ft_lstaddback(t_list **lst, t_list *new);
void					ft_env_addback(t_env **lst, t_env *new);
void					ft_cmd_addback(t_cmd **command, t_cmd *new);
void					ft_file_addback(t_file *new);
void					ft_heredoc_addback(t_heredoc **heredoc, t_heredoc *new);
int						ft_lstsize(t_list *lst);
void					ft_lstdisplay(t_list *stack);
void					ft_lstclear(t_list **lst);

void 					print_env(t_env *env_lst);
t_env* 					env_exist(t_env **env_list, const char *name);
void 					print_export(t_env *env);
char 					*get_env(t_env *env, const char *name);


#endif

// add this :
// typedef struct s_cmd
// {
// 	char			**cmd;
// 	t_node			*input_fd;
// 	t_node			*output_fd;
// }					t_cmd;

// typedef struct s_node
// {
// 	int				data;
// 	struct s_node	*next;
// 	struct s_node	*prev;
// }					t_node;