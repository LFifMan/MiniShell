/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:43 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/18 17:59:09 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define DOUBLEQUOTE 34
# define SINGLEQUOTE 39
# define SPACE 32

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char			*data;
	int				index;
	struct s_shell	*next;
}			t_shell;

typedef struct s_vars
{
	char			*env_shell;
	char			*env_pwd;
	char			**envp;
}					t_vars;

typedef struct s_tabs
{
	char			**cmds;
	char			**paths;
	struct s_tabs	*next;
}					t_tabs;


/* PARSING_SHELL.C */

char	*ft_parsing_sh(char *const *envp);
char	*ft_parsing_pwd(char *const *envp);


/* PARSING_INPUT.C */

t_shell	*parsing_not_quotation(t_shell **shell);
void	split_not_quotation(t_shell **shell, char *input);
int		parsing_input(t_shell **shell, char *input);
char	*parse_quotation(char *input, char index, int size, int i);


/* LSTS.C */

void	ft_lstadd_back(t_shell **lst, char *input);
int		free_lst(t_shell *lst);
int		ft_lstsize(t_shell **lst);


/* UTILS.C */

size_t	ft_strlen(const char *str);
int		ft_strcmp(char *input, char *str);
int		ft_memcmp(void *s1, void *s2, size_t n);


/* TO BE REMOVED */

void	ft_print_lst(t_shell **a);

#endif
