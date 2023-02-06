/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:15:26 by max               #+#    #+#             */
/*   Updated: 2023/02/03 15:36:24 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_next_pipe(t_shell *shell, int print)
{
	if (ft_strlen(shell->data) > 1)
		return (ft_write_op("||", 258, print));
	if (!shell->next)
		return (ft_write_op("|", 258, print));
	shell = shell->next;
	while (shell && shell->index != PIPE)
	{
		if (shell->index != SPACE)
			return (TRUE);
		shell = shell->next;
	}
	return (ft_write_op("|", 258, print));
}

int	ft_check_next_redirection(t_shell *shell, int print)
{
	if (ft_strlen(shell->data) > 3 && shell->index == GREAT)
		return (ft_write_op(">>", 258, print));
	if (ft_strlen(shell->data) > 3 && shell->index == SMALL)
		return (ft_write_op("<<", 258, print));
	if (ft_strlen(shell->data) > 2 && shell->index == GREAT)
		return (ft_write_op(">", 258, print));
	if (ft_strlen(shell->data) > 2 && shell->index == SMALL)
		return (ft_write_op("<", 258, print));
	if (!shell->next)
		return (ft_write_op("newline", 258, print));
	shell = shell->next;
	if (shell->index == SPACE)
	{
		if (!shell->next || (shell->next->index != CHARS && \
		shell->next->index != DOUBLEQUOTE && shell->next->index != SINGLEQUOTE))
			return (ft_write_op("newline", 258, print));
	}
	else if (shell->index != CHARS && shell->index \
	!= DOUBLEQUOTE && shell->index != SINGLEQUOTE)
		return (ft_write_op("newline", 258, print));
	return (TRUE);
}

int	ft_check_op(t_shell *shell)
{
	shell = shell->next;
	while (shell)
	{
		if (shell->index == PIPE)
		{
			if (ft_check_next_pipe(shell, FALSE) == FALSE)
				return (ft_check_next_pipe(shell, TRUE));
		}
		else if (shell->index == GREAT || shell->index == SMALL)
		{
			if (ft_check_next_redirection(shell, FALSE) == FALSE)
				return (ft_check_next_redirection(shell, TRUE));
		}
		shell = shell->next;
	}
	return (TRUE);
}

int	ft_check_spaces(char *input)
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
