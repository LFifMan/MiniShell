/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:05 by max               #+#    #+#             */
/*   Updated: 2023/02/07 14:19:55 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_update_exp(t_var *var, char *path)
{
	char	*tmp_exp;
	int		i;

	(void)path;
	tmp_exp = malloc(sizeof(char) * 16);
	if (!tmp_exp)
		exit (EXIT_FAILURE);
	i = 0;
	while (var->exp[i])
	{
		if (ft_strncmp(var->exp[i], "declare -x PWD=", 15) == TRUE)
			break ;
		i++;
	}
	ft_old_exp(var, i);
	if (!var->exp[i])
		return ;
	ft_strcpy(tmp_exp, "declare -x PWD=");
	tmp_exp = ft_strjoin(tmp_exp, getcwd(NULL, 0), FALSE);
	free(var->exp[i]);
	var->exp[i] = tmp_exp;
}

void	ft_old_exp(t_var *var, int i)
{
	int		j;
	char	*tmp_exp;

	tmp_exp = ft_strdup("declare -x OLDPWD=", FALSE);
	j = -1;
	while (var->exp[++j])
		if (ft_strncmp(var->exp[j], "declare -x OLDPWD", 17) == TRUE)
			if (var->exp[j][17] == 0 || var->exp[j][17] == EQUAL)
				break ;
	if (!var->exp[j])
		return ;
	free(var->exp[j]);
	if (!var->exp[i])
	{
		free(tmp_exp);
		var->exp[j] = ft_strdup("declare -x OLDPWD=\"\"", FALSE);
	}
	else
		var->exp[j] = ft_strjoin(tmp_exp, &var->exp[i][15], FALSE);
}

int	ft_find_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_memcmp((char *)env[i], "HOME=", 5) != 0)
		i++;
	return (i);
}
