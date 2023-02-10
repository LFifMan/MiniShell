/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:43 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/10 16:49:23 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define DQ 34
# define SQ 39
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

typedef struct s_var
{
	char			**env;
	char			**exp;
	char			*home;

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
}					t_var;

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
void	ft_init_env(t_var *var, char **envp, int envp_length);
void	ft_init_var(t_var *var, char **envp);


/* FT_INIT_TWO.C */
char	**ft_create_exp(int envp_length, char **input);
char	**ft_dup_exp(t_var *var, int envp_length);
void	ft_sort_exp(int envp_length, char **export);
char	*ft_shlvl(char *env);


/* FT_CTRL_TWR_ONE.C */
int		ft_ctrl_prs(t_shell **shell, t_var *var, char *input, t_tabs *tabs);
int		ft_ctrl_cmd(t_tabs **tabs, t_shell **shell, t_var *var);
void	ft_ctrl_twr(t_var *var);


/* FT_CTRL_TWR_TWO.C */
char	*ft_prompt(void);
int		ft_execution(t_tabs *tabs, t_var *var);


/* PARSING_INPUT.C */
t_shell	*parsing_spaces(t_shell **shell);
void	split_spaces(t_shell **shell, char *input, int old_index);
int		parsing_quotations(t_shell **shell, char *input);
char	*parse_quotation(char *input, char index, int size, int i);


/* FT_DOLLAR_ONE.C */
char	*ft_replace_status(char *data, int status);
int		ft_look_for_status(char *data);
char	*ft_to_be_named(char **env, char *data, int status);
void	ft_pars_dollar(t_shell **shell, t_var *var);


/* FT_DOLLAR_TWO.C */
int		ft_size_malloc(char *data, char *env, int start_data, int start_env);
char	*ft_malloc_cpy(char *data, char *env, int size);
char	*ft_replace(char *data, char *env);
int		ft_iteration(char c);
char	*ft_remove_dollar(char *data);


/* FT_DOLLAR_THREE.C */
int		ft_look_for_dollar(char *data);
int		ft_check_allowed_char(char c, int pos);
int		ft_look_in_envp(char *data, char *env);
int		ft_dollar_len(char *data, int start);
int		ft_env_len(char *env, int start);


/* NEW DOLLAR*/
void	ft_pars_dollar2(t_tabs **tabs, t_var *var);
char	*ft_replace_dollar2(char **env, char *data, int status);
char	*ft_remove_dollar2(char *data, int start);
char	*ft_replace2(char *data, char *env, int data_i);
int		ft_look_in_envp2(char *data, char *env, int i);
char	*ft_replace_status2(char *data, int status, int place);
int		ft_get_dollar_place(char *data);
int		ft_look_for_dollar2(char *data);



/* PARSING_REGROUP_ONE.C */
char	*ft_trim_quotations(char *str);
int		ft_lst_count_spaces(t_shell *lst);
t_tabs	*ft_regroup(t_shell **shell, t_var *var);
void	ft_split_pipes(t_shell **shell, char *input);
//t_shell	*parsing_pipes(t_shell **shell);


/* PARSING_REGROUP_TWO.C */
void	ft_prepare_new(t_shell *new, t_shell *shell);
t_shell	*ft_create_new(void);
t_shell	*parsing_pipes(t_shell *shell);


/* PARSING_REDIRECTIONS.C */
t_shell	*parsing_redops(t_shell **shell);
void	ft_split_redirections(t_shell **shell, char *input);
t_shell	*ft_space_redops(t_shell **shell);


/* PARSING_REDOP.C */
int		ft_count_redops(char **cmd);
char	**ft_remove_redop_cmds(char **cmd, int index);
//int		ft_anommer_two(t_tabs *tmp, int i, int j);
void	ft_redops(t_tabs **tabs);


/* CHECK.C */
int		ft_check_op(t_shell *shell);
int		ft_check_spaces(char *input);


/* PARSING_PATHS.C */
void	ft_paths(t_var var, t_tabs **tabs);
char	**ft_split_bin(char *s, char c, char *argv);
int		ft_countwords(char *s, char c);
char	*ft_mallocfill_bin(char **s, char c, char *argv, int beg);
char	**ft_parsing_binaries(char *const *envp, char *argv);


