NAME = minishell

SRC = ./src/main.c \
		./src/lexer/lexer.c \
		./src/lexer/lexer_machine_states.c \
		./src/lexer/lexer_utils.c \
		./src/syntax_error/syntax.c \
		./src/syntax_error/syntax_1.c \
		./src/expand/expand.c \
		./src/expand/calculation_1.c \
		./src/expand/calculation_2.c \
		./src/expand/merge_export.c \
		./src/expand/remove_quotes.c \
		./src/parsing/parser.c \
		./src/parsing/word_and_red_token_parsing.c \
		./src/parsing/pipe_token_parsing.c \
		./src/execution/pipeline_execution.c \
		./src/execution/command_execution.c \
		./src/execution/cmd_path_utils.c \
		./src/execution/execution_utils.c \
		./src/builtins/env/env.c \
		./src/builtins/env/env_1.c \
		./src/builtins/echo/echo.c \
		./src/builtins/echo/echo_1.c \
		./src/builtins/cd/cd.c \
		./src/builtins/cd/cd_functions.c \
		./src/builtins/exit/exit.c \
		./src/builtins/exit/exit_1.c \
		./src/builtins/exit/exit_2.c \
		./src/builtins/export/export.c \
		./src/builtins/export/export_1.c \
		./src/builtins/export/export_2.c \
		./src/builtins/export/export_3.c \
		./src/builtins/unset.c \
		./src/heredoc/run_heredoc.c \
		./src/heredoc/heredoc_expand.c \
		./src/heredoc/heredoc_expand_content_fill.c \
		./src/heredoc/heredoc_expand_content_copy.c \
		./src/heredoc/heredoc_expand_var_utils.c \
		./utils/signal_handler.c \
		./utils/exit_handler.c \
		./utils/garbage.c\
		./utils/linked_list/ft_lstaddback.c \
		./utils/linked_list/ft_env_addback.c \
		./utils/linked_list/ft_cmd_addback.c \
		./utils/linked_list/ft_file_addback.c \
		./utils/linked_list/ft_lstaddfront.c \
		./utils/linked_list/ft_lstsize.c \
		./utils/linked_list/ft_envsize.c \
		./utils/linked_list/ft_lstmax.c \
		./utils/linked_list/ft_lstmin.c \
		./utils/linked_list/ft_lstdisplay.c \
		./utils/linked_list/ft_lstclear.c \
		./utils/linked_list/ft_env_clear.c \
		./utils/linked_list/ft_lstnew.c \
		./utils/linked_list/ft_env_new.c \
		./utils/linked_list/ft_cmd_new.c \
		./utils/linked_list/ft_file_new.c \
		./utils/libft/ft_strdup.c \
		./utils/libft/ft_strlcat.c \
		./utils/libft/ft_strlcpy.c \
		./utils/libft/ft_strncpy.c \
		./utils/libft/ft_split.c \
		./utils/libft/ft_strncmp.c \
		./utils/libft/ft_strcmp.c \
		./utils/libft/ft_strcat.c \
		./utils/libft/ft_strcpy.c \
		./utils/libft/ft_strnstr.c \
		./utils/libft/ft_strtrim.c \
		./utils/libft/ft_substr.c \
		./utils/libft/ft_isspace.c \
		./utils/libft/ft_strlen.c \
		./utils/libft/ft_strchr.c \
		./utils/libft/ft_putstr_fd.c \
		./utils/libft/ft_putchar_fd.c \
		./utils/libft/ft_ssplit.c \
		./utils/libft/ft_isalnum.c \
		./utils/libft/ft_isalpha.c \
		./utils/libft/ft_strjoin.c \
		./utils/libft/ft_memcpy.c \
		./utils/libft/ft_calloc.c \
		./utils/libft/ft_bzero.c \
		./utils/libft/ft_memmove.c \
		./utils/libft/ft_memset.c \
		./utils/libft/ft_atoi.c \
		./utils/libft/ft_atol.c \
		./utils/libft/ft_itoa.c \
		./utils/libft/ft_isdigit.c \

CC = cc $(INC)
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
OBJ = $(SRC:.c=.o)
INC = -I./includes/

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

.o:.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

sup:
	valgrind --suppressions=readline.supp --show-leak-kinds=reachable --track-fds=yes ./minishell

.SECONDARY: $(OBJ)
