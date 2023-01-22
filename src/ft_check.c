/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:15:26 by max               #+#    #+#             */
/*   Updated: 2023/01/23 00:00:28 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_next_pipe(t_shell *shell)
{
	if (ft_strlen(shell->data) > 1)
		return (FALSE);
	shell = shell->next;
	while (shell && shell->index != PIPE)
	{
		if (shell->index != SPACE)
			return (TRUE);
		shell = shell->next;
	}
	return (FALSE);
}

int	ft_check_next_redirection(t_shell *shell)
{
	if (ft_strlen(shell->data) > 2)
		return (FALSE);
	shell = shell->next;
	if (shell->index == SPACE)
	{
		if (!shell->next)
			return (FALSE);
		if (shell->next->index != CHARS && shell->next->index != DOUBLEQUOTE && shell->next->index != SINGLEQUOTE)
			return (FALSE);
	}
	else if (shell->index != CHARS && shell->index != DOUBLEQUOTE && shell->index != SINGLEQUOTE)
		return (FALSE);

	return (TRUE);
}

int	ft_check_op(t_shell *shell)
{
	shell = shell->next;
	while (shell)
	{
		if (shell->index == PIPE)
		{
			if (!shell->next || ft_check_next_pipe(shell) == FALSE)
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return (FALSE);
			}
		}
		else if (shell->index == GREATER || shell->index == SMALLER)
		{
			if (!shell->next || ft_check_next_redirection(shell) == FALSE)
			{
				printf("bash: syntax error near unexpected token `%c'\n", shell->index);
				return (FALSE);
			}
		}
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
