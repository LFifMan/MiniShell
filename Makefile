##-----ALIAS-----##

NAME	= minishell
CC		= gcc
RM		= rm -rf
FLAGS	= -Werror -Wextra -Wall -g3 -fsanitize=address
LIBS	= -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline -I $(HOME)/.brew/Cellar/readline/8.2.1/include/readline
MKDIR_P = mkdir -p

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
DIR_OBJ		= ./obj

##-----FILES-----##

SRC		=	main.c \
			ft_init_one.c \
			ft_init_two.c \
			ft_ctrl_twr_one.c \
			ft_ctrl_twr_two.c \
			ft_parsing_input.c \
			ft_parsing_regroup_one.c \
			ft_parsing_regroup_two.c \
			ft_utils_one.c \
			ft_utils_two.c \
			ft_utils_three.c \
			ft_utils_four.c \
			ft_lsts.c \
			ft_free_lsts_one.c \
			ft_free_lsts_two.c \
			ft_verifs.c \
			ft_dollar_one.c \
			ft_dollar_two.c \
			ft_dollar_three.c \
			ft_pipex.c \
			ft_redops_handler.c \
			ft_redirections.c \
			ft_check.c \
			ft_parsing_paths.c \
			ft_built.c \
			ft_built_utils_one.c \
			ft_built_utils_two.c \
			ft_built_pwd.c \
			ft_unset.c \
			ft_export_one.c \
			ft_export_two.c \
			ft_parsing_redop.c \
			ft_signals.c \
			ft_write.c

HEAD	=	minishell.h


##-----SOURCES-----##

SRCS	= $(addprefix $(PATH_SRC),$(SRC))
OBJS	= $(addprefix $(PATH_OBJ),$(SRC:.c=.o))
HEADERS = $(addprefix $(PATH_HEAD),$(HEAD))

##-----RULES-----##

all:						$(NAME) asciiart

$(NAME):					$(DIR_OBJ) $(OBJS) $(HEADERS)
							$(CC)  $(FLAGS) -I $(PATH_HEAD) -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline -lhistory -o $(@) $(OBJS)

$(PATH_OBJ)%.o:				$(PATH_SRC)%.c
							$(CC) $(FLAGS) -c -I $(PATH_HEAD) -I $(HOME)/.brew/Cellar/readline/8.2.1/include/ -o $@ $<

${DIR_OBJ} :
		@mkdir -p ${DIR_OBJ}
		
clean:
							$(RM) $(PATH_OBJ)*.o

run:						re
							./$(NAME)

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
