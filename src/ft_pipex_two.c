/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:40:05 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/06 19:15:48 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc_two(t_var *var)
{
	ft_signals(FALSE);
	dup2(var->out_fd, 0);
	close(var->out_fd);
	var->in_fd = open("tempfile", O_RDONLY);
	dup2(var->in_fd, 0);
	close(var->in_fd);
}

void	ft_heredoc(t_tabs *tabs, t_var *var, int j)
{
	char	*delimiter;
	char	*input;

	var->redir_in = 1;
	delimiter = tabs->redop[j + 1];
	input = NULL;
	var->out_fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_signals(TRUE);
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			break ;
		else if (strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		write(var->out_fd, input, strlen(input));
		write(var->out_fd, "\n", 1);
	}
	ft_heredoc_two(var);
}

void	ft_fd_handlers(t_var *var, int option)
{
	if (option == 1)
	{
		if (var->redir_out == 0)
		{
			dup2(var->fd[1], 1);
			close(var->fd[1]);
		}
		if (var->redir_in == 0)
		{
			dup2(var->tmpfd, 0);
			close(var->tmpfd);
			close(var->fd[0]);
		}
	}
	else if (option == 2)
	{
		dup2(var->tmpfd, 0);
		close(var->tmpfd);
	}
	else
	{
		close(var->fd[0]);
		close(var->fd[1]);
		exit(0);
	}
}

void	ft_handle_execution(t_var *var, t_tabs *tabs, int option, char *cmd_one)
{
	int	k;

	k = 0;
	if (option == 1)
	{
		free(cmd_one);
		exit(0);
	}
	else if (option == 2)
	{
		free(cmd_one);
		var->var = execve(tabs->cmds[0], tabs->cmds, var->env);
		while (tabs->paths[k] && var->var < 0)
			var->var = execve(tabs->paths[k++], tabs->cmds, var->env);
		ft_write(tabs->cmds[0], 2, 127);
		exit(127);
	}
}
