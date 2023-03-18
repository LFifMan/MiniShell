/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_spaces_tabs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:19:30 by mstockli          #+#    #+#             */
/*   Updated: 2023/03/17 18:25:17 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//todo : line 79 exit instead of return.

#include "../includes/minishell.h"

int	count_words(const char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
		{
			while (*str && *str == c)
				str++;
		}
		else if (*str == SQ)
		{
			str++;
			while (*str && *str != SQ)
			{
				str++;
			}
			if (*str)
				str++;
			if (*str == c || *str == 0)
				i++;
		}
		else if (*str && *str == DQ)
		{
			str++;
			while (*str && *str != DQ)
				str++;
			if (*str)
				str++;
			if (*str == c || *str == 0)
				i++;
		}
		else
		{
			while (*str && *str != DQ && *str != SQ && *str != c)
				str++;
			if (*str == c || *str == 0)
				i++;
		}
	}
	return (i);
}

char	*word_dup(const char *str, int start, int finish)
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

char	**ft_split(char const *s, char c)
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

char	**ft_split_array(char **cmd)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	**dest;
	char	**tmp;

	i = 0;
	j = 0;
	size = 0;

	while (cmd[i])
	{
		size += count_words(cmd[i], SPACE);
		i++;
	}
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		exit(EXIT_FAILURE);
	i = 0;
	while (cmd[i])
	{
		if (count_words(cmd[i], SPACE) > 1)
		{
			tmp = ft_split(cmd[i], SPACE);
			k = 0;
			while (tmp[k])
			{
				dest[j] = ft_strdup(tmp[k], FALSE);
				k++;
				j++;
			}
			i++;
			free(tmp);
		}
		else if (ft_check_spaces(cmd[i]) == TRUE)
			i++;
		else
		{
			dest[j] = ft_strdup(cmd[i], FALSE);
			i++;
			j++;
		}
	}
	dest[j] = 0;
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	return (dest);
}

void	ft_pars_spaces(t_tabs **tabs)
{
	t_tabs	*tmp;

	tmp = (*tabs)->next;
	while (tmp)
	{
		if (tmp->cmds)
			tmp->cmds = ft_split_array(tmp->cmds);
		if (tmp->redop)
			tmp->redop = ft_split_array(tmp->redop);
		tmp = tmp->next;
	}
}
