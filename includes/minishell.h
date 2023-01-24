/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:43 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/24 15:09:25 by mstockli         ###   ########.fr       */
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
# include </Users/vfinocie/.brew/Cellar/readline/8.2.1/include/readline/readline.h>
# include </Users/vfinocie/.brew/Cellar/readline/8.2.1/include/readline/history.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>

typedef struct s_shell
{
	char			*data;
	int				index;
	struct s_shell	*next;
}			t_shell;

typedef struct s_vars
{
	char			**envp;

	int				input_redirection;
	int				output_redirection;

}					t_vars;

typedef struct s_tabs
{
	char			**cmds;
	char			**paths;
	char			**redop;
	struct s_tabs	*next;
}					t_tabs;


struct termios original_settings;


/* CONTROL_TOWER.C */
void	control_tower(t_vars *vars);
int		control_commands(t_tabs **tabs, t_shell **shell, t_vars *vars);
int		control_parsing(t_shell **shell, t_vars *vars, char *input);
char	*ft_prompt(char **input);

/* PARSING_SHELL.C */
char	*ft_parsing_sh(char *const *envp);
char	*ft_parsing_pwd(char *const *envp);

/* PARSING_INPUT.C */
t_shell	*parsing_spaces(t_shell **shell);
void	split_spaces(t_shell **shell, char *input);
int		parsing_quotations(t_shell **shell, char *input);
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
void	parsing_dollars(t_shell **shell, t_vars *vars);
int		ft_check_allowed_char(char c, int pos);

/* PARSING_REGROUP.C */
t_tabs	*ft_regroup(t_shell **shell, t_vars *vars);
int		ft_lst_count_spaces(t_shell *lst);
t_shell	*parsing_pipes(t_shell **shell);
void	ft_split_pipes(t_shell **shell, char *input);
char	*ft_trim_quotations(char *str);

/* PARSING_REDIRECTIONS.C */
t_shell	*parsing_redops(t_shell **shell);
void	ft_split_redirections(t_shell **shell, char *input);
t_shell	*ft_space_redops(t_shell **shell);

/* PARSING_REDOP.C */
void	ft_redops(t_tabs **tabs);
int		check_var(char *str);

/* CHECK.C */
int		ft_check_op(t_shell *shell);
int		check_only_spaces(char *input);

/* PARSING_PATHS.C */
void	ft_paths(t_vars vars, t_tabs **tabs);
char	**ft_split_bin(char *s, char c, char *argv);
int		ft_countwords(char *s, char c);
char	*ft_mallocfill_bin(char **s, char c, char *argv, int beg);
char	**ft_parsing_binaries(char *const *envp, char *argv);

/* LSTS.C */
void	ft_lstadd_back(t_shell **lst, char *input, int index);
int		ft_lstsize(t_shell **lst);
void	ft_lstregroup_back(	t_tabs **tabs, t_shell *input);

/* FT_FREE_LSTS.C */
int		free_shell(t_shell *lst);
int		free_tabs(t_tabs *lst);

/* FT_PIPEX.C */
void	ft_pipex(t_tabs *tabs, t_vars *vars);

/* FT_BUILTINS.C */
int		ft_build_cd(t_tabs *tabs, t_vars *vars);
int		ft_build_echo(t_tabs *tabs, t_vars *vars);
int		ft_build_pwd(t_tabs *tabs, t_vars *vars);
int		ft_build_env(t_tabs *tabs, t_vars *vars);
int		ft_builtins(t_tabs *tabs, t_vars *vars, char *cmd_one);

/* FT_EXPORT.C */
int		ft_build_export(t_tabs *tabs, t_vars *vars);

/* FT_UNSET.C */
void	ft_unset_export(t_tabs *tabs, t_vars *vars, char *cmd_one);
int		ft_build_unset(t_tabs *tabs, t_vars *vars);

/* UTILS.C */
size_t	ft_strlen(const char *str);
int		ft_strcmp(char *input, char *str);
int		ft_memcmp(void *s1, void *s2, size_t n);
char	*ft_zero(const char *s);
char	*ft_strjoin(char *s1, char *s2, int index);
char	*ft_strdup(char *src, int index);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *s1, const char *s2);


void	ft_signals(void);
void	disable_sigint_display(void);
void	restore_terminal_settings(void);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);


/* TO BE REMOVED */
void	PRINT_SHELL(t_shell **a);
void	PRINT_CMDS(t_tabs **a);
void	PRINT_PATHS(t_tabs **a);
void	PRINT_REDOP(t_tabs **tabs);

#endif
