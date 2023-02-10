/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:40:05 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/09 19:07:23 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc(t_tabs *tabs, t_var *var, int j)
{
	char	*delimiter;					
	char	*input;
	char	path[1024];
	int		fd;

	var->redir_in = 1;
	delimiter = tabs->redop[j + 1];
	input = NULL;
	while (1)
	{
		input = readline("heredoc> ");
		if (strcmp(input, delimiter) == 0)
			break ;
	}
	getcwd(path, sizeof(path));
	strcat(path, "/tempfile");
	fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, input, strlen(input)); // write the input to the file
	close(fd);
	var->in_fd = open("tempfile", O_RDONLY); // redirect input to the file
	dup2(var->in_fd, 0);
	close(var->in_fd);
	unlink("tempfile");
	free(input);
}

void	ft_child(t_tabs *tabs, t_var *var)
{
	int	k;
	char	*cmd_one;

	k = 0;
	var->redir_in = 0;
	var->redir_out = 0;
	ft_redops_handler(tabs, var);
	if (var->i != 0 && var->redir_in == 0)
		dup2(var->fd[0], 0);
	if (tabs->next && var->redir_out == 0)
		dup2(var->fd[1], 1);
	close(var->fd[0]);
	close(var->fd[1]);
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
	exit (0);
}

void	ft_parent(t_tabs *tabs, t_var *var)
{
	if (var->i != 0)
		close(var->fd[0]);
	if (tabs->next != NULL)
		close(var->fd[1]);
}

void	ft_process_execution(t_var *var, t_tabs *tabs)
{
	pipe(var->fd);
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
