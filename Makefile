##ALIAS##
NAME	= minishell
CC		= gcc
SRC		= main.c

##RULES##
all : 
	$(CC) -o $(NAME) $(SRC)

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME)
