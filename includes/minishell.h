/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:43 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/03 16:39:28 by mstockli         ###   ########.fr       */
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
# define GREAT 62
# define SMALL 60
# define EQUAL 61
# define QUESTION 63

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_shell
{
	char			*data;
	int				index;
	struct s_shell	*next;
}			t_shell;

typedef struct s_vars
{
	char			**envp;
	char			**export;

	int				redir_in;
	int				redir_out;
	int				in_fd;
	int				out_fd;
	int				fd[2];
	pid_t			child;
	int				status;
	int				var;
	int				i;
	int				tmp_g;
	char 			*root;

}					t_vars;

typedef struct s_tabs
{
	char			**cmds;
	char			**paths;
	char			**redop;
	struct s_tabs	*next;
}					t_tabs;

int	g_status;

/* FT_SIGNALS.C */
void	ft_sigint_handler(int sig);
void	ft_block_signal(int sig);
void	ft_enable_signal(void);
void	ft_halt_signal(void);
void	ft_signals(int index);


/* FT_INIT_ONE.C */
char	*get_root_new(char **env);
void	ft_init_env(t_vars *vars, char **envp, int envp_length);
void	ft_init_vars(t_vars *vars, char **envp);


/* FT_INIT_TWO.C */
char	**ft_create_exp(int envp_length, char **input);
char	**ft_dup_exp(t_vars *vars, int envp_length);
void	ft_sort_exp(int envp_length, char **export);
char	*ft_shlvl(char *env);


/* FT_CTRL_TWR_ONE.C */
int		ft_ctrl_prs(t_shell **shell, t_vars *vars, char *input, t_tabs *tabs);
int		ft_ctrl_cmd(t_tabs **tabs, t_shell **shell, t_vars *vars);
void	ft_ctrl_twr(t_vars *vars);


/* FT_CTRL_TWR_TWO.C */
char	*ft_prompt(void);
int		ft_execution(t_tabs *tabs, t_vars *vars);


/* PARSING_INPUT.C */
t_shell	*parsing_spaces(t_shell **shell);
void	split_spaces(t_shell **shell, char *input);
int		parsing_quotations(t_shell **shell, char *input);
char	*parse_quotation(char *input, char index, int size, int i);


/* PARSING_DOLLARS.C */
int		ft_look_for_dollar(char *data);
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
int		check_var(char *str, t_vars *vars, int index);


/* CHECK.C */
int		ft_check_op(t_shell *shell);
int		check_only_spaces(char *input);


/* PARSING_PATHS.C */
void	ft_paths(t_vars vars, t_tabs **tabs);
char	**ft_split_bin(char *s, char c, char *argv);
int		ft_countwords(char *s, char c);
char	*ft_mallocfill_bin(char **s, char c, char *argv, int beg);
char	**ft_parsing_binaries(char *const *envp, char *argv);


/* FT_LSTS.C */
char	ft_add_index(char c);
char	*ft_add_data(char *input);
void	ft_lst_new(t_shell **lst, char *input, int index);
void	ft_lstregroup_back(	t_tabs **tabs, t_shell *input);


/* FT_FREE_LSTS.C */
int		ft_free_shell(t_shell *lst);
int		ft_free_tabs(t_tabs *lst);
void	ft_free_lst(t_shell *shell, t_tabs *tabs, char *input, int index);
void	ft_free_vars(t_vars vars);
void	ft_free_array(char **export, int envp_length);


/* FT_PIPEX.C */
void	ft_pipex(t_tabs *tabs, t_vars *vars);


/* FT_BUILTINS.C */
int		ft_build_cd(t_tabs *tabs, t_vars *vars, int print);
int		ft_build_echo(t_tabs *tabs, t_vars *vars);
int		ft_build_pwd(t_tabs *tabs, t_vars *vars);
int		ft_build_env(t_tabs *tabs, t_vars *vars);
int		ft_build_exit(char *input);
int		ft_builtins(t_tabs *tabs, t_vars *vars, char *cmd_one);


/* FT_BUILTINS_UTILS.C */
int		ft_option_n(char *str);
int		ft_find_dir(const char *path);
char	*ft_create_root(char *env, int j);
void	ft_update_pwd(t_vars *vars, char *root);
void	ft_cd_alone(char **env, int print, t_vars *vars);


/* FT_BUILTINS_UTILS_PWD.C */
void	ft_pwd_exp(t_vars *vars, char *path);
void	ft_pwd(t_vars *vars, char *path);
void	ft_old_pwd(t_vars *vars, int i);
void	ft_old_pwd_exp(t_vars *vars, int i);
int		ft_find_pwd(char **env);


/* FT_EXPORT.C */
int		ft_build_export(t_tabs *tabs, t_vars *vars, int print);


/* FT_UNSET.C */
void	ft_unset_export(t_tabs *tabs, t_vars *vars, char *cmd_one);
int		ft_build_unset(t_tabs *tabs, t_vars *vars, int print);


/* FT_WRITE.C */
void	ft_write(char *str, int option, int status);
int		ft_write_op(char *str, int status, int print);

/* UTILS1.C */
char	*ft_strcpy(char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int		ft_strcmp(char *input, char *str);
int		ft_memcmp(void *s1, void *s2, size_t n);
char	*ft_zero(const char *s);


/* UTILS2.C */
char	*ft_join(int index, char *s1, char *s2, char *dest);
char	*ft_join_exp(char *s1, char *s2, int index);
int		ft_strcmp_ascii(char *input, char *str);
char	*ft_strjoin(char *s1, char *s2, int index);
char	*ft_strdup(char *src, int index);


/* UTILS3.C */
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);


/* UTILS4.C */
char	*dest(int n, int count);
char	*ft_itoa(int n);
int		ft_atoi(char *str);
int		ft_is_whitespace(char *str);





/* TO BE REMOVED */
void	PRINT_SHELL(t_shell **a);
void	PRINT_CMDS(t_tabs **a);
void	PRINT_PATHS(t_tabs **a);
void	PRINT_REDOP(t_tabs **tabs);

#endif
