##-----ALIAS-----##

NAME	= minishell
CC		= gcc
RM		= rm -rf
FLAGS	= -Werror -Wextra -Wall
LIBS	= -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline -I $(HOME)/.brew/Cellar/readline/8.2.1/include/readline

##-----VARIABLES-----##
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
			ft_control_tower.c \
			ft_parsing_shell.c \
			ft_parsing_input.c \
			ft_parsing_regroup.c \
			ft_utils.c \
			ft_lsts.c \
			ft_free_lsts.c \
			ft_verifs.c \
			ft_dollars.c \
			ft_pipex.c \
			ft_redirections.c \
			ft_check.c \
			ft_parsing_paths.c \
			ft_builtins.c \
			ft_unset.c \
			ft_export.c \
			ft_parsing_redop.c \
			ft_signals.c

HEAD	=	minishell.h


##-----SOURCES-----##

SRCS	= $(addprefix $(PATH_SRC),$(SRC))
OBJS	= $(addprefix $(PATH_OBJ),$(SRC:.c=.o))
HEADERS = $(addprefix $(PATH_HEAD),$(HEAD))

##-----RULES-----##

all:						$(NAME)

$(NAME):					$(OBJS) $(HEADERS)
							$(CC)  -I $(PATH_HEAD) -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline -lhistory -o $(@) $(OBJS)

$(PATH_OBJ)%.o:				$(PATH_SRC)%.c
							$(CC)  -c -I $(PATH_HEAD) -I $(HOME)/.brew/Cellar/readline/8.2.1/include/ -o $@ $<

clean:
							$(RM) $(PATH_OBJ)*.o

fclean:						clean
							$(RM) $(NAME)

re:							fclean all

.PHONY:						all fclean clean re

#-----ASCII ART SISI LE S-----#
asciiart:
	@echo "$(RED)                                                                            										"
	@echo "                                                                                     									"
	@echo "                                                                                     									"
	@echo "		███╗   ███╗██╗███╗   ██╗██╗██████╗  ██████╗  ██████╗██╗  ██╗███████╗██╗     ██╗     ███████╗    						"
	@echo "		████╗ ████║██║████╗  ██║██║██╔══██╗██╔═══██╗██╔════╝██║  ██║██╔════╝██║     ██║     ██╔════╝    						"
	@echo "		██╔████╔██║██║██╔██╗ ██║██║██████╔╝██║   ██║██║     ███████║█████╗  ██║     ██║     █████╗      						"
	@echo "		██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗██║   ██║██║     ██╔══██║██╔══╝  ██║     ██║     ██╔══╝      						"
	@echo "		██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║╚██████╔╝╚██████╗██║  ██║███████╗███████╗███████╗███████╗    						"
	@echo "		╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚══════╝    						"
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
