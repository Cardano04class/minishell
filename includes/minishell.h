#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum	e_token
{
	CMD,
	INRED,
	OUTRED,
	APPEND,
	HEREDOC,
	PIPE
}	t_token;

typedef struct s_list
{
	char 			*content;
	t_token			type;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

////////////////////..LINKED LIST FUNCTIONS../////////////////////
t_list				*ft_lstnew(int content);
t_list				*ft_lstmax(t_list *stack_a);
t_list				*ft_lstmin(t_list *stack_a);
void				ft_lstaddfront(t_list **lst, t_list *new);
void				ft_lstaddback(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
void				ft_lstdisplay(t_list *stack);
void				ft_lstclear(t_list **lst);

#endif