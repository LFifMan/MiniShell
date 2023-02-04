/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/02/03 15:47:56 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_write_op(char *str, int status, int print)
{
	if (print == TRUE)
	{
		write (2, "\"minishell: syntax error near unexpected token `", 49);
		write (2, str, ft_strlen(str));
		write (2, "'\n", 2);
		g_status = status;
	}
	return (FALSE);
}

void	ft_write(char *str, int option, int status)
{
	char	*buf;

	if (option == 0)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: cd: ", FALSE), \
		str, FALSE), ": No such file or directory\n", FALSE);
	if (option == 1)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: cd: ", FALSE), \
		str, FALSE), ": Permission denied\n", FALSE);
	if (option == 2)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: ", FALSE), \
		str, FALSE), ": command not found\n", FALSE);
	if (option == 3)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: ", FALSE), \
		str, FALSE), ": No such file or directory\n", FALSE);
	if (option == 4)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: export: `", FALSE), \
		str, FALSE), "': not a valid identifier\n", FALSE);
	if (option == 5)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: unset: `", FALSE), \
		str, FALSE), "': not a valid identifier\n", FALSE);
	write(2, buf, ft_strlen(buf));
	g_status = status;
	free(buf);
}
