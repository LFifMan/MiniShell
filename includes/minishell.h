/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:43 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/20 17:40:58 by mstockli         ###   ########.fr       */
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
	int				tmpfd;
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
	int				ambiguity;
}					t_tabs;

int	g_status;

/* FT_AMBIGUITY.C */

int		ft_check_ambiguity(t_tabs **tabs);
void	ft_pars_spaces_two(t_tabs **tabs);

/* FT_BUILT.C */

int		ft_build_echo(t_tabs *tabs, t_var *var);
int		ft_build_pwd(t_tabs *tabs, t_var *var);
int		ft_build_env(t_tabs *tabs, t_var *var);
int		ft_build_cd(t_tabs *tabs, t_var *var, int print);

/* FT_BUILT_TWO.C */

char	*ft_str_lower(char *str);
int		ft_builtins(t_tabs *tabs, t_var *var, char *cmd_one);

/* FT_BUILT_UTILS_ONE.C */

int		ft_option_n(char *str);
int		ft_find_dir(const char *path);
char	*ft_create_root(char *env, int j);
void	ft_update_pwd(t_var *var, char *root);
void	ft_cd_alone(char **env, int print, t_var *var);

/* FT_BUILT_UTILS_TWO.C */

int		check_num(char *str);
int		ft_build_exit(t_tabs *tabs, t_var *var, int print);
void	ft_cd_absolute(t_tabs *tabs, t_var *var, int print);
void	ft_cd_relative(t_tabs *tabs, t_var *var, int print, char *current);
int		ft_find_home(char **env);

/* FT_CHECK.C */

int		ft_check_next_pipe(t_shell *shell, int print);
int		ft_check_next_redirection(t_shell *shell, int print);
int		ft_check_op(t_shell *shell);
int		ft_check_spaces(char *input);

/* FT_CTRL_TWR_ONE.C */
int		ft_ctrl_prs(t_shell **shell, t_var *var, char *input, t_tabs *tabs);
int		ft_ctrl_cmd(t_tabs **tabs, t_shell **shell, t_var *var);
void	ft_ctrl_twr(t_var *var);

/* FT_CTRL_TWR_TWO.C */
char	*ft_prompt(t_var *var);
int		ft_check_builtins(char *cmd_one);
int		ft_execution(t_tabs *tabs, t_var *var);

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

/* FT_FREE_LSTS_ONE.C */

int		ft_free_shell(t_shell *lst);
void	ft_free(t_tabs *lst);
int		ft_free_tabs(t_tabs *lst);
void	ft_free_lst(t_shell *shell, t_tabs *tabs, char *input, int index);
void	ft_free_var(t_var var);

/* FT_FREE_LSTS_TWO.C */

void	ft_free_array(char **exp, int len_env);

/* FT_INIT_ONE.C */

char	*get_root_new(char **env);
void	ft_init_env(t_var *var, char **env, int len_env);
void	ft_init_var(t_var *var, char **env);

/* FT_INIT_TWO.C */

char	**ft_create_exp(int len_env, char **exp);
char	**ft_dup_exp(t_var *var, int len_env);
void	ft_sort_exp(int len_env, char **exp);
char	*ft_shlvl(char *env);

/* FT_LSTS.C */

char	ft_add_index(char c, int index);
char	*ft_add_data(char *input);
void	ft_lst_new(t_shell **lst, char *input, int index, int old_index);
void	ft_lstregroup_back(	t_tabs **tabs, t_shell *input);

/* FT_MALLOC.C */

char	*ft_malloc_str(int size);
char	**ft_malloc_array(int size);

/* FT_DOLLAR_ONE.C */

int		loop_get_dollar_place(char *data, int i);
int		ft_get_dollar_place(char *data);
int		loop_look_for_dollar(char *data, int i);
int		ft_look_for_dollar(char *data);

/* FT_DOLLAR_TWO.C */

int		ft_iteration(char c);
int		ft_check_allowed_char(char c, int pos);
char	*ft_replace_status(char *data, int status, int place);
int		ft_look_in_envp(char *data, char *env, int i);
char	*ft_replace(char *data, char *env, int data_i);

/* FT_DOLLAR_THREE.C */

char	*ft_remove_dollar(char *data, int start);
char	*ft_replace_dollar(char **env, char *data, int status);
void	ft_pars_dollar(t_tabs **tabs, t_var *var);

/* FT_DOLLAR_THREE.C */

char	*ft_rep_quotes(char *cmd, int i, int j);

/* FT_REPARSE_SPACES_ONE.C */

void	ft_reparse_spaces(t_tabs **tabs);
char	**ft_split_array_two(char **cmd);
void	prepare_tab(char **tab, char **cmd);
int		ft_resplit(char *cmd, char **tab, int i_tab, int start);

/* FT_REPARSE_SPACES_TWO.C */

char	*fill_malloc(char *cmd, int start, int end);
int		find_end(char *cmd, int i);
int		find_start(char *cmd, int end);

/* FT_REPARSE_SPACES_THREE.C */

int		count_total_words(char **cmd);
int		count_words(char *cmd);
int		ft_incr_quotes(char *cmd, int i, char c);
int		ft_incr_chars(char *cmd, int i);
int		ft_incr_spaces(char *cmd, int i);

