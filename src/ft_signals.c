/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 00:01:15 by max               #+#    #+#             */
/*   Updated: 2023/02/14 16:05:39 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
	g_status = 1;
}

void	ft_block_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
	}
	if (sig == SIGQUIT)
	{
		g_status = 131;
	}
}

void	ft_enable_signal(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sig_int.sa_handler = &ft_sigint_handler;
//	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = SIG_IGN;
//	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	ft_halt_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_handler = &ft_block_signal;
//	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = &ft_block_signal;
//	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	ft_signals(int index)
{
	static struct termios	saved_termios;
	static struct termios	modified_termios;

	if (index == TRUE)
	{
		ft_enable_signal();
		tcgetattr(STDIN_FILENO, &saved_termios);
		tcgetattr(STDIN_FILENO, &modified_termios);
		modified_termios.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &modified_termios);
	}
	else
	{
		ft_halt_signal();
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
	}
}


// void	ft_heredoc(t_tabs *tabs, t_var *var, int j)
// {
// 	char	*delimiter;					
// 	char	*input;
// 	char	path[1024];
// 	int		fd;

// 	var->redir_in = 1;
// 	delimiter = tabs->redop[j + 1];
// 	input = NULL;
// 	fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	while (1)
// 	{
// 		input = readline("heredoc> ");
// 		if (strcmp(input, delimiter) == 0)
// 		{
// 			free(input);
// 			break ;
// 		}
// 		write(fd, input, strlen(input));
// 		write(fd, "\n", 1);
// 		free(input);
// 	}
// 	close(fd);
// 	getcwd(path, sizeof(path));
// 	strcat(path, "/tempfile");
// 	var->in_fd = open(path, O_RDONLY); // redirect input to the file
// 	dup2(var->in_fd, 0);
// 	close(var->in_fd);
// 	unlink(path);
// }


// void	ft_heredoc(t_tabs *tabs, t_var *var, int j)
// {
// 	char	*delimiter;					
// 	char	*input;
// 	char	path[1024];
// 	int		fd;

// 	var->redir_in = 1;
// 	delimiter = tabs->redop[j + 1];
// 	input = NULL;
// 	fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	while (1)
// 	{
// 		input = readline("heredoc> ");
// 		if (strcmp(input, delimiter) == 0)
// 		{
// 			free(input);
// 			break ;
// 		}
// 		write(fd, input, strlen(input));
// 		write(fd, "\n", 1);
// 		printf("%s\n", input);
// 		free(input);
// 	}
// 	close(fd);
// 	getcwd(path, sizeof(path));
// 	strcat(path, "/tempfile");
// 	var->in_fd = open(path, O_RDONLY); // redirect input to the file
// 	dup2(var->in_fd, 0);
// 	close(var->in_fd);
// 	unlink(path);
// }