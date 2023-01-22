/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:43 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/22 20:56:53 by max              ###   ########.fr       */
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
# define GREATER 62
# define SMALLER 60
# define EQUAL 61

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

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
	char			**redop;
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
int		ft_check_allowed_char(char c, int pos);


/* PARSING_REGROUP.C */

t_tabs	*ft_regroup(t_shell **shell, t_vars *vars);
int		ft_lst_count_spaces(t_shell *lst);

t_shell	*ft_get_da_pipes(t_shell **shell);
void	ft_split_pipes(t_shell **shell, char *input);
char	*ft_trim_quotations(char *str);


/* PARSING_REDIRECTIONS.C */

t_shell	*ft_redirections(t_shell **shell);
void	ft_split_redirections(t_shell **shell, char *input);
t_shell	*ft_space_redop(t_shell **shell);


/* PARSING_REDOP.C */

void	ft_parsing_redop(t_tabs **tabs);


/* CHECK.C */

int		ft_check_op(t_shell *shell);


/* PARSING_PATHS.C */

void	ft_parsing_paths(t_vars vars, t_tabs **tabs);
char	**ft_split_bin(char *s, char c, char *argv);
int		ft_countwords(char *s, char c);
char	*ft_mallocfill_bin(char **s, char c, char *argv, int beg);
char	**ft_parsing_binaries(char *const *envp, char *argv);


/* LSTS.C */

void	ft_lstadd_back(t_shell **lst, char *input);
int		free_lst(t_shell *lst);
int		free_lst_tabs(t_tabs *lst);
int		ft_lstsize(t_shell **lst);
void	ft_lstregroup_back(	t_tabs **tabs, t_shell *input);

/* FT_PIPEX.C */

void	ft_pipex(t_tabs *tabs, t_vars *vars);


/* FT_PIPEX.C */
int		ft_build_cd(t_tabs *tabs, t_vars *vars);
int		ft_build_echo(t_tabs *tabs, t_vars *vars);
int		ft_build_pwd(t_tabs *tabs, t_vars *vars);
int		ft_build_export(t_tabs *tabs, t_vars *vars);
int		ft_build_unset(t_tabs *tabs, t_vars *vars);
int		ft_build_env(t_tabs *tabs, t_vars *vars);
int	ft_builtins(t_tabs *tabs, t_vars *vars, char *cmd_one);

void	ft_unset_export(t_tabs *tabs, t_vars *vars, char *cmd_one);

/* UTILS.C */

size_t	ft_strlen(const char *str);
int		ft_strcmp(char *input, char *str);
int		ft_memcmp(void *s1, void *s2, size_t n);
char	*ft_zero(const char *s);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strdup(const char *src);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);


/* TO BE REMOVED */

void	PRINT_SHELL(t_shell **a);
void	PRINT_CMDS(t_tabs **a);
void	PRINT_PATHS(t_tabs **a);
void	PRINT_REDOP(t_tabs **tabs);

#endif
