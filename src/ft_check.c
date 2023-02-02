/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:15:26 by max               #+#    #+#             */
/*   Updated: 2023/01/31 14:59:47 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_next_pipe(t_shell *shell)
{
	if (ft_strlen(shell->data) > 1)
		return (ft_write_op("||", 258));
	if (!shell->next)
		return (ft_write_op("|", 258));
	shell = shell->next;
	while (shell && shell->index != PIPE)
	{
		if (shell->index != SPACE)
			return (TRUE);
		shell = shell->next;
	}
	return (ft_write_op("|", 258));
}

int	ft_check_next_redirection(t_shell *shell)
{
	if (ft_strlen(shell->data) > 3 && shell->index == GREATER)
		return (ft_write_op(">>", 258));
	if (ft_strlen(shell->data) > 3 && shell->index == SMALLER)
		return (ft_write_op("<<", 258));
	if (ft_strlen(shell->data) > 2 && shell->index == GREATER)
		return (ft_write_op(">", 258));
	if (ft_strlen(shell->data) > 2 && shell->index == SMALLER)
		return (ft_write_op("<", 258));
	if (!shell->next)
		return (ft_write_op("newline", 258));
	shell = shell->next;
	if (shell->index == SPACE)
	{
		if (!shell->next || (shell->next->index != CHARS && \
		shell->next->index != DOUBLEQUOTE && shell->next->index != SINGLEQUOTE))
			return (ft_write_op("newline", 258));
	}
	else if (shell->index != CHARS && shell->index \
	!= DOUBLEQUOTE && shell->index != SINGLEQUOTE)
		return (ft_write_op("newline", 258));
	return (TRUE);
}

int	ft_check_op(t_shell *shell)
{
	shell = shell->next;
	while (shell)
	{
		if (shell->index == PIPE)
		{
			return (ft_check_next_pipe(shell));
		}
		else if (shell->index == GREATER || shell->index == SMALLER)
			return (ft_check_next_redirection(shell));
		shell = shell->next;
	}
	return (TRUE);
}

int	check_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != SPACE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
