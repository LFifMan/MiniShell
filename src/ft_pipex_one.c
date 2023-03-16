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

void	ft_child(t_tabs *tabs, t_var *var)
{
	char	*cmd_one;

	var->redir_in = 0;
	var->redir_out = 0;
	ft_redops_handler(tabs, var);
	if (tabs->next)
		ft_fd_handlers(var, 1);
	else if (!tabs->next && var->i != 0 && var->redir_in == 0)
		ft_fd_handlers(var, 2);
	if (tabs->cmds && tabs->cmds[0])
	{
		cmd_one = ft_str_lower(tabs->cmds[0]);
		if (ft_builtins(tabs, var, cmd_one) == TRUE)
			ft_handle_execution(var, tabs, 1, cmd_one);
		else
			ft_handle_execution(var, tabs, 2, cmd_one);
	}
	ft_fd_handlers(var, 0);
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
		if (tabs->ambiguity == FALSE)
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
