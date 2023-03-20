/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reparse_spaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:39:45 by max               #+#    #+#             */
/*   Updated: 2023/03/20 16:58:12 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	ft_incr_spaces(char *cmd, int i)
{
	while (cmd[i] && cmd[i] == SPACE)
		i++;
	return (i);
}

int	ft_incr_quotes(char *cmd, int i, char c)
{
	i++;
	while (cmd[i] && cmd[i] != c)
		i++;
	if (cmd[i])
		i++;
	return (i);
}

int	ft_incr_chars(char *cmd, int i)
{
	while (cmd[i] && cmd[i] != DQ && cmd[i] != SQ && cmd[i] != SPACE)
		i++;
	return (i);
}


int	count_words(char *cmd, char c)
{
	int	count;
	int	i;

	(void)c;
	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == SPACE)
			i = ft_incr_spaces(cmd, i);
		else if (cmd[i] && (cmd[i] == SQ || cmd[i] == DQ))
		{
			i = ft_incr_quotes(cmd, i, cmd[i]);
			if (cmd[i] == SPACE || cmd[i] == 0)
				count++;
		}
		else
		{
			i = ft_incr_chars(cmd, i);
			if (cmd[i] == SPACE || cmd[i] == 0)
				count++;
		}
	}
	return (count);
}

int	count_total_words(char **cmd)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (cmd[i])
	{
		size += count_words_two(cmd[i]);
		i++;
	}
	return (size);
}

int find_start(char *cmd, int end)
{
	while (cmd[end] && (cmd[end] == SPACE || (cmd[end] >= 9 && cmd[end] <= 13)))
	{
		end++;
	}
	if (!cmd[end])
		return (-1);
	return (end);
}

int	find_end(char *cmd, int i)
{
	while (cmd[i] && (cmd[i] != SPACE && (cmd[i] < 9 || cmd[i] > 13)))
	{
		i++;
	}
	return (i);
}

char	*fill_malloc(char *cmd, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_malloc_str((end - start) + 2);
	result[i++] = DQ;
	while (start < end)
	{
		result[i++] = cmd[start++];
	}
	result[i++] = DQ;
	result[i] = 0;
	return (result);
}

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
		compteur = count_words_two(cmd[i_cmd]);
		if (compteur == 1)
			tab[i_tab++] = ft_strdup(cmd[i_cmd], FALSE);
		else if (compteur > 1)
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