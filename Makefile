NAME = minishell

SRC = ./src/main.c \
		./utils/linked_list_functions/ft_lstnew.c \
		./utils/linked_list_functions/ft_lstaddback.c \
		./utils/linked_list_functions/ft_lstaddfront.c \
		./utils/linked_list_functions/ft_lstsize.c \
		./utils/linked_list_functions/ft_lstmax.c \
		./utils/linked_list_functions/ft_lstmin.c \
		./utils/linked_list_functions/ft_lstdisplay.c \
		./utils/linked_list_functions/ft_lstclear.c \

CC = cc $(INC)
CFLAGS = -Wall -Wextra -Werror 
OBJ = $(SRC:.c=.o)
INC = -I./includes/
all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
%.o:%.c
	$(CC) $(CFLAGS)  -c $< -o $@

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.SECONDARY: $(OBJ)