/* FT_TRIM_QUOTES.C */
void	ft_trim_quotes(t_tabs **tabs);
char	*ft_trim_cmds(char *cmd, int size);
int		ft_trim_count(char *cmd);


/* FT_LSTS.C */
char	ft_add_index(char c, int index);
char	*ft_add_data(char *input);
void	ft_lst_new(t_shell **lst, char *input, int index, int old_index);
void	ft_lstregroup_back(	t_tabs **tabs, t_shell *input);


/* FT_FREE_LSTS_ONE.C */
int		ft_free_shell(t_shell *lst);
//void	ft_free(t_tabs *lst);
int		ft_free_tabs(t_tabs *lst);
void	ft_free_lst(t_shell *shell, t_tabs *tabs, char *input, int index);
void	ft_free_var(t_var var);


/* FT_FREE_LSTS_TWO.C */
void	ft_free_array(char **exp, int len_env);


/* FT_PIPEX.C */
void	ft_heredoc(t_tabs *tabs, t_var *var, int j);
void	ft_child(t_tabs *tabs, t_var *var);
void	ft_parent(t_tabs *tabs, t_var *var);
void	ft_process_execution(t_var *var, t_tabs *tabs);
void	ft_pipex(t_tabs *tabs, t_var *var);


/* FT_REDOPS_HANDLER.C */
void	ft_handle_heredoc(t_tabs *tabs, t_var *var, int i);
void	ft_handle_append_redir(t_tabs *tabs, t_var *var, int i);
void	ft_handle_input_redir(t_tabs *tabs, t_var *var, int i);
void	ft_handle_trunc_redir(t_tabs *tabs, t_var *var, int i);
void	ft_redops_handler(t_tabs *tabs, t_var *var);


/* FT_BUILT.C */
int		ft_build_echo(t_tabs *tabs, t_var *var);
int		ft_build_pwd(t_tabs *tabs, t_var *var);
int		ft_build_env(t_tabs *tabs, t_var *var);
int		ft_build_cd(t_tabs *tabs, t_var *var, int print);
int		ft_builtins(t_tabs *tabs, t_var *var, char *cmd_one);
char	*ft_str_lower(char *str);


/* FT_BUILTINS_UTILS.C */
int		ft_option_n(char *str);
int		ft_find_dir(const char *path);
char	*ft_create_root(char *env, int j);
void	ft_update_pwd(t_var *var, char *root);
void	ft_cd_alone(char **env, int print, t_var *var);

/* FT_BUILT_UTILS_TWO.c */
int		ft_build_exit(char *input);
void	ft_cd_absolute(t_tabs *tabs, t_var *var, int print);
void	ft_cd_relative(t_tabs *tabs, t_var *var, int print, char *current);
int		ft_find_home(char **env);


/* FT_UPDATE_ENV.C */
int		ft_check_old(t_var *var);
void	ft_update_env (t_var *var, char *path);
void	ft_old_env(t_var *var, int i);
void	reset_env(t_var *var, char *src);
void	deset_env(t_var *var);

/* FT_UPDATE_EXP.C */
void	ft_old_exp(t_var *var, int i);
void	ft_update_exp(t_var *var, char *path);


/* FT_EXPORT_ONE.C */
int		ft_check_var(char *str, t_var *var, int index);
void	ft_export_env(t_var *var, char *str);
void	ft_export_export(t_var *var, char *str, int index);
int		ft_printf_export(t_tabs *tabs, t_var *var);
int		ft_build_export(t_tabs *tabs, t_var *var, int print);


/* FT_EXPORT_TWO.C */
char	**ft_new_src(char **src, char *str, int len);
char	**replace_var(char **src, char *str, int place);
void	ft_sort_new_export(t_var *var);


/* FT_UNSET.C */
void	ft_unset_export(t_tabs *tabs, t_var *var, char *cmd_one);
int		ft_build_unset(t_tabs *tabs, t_var *var, int print);


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
int		ft_cmp_ascii(char *input, char *str);
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


/* FT_MALLOC.C */
char	**ft_malloc_array(int size);
char	*ft_malloc_str(int size);

/* TO BE REMOVED */
void	PRINT_SHELL(t_shell **a);
void	PRINT_CMDS(t_tabs **a);
void	PRINT_PATHS(t_tabs **a);
void	PRINT_REDOP(t_tabs **tabs);





void	ft_pars_spaces(t_tabs **tabs);



#endif
