##-----ALIAS-----##

NAME	= minishell
CC		= gcc
RM		= rm -rf
FLAGS	= -g -Werror -Wextra -Wall -I$(PATH_HEAD)
SAN		= -fsanitize=address

# Variables
COLOR			= \033
WHITE			= $(COLOR)[97m
CYAN			= $(COLOR)[96m
GREEN			= $(COLOR)[32m
BLUE			= $(COLOR)[34m
RED 			= $(COLOR)[31m
YELLOW			= $(COLOR)[33m
MAGENTA 		= $(COLOR)[35m
BOLD			= $(COLOR)[1m
RESET			= $(COLOR)[0m
RESET_BOLD		= $(COLOR)[21m

##-----PATHS-----##

PATH_SRC	= src/
PATH_HEAD	= includes/
PATH_OBJ	= obj/


##-----FILES-----##

SRC		=	main.c \
			parsingshell.c

HEAD	=	minishell.h


##-----SOURCES-----##

SRCS	= $(addprefix $(PATH_SRC),$(SRC))
OBJS	= $(addprefix $(PATH_OBJ),$(SRC:.c=.o))
HEADERS = $(addprefix $(PATH_HEAD),$(HEAD))

##RULES##

all:						asciiart $(NAME)

$(NAME):					$(OBJS) $(HEADERS)
							$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lreadline

$(PATH_OBJ)%.o:				$(PATH_SRC)%.c
							$(CC) $(FLAGS) -c $< -o $@

clean:
							$(RM) $(PATH_OBJ)*.o

fclean:						clean
							$(RM) $(NAME)

re:							fclean all

.PHONY:						all fclean clean re

# ASCII ART SISI LE S
asciiart:
	@echo "$(RED)                                                                            										"
	@echo "                                                                                     									"
	@echo "                                                                                     									"
	@echo "	███╗   ███╗██╗███╗   ██╗██╗██████╗  ██████╗  ██████╗██╗  ██╗███████╗██╗     ██╗     ███████╗    						"
	@echo "	████╗ ████║██║████╗  ██║██║██╔══██╗██╔═══██╗██╔════╝██║  ██║██╔════╝██║     ██║     ██╔════╝    						"
	@echo "	██╔████╔██║██║██╔██╗ ██║██║██████╔╝██║   ██║██║     ███████║█████╗  ██║     ██║     █████╗      						"
	@echo "	██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗██║   ██║██║     ██╔══██║██╔══╝  ██║     ██║     ██╔══╝      						"
	@echo "	██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║╚██████╔╝╚██████╗██║  ██║███████╗███████╗███████╗███████╗    						"
	@echo "	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚══════╝    						"
	@echo "$(BLUE)                                                                                       							"
	@echo "			██████╗ ██╗   ██╗    ██╗   ██╗███████╗██╗███╗   ██╗ ██████╗  ██████╗██╗███████╗                 				"
	@echo "			██╔══██╗╚██╗ ██╔╝    ██║   ██║██╔════╝██║████╗  ██║██╔═══██╗██╔════╝██║██╔════╝                 				"
	@echo "			██████╔╝ ╚████╔╝     ██║   ██║█████╗  ██║██╔██╗ ██║██║   ██║██║     ██║█████╗                   				"
	@echo "			██╔══██╗  ╚██╔╝      ╚██╗ ██╔╝██╔══╝  ██║██║╚██╗██║██║   ██║██║     ██║██╔══╝                   				"
	@echo "			██████╔╝   ██║        ╚████╔╝ ██║     ██║██║ ╚████║╚██████╔╝╚██████╗██║███████╗                 				"
	@echo "			╚═════╝    ╚═╝         ╚═══╝  ╚═╝     ╚═╝╚═╝  ╚═══╝ ╚═════╝  ╚═════╝╚═╝╚══════╝                 				"
	@echo "$(GREEN)                                                                                       							"
	@echo "			   ██╗       ███╗   ███╗███████╗████████╗ ██████╗  ██████╗██╗  ██╗██╗     ██╗                   				"
	@echo "			   ██║       ████╗ ████║██╔════╝╚══██╔══╝██╔═══██╗██╔════╝██║ ██╔╝██║     ██║                   				"
	@echo "			████████╗    ██╔████╔██║███████╗   ██║   ██║   ██║██║     █████╔╝ ██║     ██║                   				"
	@echo "			██╔═██╔═╝    ██║╚██╔╝██║╚════██║   ██║   ██║   ██║██║     ██╔═██╗ ██║     ██║                   				"
	@echo "			██████║      ██║ ╚═╝ ██║███████║   ██║   ╚██████╔╝╚██████╗██║  ██╗███████╗██║                   				"
	@echo "			╚═════╝      ╚═╝     ╚═╝╚══════╝   ╚═╝    ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝                   		$(RESET)"