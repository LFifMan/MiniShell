/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:43 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/20 02:37:23 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define DOUBLEQUOTE 34
# define SINGLEQUOTE 39
# define SPACE 32
# define CHARS 0
# define DOLLAR 36
# define PIPE 124

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

/* PARSING_DOLLARS.C */
int		ft_look_for_dollar(char *data);
int		ft_find(char *data, char *envp);
int		ft_look_in_envp(char *data, char *envp);
int		ft_dollar_len(char *data, int start);
int		ft_env_len(char *envp, int start);
int		ft_size_malloc(char *data, char *envp, int start_data, int start_envp);
char	*ft_malloc_cpy(char *data, char *envp, int size);
char	*ft_replace(char *data, char *envp);
void	ft_dollars(t_shell **shell, t_vars *vars);

/* PARSING_REGROUP.C */

t_tabs	*ft_regroup(t_shell **shell, t_vars *vars);
int		ft_lst_count_spaces(t_shell *lst);

t_shell	*ft_get_da_pipes(t_shell **shell);
void	ft_split_pipes(t_shell **shell, char *input);
char	*ft_trim_quotations(char *str);


/* LSTS.C */

void	ft_lstadd_back(t_shell **lst, char *input);
int		free_lst(t_shell *lst);
int		ft_lstsize(t_shell **lst);
void	ft_lstregroup_back(	t_tabs **tabs, t_shell *input);


/* UTILS.C */

size_t	ft_strlen(const char *str);
int		ft_strcmp(char *input, char *str);
int		ft_memcmp(void *s1, void *s2, size_t n);
char	*ft_zero(const char *s);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strdup(const char *src);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);


/* TO BE REMOVED */

void	ft_print_lst(t_shell **a);
void	ft_print_lst_tabs(t_tabs **a);

#endif
