/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:45:45 by mstockli          #+#    #+#             */
/*   Updated: 2023/02/06 22:54:09 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	ft_add_index(char c)
{
	if (c == DOUBLEQUOTE || c == SINGLEQUOTE || c == PIPE || c == SPACE || c == GREAT || c == SMALL) // todo: change DQ & SQ
		return (c);
	return (CHARS);
}

char	*ft_add_data(char *input)
{
	int		i;
	char	*data;

	i = 0;
	data = malloc (sizeof(char) * ft_strlen(input) + 1);
	if (!data)
		exit (EXIT_FAILURE);
	while (input[i])
	{
		data[i] = input[i];
		i++;
	}
	data[i] = 0;
	return (data);
}

void	ft_lst_new(t_shell **lst, char *input, int index)
{
	t_shell	*new;
	t_shell	*curr;

	new = malloc(sizeof(t_shell));
	if (!new)
		exit (EXIT_FAILURE);
	new->next = NULL;
	new->index = (int)ft_add_index(input[0]);
	new->data = ft_add_data(input);
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	if (index == TRUE)
		free (input);
}

void	ft_lstregroup_back(	t_tabs **tabs, t_shell *input)
{
	t_tabs	*tmp;
	t_tabs	*curr;
	int		i;

	tmp = malloc(sizeof(t_tabs));
	if (!tmp)
		exit (EXIT_FAILURE);
	tmp->next = NULL;
	i = 0;
	tmp->cmds = malloc (sizeof(char *) * (ft_lst_count_spaces(input) + 1));
	if (!tmp->cmds)
		exit (EXIT_FAILURE);
	while (input)
	{
		if (input && input->next && input->index == SPACE)
			input = input->next;
		if (input && input->index == PIPE)
			break ;
		if (input && input->index == SPACE && !input->next)
			break ;
		if (input->index == DOUBLEQUOTE || input->index == SINGLEQUOTE)
			tmp->cmds[i] = ft_strdup(ft_trim_quotations(input->data), TRUE);
		else
			tmp->cmds[i] = ft_strdup(ft_trim_quotations(input->data), FALSE);
		input = input->next;
		while (input && input->index != SPACE && input->index != PIPE)
		{
			if (input->index == DOUBLEQUOTE || input->index == SINGLEQUOTE)
				tmp->cmds[i] = ft_strjoin(tmp->cmds[i], ft_trim_quotations(input->data), TRUE);
			else
				tmp->cmds[i] = ft_strjoin(tmp->cmds[i], ft_trim_quotations(input->data), FALSE);
			input = input->next;
		}
		i++;
	}
	tmp->cmds[i] = 0;
	curr = *tabs;
	while (tabs && (*tabs)->next != NULL)
		(*tabs) = (*tabs)->next;
	(*tabs)->next = tmp;
	(*tabs) = curr;
}
