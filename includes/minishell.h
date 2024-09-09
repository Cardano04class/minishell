#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

/*--------shell---------*/
void				lexer(char *str, t_list **lst);
void				syntax_error(t_list *list);

////////////////////..LINKED LIST FUNCTIONS../////////////////////
t_list				*ft_lstnew(char *content, t_token type);
t_env				*ft_env_new(char *key, char *value);
void				ft_env_addback(t_env **lst, t_env *new);
t_list				*ft_lstmax(t_list *stack_a);
t_list				*ft_lstmin(t_list *stack_a);
void				ft_lstaddfront(t_list **lst, t_list *new);
void				ft_lstaddback(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
void				ft_lstdisplay(t_list *stack);
void				ft_lstclear(t_list **lst);

#endif