/* FT_PARSING_INPUT.C */

char	*parse_quotation(char *input, char index, int size, int i);
int		parsing_quotations(t_shell **shell, char *input);
void	split_spaces(t_shell **shell, char *input, int old_index);
t_shell	*parsing_spaces(t_shell **shell);

/* FT_PARSING_PATHS.C */

void	ft_paths(t_var var, t_tabs **tabs);
char	**ft_create_paths(void);
char	**ft_parsing_binaries(char *const *envp, char *argv);
char	*ft_mallocfill_bin(char **str, char c, char *argv, int beg);
int		ft_countwords(char *str, char c);
char	**ft_split_bin(char *str, char c, char *argv, int i);

/* FT_PARSING_PIPES.C */

void	ft_prepare_new(t_shell *new, t_shell *shell);
t_shell	*ft_create_new(void);
t_shell	*parsing_pipes(t_shell *shell);

/* FT_PARSING_REDOP.C */

int		ft_count_redops(char **cmd);
char	**ft_remove_redop_cmds(char **cmd, int index);
int		ft_tmp_redop(t_tabs *tmp, int i, int j);
void	ft_redops(t_tabs **tabs);

/* FT_PARSING_REGROUP_ONE.C */

char	*ft_trim_quotations(char *str);
int		ft_lst_count_spaces(t_shell *lst);
t_tabs	*ft_regroup(t_shell **shell, t_var *var);
void	ft_split_pipes(t_shell **shell, char *input);

/* FT_PIPEX_ONE.C */

void	ft_child(t_tabs *tabs, t_var *var);
void	ft_parent(t_tabs *tabs, t_var *var);
void	ft_process_execution(t_var *var, t_tabs *tabs);
void	ft_pipex(t_tabs *tabs, t_var *var);

/* FT_PIPEX_TWO.C */

void	ft_heredoc_two(t_var *var);
void	ft_heredoc(t_tabs *tabs, t_var *var, int j);
void	ft_fd_handlers(t_var *var, int option);
void	ft_handle_exec(t_var *var, t_tabs *tabs, int option, char *cmd_one);

/* FT_REDIRECTIONS.C */

void	ft_to_name(t_shell *tmp, t_shell *new, int option);
t_shell	*ft_space_redops(t_shell **shell);
void	ft_split_redirections(t_shell **shell, char *str);
void	ft_split_add(t_shell *tmp, t_shell *new);
t_shell	*parsing_redops(t_shell **shell);

/* FT_REDOPS-HANDLER.C */

void	ft_handle_heredoc(t_tabs *tabs, t_var *var, int i);
void	ft_handle_append_redir(t_tabs *tabs, t_var *var, int i);
void	ft_handle_input_redir(t_tabs *tabs, t_var *var, int i);
void	ft_handle_trunc_redir(t_tabs *tabs, t_var *var, int i);
void	ft_redops_handler(t_tabs *tabs, t_var *var);

/* FT_SIGNALS.C */

void	ft_sigint_handler(int sig);
void	ft_block_signal(int sig);
void	ft_enable_signal(void);
void	ft_halt_signal(void);
void	ft_signals(int index);

/* FT_TRIM_QUOTES.C */

int		ft_trim_count(char *cmd, int i, int j);
char	*ft_trim_cmds(char *cmd, int size, int i, int j);
void	ft_trim_quotes(t_tabs **tabs);

/* FT_UNSET.C */

void	ft_remove_env_var(t_var *var, char *str);
void	ft_remove_export_var(t_var *var, char *str);
int		ft_build_unset(t_tabs *tabs, t_var *var, int print);
void	ft_unset_export(t_tabs *tabs, t_var *var, char *cmd_one);

/* FT_UPDATE_ENV.C */

void	ft_update_env(t_var *var, char *path);
int		ft_check_old_env(t_var *var);
void	deset_env(t_var *var);
void	reset_env(t_var *var, char *src);
void	ft_old_env(t_var *var, int i);
int		ft_check_old(t_var *var);

/* FT_UPDATE_EXP.C */

void	ft_update_exp(t_var *var, char *path);
void	ft_old_exp(t_var *var, int i);
int		ft_find_pwd(char **env);

/* FT_UTILS_FOUR.C */

char	*dest(int n, int count);
char	*ft_itoa(int n);
int		ft_is_whitespace(char *str);
int		ft_atoi(char *str);

/* FT_UTILS_ONE.C */

char	*ft_strcpy(char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int		ft_strcmp(char *input, char *str);
int		ft_memcmp(void *s1, void *s2, size_t n);
char	*ft_zero(const char *s);

/* FT_UTILS_THREE.C */

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* FT_UTILS_TWO.C */

char	*ft_join(int index, char *s1, char *s2, char *dest);
char	*ft_join_exp(char *s1, char *s2, int index);
int		ft_cmp_ascii(char *input, char *str);
char	*ft_strjoin(char *s1, char *s2, int index);
char	*ft_strdup(char *src, int index);

/* FT_WRITE.C */

int		ft_write_op(char *str, int status, int print);
void	ft_write(char *str, int option, int status);
void	ft_write_exit(char *str, int option, int status);

/* FT_MAIN.C */

int		main(int ac, char **av, char **ev);

#endif
