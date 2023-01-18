/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:43 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/18 15:39:40 by mstockli         ###   ########.fr       */
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
	char			quote_type;
	int				pos;
	int				index;

	struct s_shell	*next;
}			t_shell;

typedef struct s_vars
{
	char			*env_shell;
}					t_vars;

char	*ft_parsing_sh(char *const *envp);
t_shell	*parsing_not_quotation(t_shell **shell);
void	split_not_quotation(t_shell **shell, char *input);
int		parsing_input(t_shell **shell, char *input);
char	*parse_quotation(char *input, int index, int size);

void	ft_lstadd_back(t_shell **lst, char *input);
int		free_lst(t_shell *lst);
int		ft_lstsize(t_shell **lst);

size_t	ft_strlen(const char *str);
int		ft_strcmp(char *input, char *str);

/* TO BE REMOVED */
void	printed(t_shell **a);

#endif
