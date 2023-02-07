/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redops_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:40:05 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/06 22:49:12 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_heredoc(t_tabs *tabs, t_var *var, int i)
{
	ft_heredoc(tabs, var, i);
	i += 1;
	//ft_write(tabs->redop[i], 3, 1);
	//todo : ft_write(option = 3 || 1 withno cd ?)
}

void	ft_handle_append_redir(t_tabs *tabs, t_var *var, int i)
{
	i += 1;
	var->redir_out = 1;
	var->out_fd = open(tabs->redop[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(var->out_fd, 1);
	close(var->out_fd);
	if (var->out_fd < 0)
	{
		ft_write(tabs->redop[i], 3, 1);
		exit (1);
	}
}

void	ft_handle_input_redir(t_tabs *tabs, t_var *var, int i)
{
	i += 1;
	var->redir_in = 1;
	var->in_fd = open(tabs->redop[i], O_RDONLY);
	dup2(var->in_fd, 0);
	close(var->in_fd);
	if (var->in_fd < 0)
	{
		ft_write(tabs->redop[i], 3, 1);
		exit (1);
	}
}

void	ft_handle_trunc_redir(t_tabs *tabs, t_var *var, int i)
{
	i += 1;
	var->redir_out = 1;
	var->out_fd = open(tabs->redop[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(var->out_fd, 1);
	close(var->out_fd);
	if (var->out_fd < 0)
	{
		ft_write(tabs->redop[i], 3, 1);
		exit (1);
	}
}

void	ft_redops_handler(t_tabs *tabs, t_var *var)
{
	int	i;

	i = 0;
	if (!tabs->redop[i])
		return ;
	while (tabs->redop[i])
	{
		if (ft_strcmp(tabs->redop[i], "<<") == TRUE)
			ft_handle_heredoc(tabs, var, i);
		else if (ft_strcmp(tabs->redop[i], ">>") == TRUE)
			ft_handle_append_redir(tabs, var, i);
		else if (ft_strcmp(tabs->redop[i], "<") == TRUE)
			ft_handle_input_redir(tabs, var, i);
		else if (ft_strcmp(tabs->redop[i], ">") == TRUE)
			ft_handle_trunc_redir(tabs, var, i);
		i++;
	}
}
