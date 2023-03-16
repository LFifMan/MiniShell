/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/03/06 18:22:01 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_write_op(char *str, int status, int print)
{
	if (print == TRUE)
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, str, ft_strlen(str));
		write (2, "'\n", 2);
		g_status = status;
	}
	return (FALSE);
}

char	*ft_write_two(char *str, int option)
{
	char	*buf;

	if (option == 4)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: export: `", FALSE), \
		str, FALSE), "': not a valid identifier\n", FALSE);
	if (option == 5)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: unset: `", FALSE), \
		str, FALSE), "': not a valid identifier\n", FALSE);
	if (option == 6)
		buf = ft_strdup("Problem with child opening\n", FALSE);
	if (option == 7)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: cd: ", FALSE), \
		str, FALSE), ": Not a relative or absolute path\n", FALSE);
	return (buf);
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
	if (option > 3)
		buf = ft_write_two(str, option);
	write(2, buf, ft_strlen(buf));
	g_status = status;
	free(buf);
}

void	ft_write_exit(char *str, int option, int status)
{
	char	*buf;

	write(2, "exit\n", ft_strlen("exit\n"));
	if (option == 1)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: exit: ", FALSE), \
		str, FALSE), ": numeric argument required\n", FALSE);
	if (option == 2)
		buf = ft_strdup("minishell: exit: too many arguments\n", FALSE);
	write(2, buf, ft_strlen(buf));
	g_status = status;
	free(buf);
}
