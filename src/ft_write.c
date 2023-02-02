/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/01/31 18:16:14 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_write_op(char *str, int status)
{
	write (2, "\"minishell: syntax error near unexpected token `", ft_strlen("minishell: syntax error near unexpected token `"));
	write (2, str, ft_strlen(str));
	write (2, "'\n", 2);
	g_status = status;
	return (FALSE);
}

void	ft_write(char *str, int option, int status)
{
	char	*buf;

	if (option == 0) // from ft_cd_alone && ft_build_cd file does not exist
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: cd: ", FALSE), str, FALSE), \
		": No such file or directory\n", FALSE);
	if (option == 1) // from ft_build (chmod)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: cd: ", FALSE), str, FALSE), \
		": Permission denied\n", FALSE);
	if (option == 2) //ft_child
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: ", FALSE), str, FALSE), \
		": command not found\n", FALSE);
	if (option == 3) //redops
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: ", FALSE), str, FALSE), \
		": No such file or directory\n", FALSE);
	if (option == 4)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: export: `", FALSE), str, FALSE), \
		"': not a valid identifier\n", FALSE);
	if (option == 5)
		buf = ft_strjoin(ft_strjoin(ft_strdup("minishell: unset: `", FALSE), str, FALSE), \
		"': not a valid identifier\n", FALSE);
	write(2, buf, ft_strlen(buf));
	g_status = status;
	free(buf);
}
