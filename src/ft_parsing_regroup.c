/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_regroup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:25:12 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/20 19:48:17 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_trim_quotations(char *str)
{
	char	*dest;
	
	if (str[0] == SINGLEQUOTE || str[0] == DOUBLEQUOTE)
	{
		if (ft_strlen(str) == 2)
			return (ft_strdup(""));
		dest = (char *)malloc(sizeof(char) * (ft_strlen(str) - 2 + 1));
		ft_strlcpy(dest, (char *)str + 1, (ft_strlen(str) -2 + 1));
		return (dest);
	}
	return (str);
}

int	ft_lst_count_spaces(t_shell *lst)
{
	int	i;

	i = 1;
	if (lst->index == SPACE && lst->next)
		lst = lst->next;
	while (lst)
	{
		if (lst->index == SPACE && lst->next && lst->next->index != PIPE)
			i++;
		else if (lst->index == PIPE)
			return (i);
		lst = lst->next;
	}
	return (i);
}

/* To keep the quotes ===
ft_trim_quotations(tmp->data) --> tmp->data*/
t_tabs	*ft_regroup(t_shell **shell, t_vars *vars)
{
	t_tabs	*tabs;
	t_shell	*tmp;

	(void)vars;

	tabs = malloc(sizeof(t_tabs));
	if (!tabs)
		return (0);
	tabs->next = NULL;
	tmp = (*shell)->next;
	while (tmp)
	{
		if (tmp->index == PIPE && tmp->next != NULL)
			tmp = tmp->next;
		ft_lstregroup_back(&tabs, tmp); // follow the path to the segfault
		while (tmp && tmp->next && tmp->index != PIPE)
			tmp = tmp->next;
		if (!tmp || !tmp->next)
			return (tabs);
	}
	return (tabs);
}

void	ft_split_pipes(t_shell **shell, char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i] == PIPE)
		{
			while (input[i + j] == PIPE)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], PIPE, j, 0));
		}
		else if (input[i])
		{
			while (input[i + j] && input[i + j] != PIPE)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], 0, j, 0));
		}
		else
			return ;
		i += j;
	}
}

t_shell	*ft_get_da_pipes(t_shell **shell)
{
	t_shell *tmp;
	t_shell *tmp2;
	t_shell *new;
	int		i;

	ft_print_lst(shell);

	new = malloc(sizeof(t_shell));
	if (!new)
		return (NULL);
	new->next = NULL;
	tmp = (*shell)->next; // error check?
	tmp2 = (*shell); // error check?
	while (tmp)
	{
		printf("before shell %s | address tmp %s\n", (*shell)->next->data, tmp->data);
		i = 0;
		if (tmp->index == CHARS)
		{
			while (tmp->data[i] != PIPE && tmp->data[i])
			{
				i++;
			}
			if (tmp->data[i] == PIPE)
			{
				ft_split_pipes(&new, tmp->data);
			}
			else
				ft_lstadd_back(&new, tmp->data);
		}
		else // otherwise, split it
			ft_lstadd_back(&new, tmp->data);
		printf("after shell %s | address tmp %s\n", (*shell)->next->data, tmp->data);
		tmp = tmp->next;
	}
	//printf("address shell %s | address tmp %s\n", (*shell)->next->data, tmp->data);

	*shell = tmp2;
	ft_print_lst(shell);
	free_lst(*shell); //--> does not work, I'm lost in translation
	return (new);
}
