/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reparse_spaces_one.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:39:45 by max               #+#    #+#             */
/*   Updated: 2023/03/20 17:34:30 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_resplit(char *cmd, char **tab, int i_tab, int start)
{
	int	end;

	end = 0;
	while (cmd[end])
	{
		start = find_start(cmd, end);
		if (start == -1)
			break ;
		end = find_end(cmd, start);
		tab[i_tab] = fill_malloc(cmd, start, end);
		i_tab++;
	}
	return (i_tab);
}

void	prepare_tab(char **tab, char **cmd)
{
	int	i_tab;
	int	i_cmd;
	int	compteur;

	i_cmd = 0;
	i_tab = 0;
	while (cmd[i_cmd])
	{
		compteur = count_words(cmd[i_cmd]);
		if (compteur > 0)
			i_tab = ft_resplit(cmd[i_cmd], tab, i_tab, 0);
		i_cmd++;
	}
	tab[i_tab] = 0;
	ft_free_array(cmd, i_cmd);
}

char	**ft_split_array_two(char **cmd)
{
	char	**tab;
	int		size;

	size = count_total_words(cmd);
	tab = malloc((size + 1) * sizeof(char *));
	if (!tab)
		exit (EXIT_FAILURE);
	prepare_tab(tab, cmd);
	return (tab);
}

void	ft_reparse_spaces(t_tabs **tabs)
{
	t_tabs	*tmp;

	tmp = (*tabs)->next;
	while (tmp)
	{
		if (tmp->cmds)
			tmp->cmds = ft_split_array_two(tmp->cmds);
		if (tmp->redop)
			tmp->redop = ft_split_array_two(tmp->redop);
		tmp = tmp->next;
	}
}
