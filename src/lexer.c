#include "minishell.h"

typedef struct s_lexer
{
    int         index;
	int         start;
	t_state     state;
	char        quote_char;
	int         separated_by_space;
}						t_lexer;


static int	is_special_char(char c)
{
    if (c == '|' || c == '>' || c == '<')
    {
        return (1);   
    }
	return (0);
}

static char	*create_token(char *str, int start, int end)
{
	return (ft_substr(str, start, end - start));
}
void str_in_initial_state(char *str, int i, t_lexer *vars)
{
    if (ft_isspace(str[i]))
    {
        vars->state = IN_WHITESPACE;
        vars->separated_by_space = 1;
    }
    else if (is_special_char(str[i]))
        vars->state = IN_SPECIAL;
    else if (str[i] == 34 || str[i] == 39)
    {
        vars->quote_char = str[i];
        vars->state = IN_QUOTE;
        vars->start = i;
    }
    else
    {
        vars->state = IN_WORD;
        vars->start = i;
    }
}

void in_whitespace_state(char *str, int *i, t_lexer *vars)
{
    while (ft_isspace(str[*i]))
        *i += 1;
    vars->state = INITIAL;
    *i -= 1;
}

void in_special_state(char *str, t_list **lst, t_lexer *vars, int *i)
{
    if (str[*i] == '|')
        ft_lstaddback(lst, ft_lstnew_2(ft_strdup("|"), PIPE, vars->separated_by_space));
    else if (str[*i] == '>' && str[*i + 1] == '>')
    {
        ft_lstaddback(lst, ft_lstnew_2(ft_strdup(">>"), APPEND, vars->separated_by_space));
        *i += 1;
    }
    else if (str[*i] == '<' && str[*i + 1] == '<')
    {
        ft_lstaddback(lst, ft_lstnew_2(ft_strdup("<<"), HEREDOC, vars->separated_by_space));
        *i += 1;
    }
    else if (str[*i] == '>')
        ft_lstaddback(lst, ft_lstnew_2(ft_strdup(">"), OUTRED, vars->separated_by_space));
    else if (str[*i] == '<')
        ft_lstaddback(lst, ft_lstnew_2(ft_strdup("<"), INRED, vars->separated_by_space));
    vars->state = INITIAL;
    vars->separated_by_space = 0;
}
void in_word_state(char *str, t_list **lst, t_lexer *vars, int *i)
{
    while (str[*i] != '\0' && !is_special_char(str[*i]) && !ft_isspace(str[*i]) && str[*i] != 34 && str[*i] != 39)
        *i += 1;
    ft_lstaddback(lst, ft_lstnew_2(create_token(str, vars->start, *i), WORD, vars->separated_by_space));
    vars->separated_by_space = 0;
}

int quote_found(char *str, t_lexer *vars, int *i)
{
    if (str[*i] == 34 || str[*i] == 39)
    {
        vars->quote_char = str[*i];
        vars->state = IN_QUOTE;
        vars->start = *i;
        return (1);
    }
    return (0);
}

int special_char_found(char c, t_lexer *vars)
{
    if (is_special_char(c))
    {
        vars->state = IN_SPECIAL;
        return (1);
    }
    return (0);
}

void    in_quote_state(char *str, t_list **lst, t_lexer *vars, int *i)
{
    *i += 1;
    while (str[*i] != '\0' && str[*i] != vars->quote_char)
        *i += 1;
    if (str[*i] == vars->quote_char)
        *i += 1;
    ft_lstaddback(lst, ft_lstnew_2(create_token(str, vars->start, *i), WORD, vars->separated_by_space));
    vars->separated_by_space = 0;
}
void    state_checks(char *str, t_list **lst, t_lexer *vars, int *i)
{
    if (vars->state == INITIAL)
        str_in_initial_state(str, *i, vars);
    if (vars->state == IN_WHITESPACE)
        in_whitespace_state(str, i, vars);
    if (vars->state == IN_SPECIAL)
        in_special_state(str, lst, vars, i); 
}
void    state_machine_lex(char *str, t_list **lst, t_lexer *vars, int *i)
{
    while (str[*i] != '\0')
    {
        state_checks(str, lst, vars, i);
        if (vars->state == IN_WORD || vars->state == IN_QUOTE)
        {
            if (vars->state == IN_WORD)
            {
                in_word_state(str, lst, vars, i);
                if (quote_found(str, vars, i) || special_char_found(str[*i], vars))
                    continue ;
                vars->state = INITIAL;
                *i -= 1;
            }
            else if (vars->state == IN_QUOTE)
            {
                in_quote_state(str, lst, vars, i);         
                if (special_char_found(str[*i], vars))
                    continue ;
                vars->state = INITIAL;
                *i -= 1;
            }
        }
        *i += 1;
    }
}
void    initialise_lexer_vars(t_lexer *vars)
{
    vars->start = 0;
    vars->state = INITIAL;
	vars->separated_by_space = 0;
}

void	lexer(char *str, t_list **lst)
{
	int i;
    t_lexer vars;

    i = 0;
    initialise_lexer_vars(&vars);
    state_machine_lex(str, lst, &vars, &i);
}
