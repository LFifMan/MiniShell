/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_spaces_tabs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:19:30 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/20 17:09:26 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//todo : line 79 exit instead of return.

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
char	*word_dup(char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	q;
	char	**split;

	if (!s)
		return (0);
	split = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
		exit (EXIT_FAILURE);
	i = 0;
	j = 0;
	index = 0;
	while (s[i])
	{
		index = ft_incr_spaces(s, i);
		if (s[i] == SQ || s[i] == DQ)
		{
			q = s[i];
			i++;
			while (s[i] && s[i] != q)
				i++;
			if (s[i])
				i++;
		}
		else
		{
			while (s[i] && s[i] != SQ && s[i] != DQ)
			{
				if (s[i] == c)
				{
					split[j] = word_dup(s, index, i);
					index = i + 1;
					j++;
				}
				i++;
			}
		}
	}
	if (s[i - 1] != ' ')
		split[j++] = word_dup(s, index, i);
	split[j] = 0;
	return (split);
}

char	**ft_split_array(char **cmd, int i, int j, int size)
{
	int		k;
	char	**dest;
	char	**tmp;

	while (cmd[i])
	{
		printf("size = %d and cmd= %s\n", count_words(cmd[i], SPACE), cmd[i]);
		size += count_words(cmd[i++], SPACE);
	
	}
	dest = ft_malloc_array(size);
	i = 0;
	while (cmd[i])
	{
		if (count_words(cmd[i], SPACE) > 1)
		{
			tmp = ft_split(cmd[i], SPACE);
			k = 0;
			while (tmp[k])
				dest[j++] = ft_strdup(tmp[k++], FALSE);
			i++;
			free(tmp);
		}
		else if (ft_check_spaces(cmd[i]) == TRUE)
			i++;
		else
			dest[j++] = ft_strdup(cmd[i++], FALSE);
	}
	dest[j] = 0;
	ft_free_array(cmd, i);
	return (dest);
}

void	ft_pars_spaces(t_tabs **tabs)
{
	t_tabs	*tmp;

	tmp = (*tabs)->next;
	while (tmp)
	{
		if (tmp->cmds)
			tmp->cmds = ft_split_array(tmp->cmds, 0, 0, 0);
		if (tmp->redop)
			tmp->redop = ft_split_array(tmp->redop, 0, 0, 0);
		tmp = tmp->next;
	}
}
