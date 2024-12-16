#include "minishell.h"

static int	is_special_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

static char	*create_token(char *str, int start, int end)
{
	return (ft_substr(str, start, end - start));
}

void	lexer(char *str, t_list **lst)
{
	int i;
	int start;
	t_state state;
	char quote_char;
	int separated_by_space = 0;

    i = 0;
    start = 0;
    state = INITIAL;
    while (str[i] != '\0')
    {
        if (state == INITIAL)
        {
            if (ft_isspace(str[i]))
            {
                state = IN_WHITESPACE;
                separated_by_space = 1;
            }
            else if (is_special_char(str[i]))
                state = IN_SPECIAL;
            else if (str[i] == 34 || str[i] == 39)
            {
                quote_char = str[i];
                state = IN_QUOTE;
                start = i;
            }
            else
            {
                state = IN_WORD;
                start = i;
            }
        }
        if (state == IN_WHITESPACE)
        {
            while (ft_isspace(str[i]))
                i++;
            state = INITIAL;
            --i;
        }
        else if (state == IN_SPECIAL)
        {
            if (str[i] == '|')
			    ft_lstaddback(lst, ft_lstnew_2(ft_strdup("|"), PIPE, separated_by_space));
            else if (str[i] == '>' && str[i + 1] == '>')
            {
                ft_lstaddback(lst, ft_lstnew_2(ft_strdup(">>"), APPEND, separated_by_space));
                i++;
            }
            else if (str[i] == '<' && str[i + 1] == '<')
            {
                ft_lstaddback(lst, ft_lstnew_2(ft_strdup("<<"), HEREDOC, separated_by_space));
                i++;
            }
            else if (str[i] == '>')
			    ft_lstaddback(lst, ft_lstnew_2(ft_strdup(">"), OUTRED, separated_by_space));
            else if (str[i] == '<')
			    ft_lstaddback(lst, ft_lstnew_2(ft_strdup("<"), INRED, separated_by_space));
            state = INITIAL;
            separated_by_space = 0;
        }
        else if (state == IN_WORD || state == IN_QUOTE)
        {
            if (state == IN_WORD)
            {
                while (str[i] != '\0' && !is_special_char(str[i]) && !ft_isspace(str[i]) && str[i] != 34 && str[i] != 39)
                    i++;
                ft_lstaddback(lst, ft_lstnew_2(create_token(str, start, i), WORD, separated_by_space));
                separated_by_space = 0;
                
                if (str[i] == 34 || str[i] == 39)
                {
                    quote_char = str[i];
                    state = IN_QUOTE;
                    start = i;
                    continue ;
                }
                else if (is_special_char(str[i]))
                {
                    state = IN_SPECIAL;
                    continue ;
                }
                state = INITIAL;
                --i;
            }
            else if (state == IN_QUOTE)
            {
                i++;
                while (str[i] != '\0' && str[i] != quote_char)
                    i++;
                if (str[i] == quote_char)
                    i++;
                
                ft_lstaddback(lst, ft_lstnew_2(create_token(str, start, i), WORD, separated_by_space));
                separated_by_space = 0;                
                if (is_special_char(str[i]))
                {
                    state = IN_SPECIAL;
                    continue ;
                }
                state = INITIAL;
                --i;
            }
        }
        i++;
    }
}


