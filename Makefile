NAME = minishell

SRC = ./src/main.c

CC = cc
CFLAGS = -Wall -Wextra -Werror 
OBJ = $(SRC:.c=.o)

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