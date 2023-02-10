/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_spaces_tabs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:19:30 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/10 16:51:14 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int	count_words(const char *str, char c)
{
	int i;
	int trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str == SQ)
		{
			str++;
			while (*str != SQ)
				str++;
		}
		else if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
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

char		**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
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
	dest = malloc(sizeof(char*) * (size + 1));
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
	{
		free(cmd[i]);
		i++;
	}
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