NAME = minishell

SRC = ./src/main.c \
		./src/lexer.c \
		./src/syntax.c \
		./src/env.c \
		./src/echo.c \
		./utils/linked_list/ft_lstnew.c \
		./utils/linked_list/ft_lstaddback.c \
		./utils/linked_list/ft_lstaddfront.c \
		./utils/linked_list/ft_lstsize.c \
		./utils/linked_list/ft_lstmax.c \
		./utils/linked_list/ft_lstmin.c \
		./utils/linked_list/ft_lstdisplay.c \
		./utils/linked_list/ft_lstclear.c \
		./utils/linked_list/ft_env_new.c \
		./utils/linked_list/ft_env_clear.c \
		./utils/linked_list/ft_env_addback.c \
		./utils/linked_list/ft_cmd_new.c \
		./utils/libft/ft_strdup.c \
		./utils/libft/ft_strncmp.c \
		./utils/libft/ft_substr.c \
		./utils/libft/ft_isspace.c \
		./utils/libft/ft_strlen.c \
		./utils/libft/ft_strchr.c \
		./utils/libft/ft_putstr_fd.c \
		./utils/libft/ft_putchar_fd.c \
		./utils/libft/ft_ssplit.c 

CC = cc $(INC)
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
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

.SECONDARY: $(OBJ)
