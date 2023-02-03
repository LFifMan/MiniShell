/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:40:05 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/03 15:51:41 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc(t_tabs *tabs, t_vars *vars, int j)
{
	char	*delimiter;					
	char	*input; // store the input from readline
	char	path[1024];
	int		fd;

	vars->redir_in = 1;
	delimiter = tabs->redop[j + 1];
	input = NULL;
	while (1)
	{
		input = readline("heredoc> ");
		if (strcmp(input, delimiter) == 0)
			break;
	}
	getcwd(path, sizeof(path)); // get the current working directory
	// concatenate the current working directory with the file name
	strcat(path, "/tempfile");
		// open the file for writing
	fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, input, strlen(input)); // write the input to the file
	close(fd);
	vars->in_fd = open("tempfile", O_RDONLY); // redirect input to the file
	dup2(vars->in_fd, 0);
	close(vars->in_fd);
	unlink("tempfile");
	free(input);
}

void	ft_redops_handler(t_tabs *tabs, t_vars *vars)
{
	int	j;

	j = 0;
	if (!tabs->redop[j])
	{
		return ;
	}
	while (tabs->redop[j])
	{
		if (ft_strcmp(tabs->redop[j], "<<") == TRUE)
		{
			ft_heredoc(tabs, vars, j);
			// todo : ft_write option == 3 (option 1 sans cd ? a tester)
		}
		else if (ft_strcmp(tabs->redop[j], ">>") == TRUE)
		{
			vars->redir_out = 1;
			vars->out_fd = open(tabs->redop[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(vars->out_fd, 1);
			close(vars->out_fd);
			if (vars->out_fd < 0) // todo : ft_write option == 3
			{
				ft_write(tabs->redop[j + 1], 3, 1);
				exit (1);
			}
		}
		else if (ft_strcmp(tabs->redop[j], "<") == TRUE)
		{
			vars->redir_in = 1;
			vars->in_fd = open(tabs->redop[j + 1], O_RDONLY);
			dup2(vars->in_fd, 0);
			close(vars->in_fd);
			if (vars->in_fd < 0) // todo : ft_write option == 3
			{
				ft_write(tabs->redop[j + 1], 3, 1);
				exit (1);
			}
		}
		else if (ft_strcmp(tabs->redop[j], ">") == TRUE)
		{
			vars->redir_out = 1;
			vars->out_fd = open(tabs->redop[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(vars->out_fd, 1);
			close(vars->out_fd);
			if (vars->out_fd < 0) // todo : ft_write option == 3
			{
				ft_write(tabs->redop[j + 1], 3, 1);
				exit (1);
			}
		}
		j++;
	}
}

void	ft_child(t_tabs *tabs, t_vars *vars)
{
	vars->redir_in = 0;
	vars->redir_out = 0;
	ft_redops_handler(tabs, vars);
	if (vars->i != 0 && vars->redir_in == 0)
		dup2(vars->fd[0], 0);
	if (tabs->next && vars->redir_out == 0)
		dup2(vars->fd[1], 1);
	close(vars->fd[0]);
	close(vars->fd[1]);
	if (ft_builtins(tabs, vars, tabs->cmds[0]) == TRUE)
		exit(0);
	else
	{
		vars->var = execve(tabs->cmds[0], tabs->cmds, vars->envp);
		while (tabs->paths[vars->i] && vars->var < 0)
		{
			vars->var = execve(tabs->paths[vars->i], tabs->cmds, vars->envp);
			vars->i++;
		}
		ft_write(tabs->cmds[0], 2, 127);
		exit(127);
	}
}

void	ft_parent(t_tabs *tabs, t_vars *vars)
{
	if (vars->i != 0)
		close(vars->fd[0]);
	if (tabs->next != NULL)
		close(vars->fd[1]);
}

void	ft_pipex(t_tabs *tabs, t_vars *vars)
{
	vars->var = -1;
	vars->i = 0;
	if (tabs->next)
		tabs = tabs->next;
	while (tabs)
	{
		pipe(vars->fd);
		vars->child = fork();
		if (vars->child < 0)
			printf("la sauce"); //todo : ft_errors(3, tabs);
		if (vars->child == 0)
		{
			ft_child(tabs, vars);
		}
		else
		{
			ft_parent(tabs, vars);
		}
		tabs = tabs->next;
		vars->i++;
	}
	while (vars->i--)
		wait(&vars->status);
	g_status = 0;
	if (WIFEXITED(vars->status))
	{
		g_status = WEXITSTATUS(vars->status);
	}
	else
	{
		g_status = 1;
	}
}
