#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <sysexits.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_token
{
	WORD,
	INRED,
	OUTRED,
	APPEND,
	HEREDOC,
	PIPE
}					t_token;

typedef enum e_state
{
	INITIAL,
	IN_WORD,
	IN_QUOTE,
	IN_SPECIAL,
	IN_WHITESPACE
}					t_state;

typedef struct s_list
{
	char			*content;
	t_token			type;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			**content;
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
}					t_cmd;

/*--------shell---------*/
void 		lexer(char *str, t_list **lst);
void 		syntax_error(t_list *list);
void		ft_env(char **env);
int 		echo(char **args);
void 		cd(char **args);
void 		print_working_directory();
////////////////////..LINKED LIST FUNCTIONS../////////////////////
t_list				*ft_lstnew(char *content, t_token type);
t_env				*ft_env_new(char *key, char *value);
t_cmd				*ft_cmd_new(char **content);
void				ft_env_addback(t_env **lst, t_env *new);
void 				ft_env_clear(t_env **lst);
t_list				*ft_lstmax(t_list *stack_a);
t_list				*ft_lstmin(t_list *stack_a);
void				ft_lstaddfront(t_list **lst, t_list *new);
void				ft_lstaddback(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
void				ft_lstdisplay(t_list *stack);
void				ft_lstclear(t_list **lst);

#endif