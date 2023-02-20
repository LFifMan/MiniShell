/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:40:05 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/20 15:58:16 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		{
			break ;
		}
		else if (strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		write(var->out_fd, input, strlen(input));
		write(var->out_fd, "\n", 1);
	}

	ft_signals(FALSE);
	dup2(var->out_fd, 0);
	close(var->out_fd);
	var->in_fd = open("tempfile", O_RDONLY);
	dup2(var->in_fd, 0);
	close(var->in_fd);
}

void	ft_child(t_tabs *tabs, t_var *var)
{
	int		k;
	char	*cmd_one;

	k = 0;
	var->redir_in = 0;
	var->redir_out = 0;
	ft_redops_handler(tabs, var);
	if (tabs->next)
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
	else if (!tabs->next && var->i != 0 && var->redir_in == 0) // 
	{
		printf("redir = 0\n");
        dup2(var->tmpfd, 0); // todo: why is it in_fd?
        close(var->tmpfd);
	}
	if (tabs->cmds && tabs->cmds[0])
	{
		cmd_one = ft_str_lower(tabs->cmds[0]);
		if (ft_builtins(tabs, var, cmd_one) == TRUE)
		{
			free(cmd_one);
			exit(0);
		}
		else
		{
			free(cmd_one);
			var->var = execve(tabs->cmds[0], tabs->cmds, var->env);
			while (tabs->paths[k] && var->var < 0)
			{
				var->var = execve(tabs->paths[k], tabs->cmds, var->env);
				k++;
			}
			ft_write(tabs->cmds[0], 2, 127);
			exit(127);
		}
	}
	close(var->fd[0]);
	close(var->fd[1]);
	exit (0);
}

void	ft_parent(t_tabs *tabs, t_var *var)
{
	if (tabs->next != NULL)
	{
		close(var->tmpfd);
		close(var->fd[1]);
		var->tmpfd = var->fd[0];
	}
	else if (!tabs->next && var->i != 0)
	{
		close(var->tmpfd);
	}
}

void	ft_process_execution(t_var *var, t_tabs *tabs)
{
	
	if (var->i != 0 || tabs->next)
	{	
		if (pipe(var->fd) == -1)
		{
				printf("la sauce");
		}
	}
	var->child = fork();
	if (var->child < 0)
		ft_write(tabs->cmds[0], 6, 52);
	if (var->child == 0)
	{
		ft_child(tabs, var);
	}
	else
	{
		ft_parent(tabs, var);
	}
}


void	ft_pipex(t_tabs *tabs, t_var *var)
{
	var->var = -1;
	var->i = 0;
	var->tmpfd = dup(0);

	if (tabs->next)
		tabs = tabs->next;
	while (tabs)
	{
		ft_process_execution(var, tabs);
		tabs = tabs->next;
		var->i++;
	}
	while (var->i--)
		wait(&var->status);
	g_status = 0;
	if (WIFEXITED(var->status))
	{
		g_status = WEXITSTATUS(var->status);
	}
	else
	{
		g_status = 1;
	}
}









/*
void	ft_pipex(t_tabs *tabs, t_var *var)
{
	int		fd[2];
	int		tmpfd;
	pid_t	child;
	int		i;
	int		status;
	int		var2;

	var2 = -1;
	i = 0;
	tmpfd = dup(0);
	tabs = tabs->next;
	while (tabs)
	{
		if (i != 0 || tabs->next)
		{
			printf("in da pipe\n");
		
			if (pipe(fd) == -1)
			{

				printf("la sauce");
			}
		}
		child = fork();
		if (child < 0)
			printf("la sauce"); //ft_errors(3, tabs);
		if (child == 0)
		{
			if (tabs->next )
			{
				if (var->redir_out == 0)
				{
					dup2(fd[1], 1);
					close(fd[1]);

				}	
		
				if (var->redir_in == 0)
				{
					dup2(tmpfd, 0);
					close(tmpfd);
					close(fd[0]);
				}
				dup2(tmpfd, 0);
				dup2(fd[1], 1);
				close(tmpfd);
				close(fd[0]);
				close(fd[1]);
			}
			else if (!tabs->next && i != 0 && var->redir_in == 0)
			{
				dup2(tmpfd, 0);
				close(tmpfd);
			}
				dup2(tmpfd, 0);
			if (tabs->next != NULL)
				dup2(fd[1], 1);
			else
			{
				dup2(tmpfd, 0);
				close(tmpfd);
			}
			close(tmpfd);
			close(fd[1]);
			*/
/*			while (tabs->paths[i] && var2 < 0)
			{
				var2 = execve(tabs->paths[i], tabs->cmds, var->env);
				i++;
			}
			printf("bash: %s command not found\n", tabs->cmds[0]);//ft_errors(4, tabs);
		}
		else
		{
			if (tabs->next != NULL)
			{
				close(tmpfd);
				close(fd[1]);
				tmpfd = fd[0];
			}
			else if (!tabs->next && i != 0)
			{
				close(tmpfd);
			}
			//if (i != 0)
				close(tmpfd);
			if (!tabs->next)
			{
				close(tmpfd);
				
			}
			close(fd[1]);
			tmpfd = fd[0];
			*/
		/*
		}
		tabs = tabs->next;
		i++;
	}
	while (i--)
		wait(&status);
	//tmpfd = dup(0);
}
*/