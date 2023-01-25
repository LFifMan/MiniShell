/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:45:45 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/25 19:01:44 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize(t_shell **lst)
{
	t_shell	*tmp;
	int		i;

	tmp = (*lst)->next;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_lstadd_back(t_shell **lst, char *input, int index)
{
	t_shell	*tmp;
	t_shell	*curr;
	int		i;

	tmp = malloc(sizeof(t_shell));
	if (!tmp)
		return ;
	tmp->next = NULL;
	if (input[0] == DOUBLEQUOTE || input[0] == SINGLEQUOTE || input[0] == PIPE || input[0] == SPACE || input[0] == GREATER || input[0] == SMALLER) // create an index to know if the lst is a quotation or not
		tmp->index = input[0];
	else
		tmp->index = CHARS;
	i = 0;
	tmp->data = malloc(sizeof(char) * ft_strlen(input) + 1);
	if (!tmp->data)
		return ;
	while (input[i])
	{
		tmp->data[i] = input[i];
		i++;
	}
	tmp->data[i] = 0;
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = tmp;
	if (index == TRUE)
		free (input);

}

void	ft_lstregroup_back(	t_tabs **tabs, t_shell *input)
{
	t_tabs	*tmp;
	t_tabs	*curr;
	t_shell	*temp_remove;
	int		i;

	temp_remove  = input;
	tmp = malloc(sizeof(t_tabs));
	if (!tmp)
		return ;
	tmp->next = NULL;
	i = 0;
	tmp->cmds = malloc (sizeof(char*) *ft_lst_count_spaces(input) + 1);
	if (!tmp->cmds)
		return ;
	while (input)
	{
		if (input && input->next && input->index == SPACE)
		{
			input = input->next;
		}
		if (input && input->index == PIPE)
		{
			break ;
		}
		if (input && input->index == SPACE && !input->next)
		{
			break ;
		}
		if (input->index == DOUBLEQUOTE || input->index == SINGLEQUOTE)
		{
			tmp->cmds[i] = ft_strdup(ft_trim_quotations(input->data), TRUE);
		}
		else
		{
			tmp->cmds[i] = ft_strdup(ft_trim_quotations(input->data), FALSE);
		}
		input = input->next;
		while (input && input->index != SPACE && input->index != PIPE)
		{
			if (input->index == DOUBLEQUOTE || input->index == SINGLEQUOTE)
			{
				tmp->cmds[i] = ft_strjoin(tmp->cmds[i], ft_trim_quotations(input->data), TRUE);
			}
			else
			{
				tmp->cmds[i] = ft_strjoin(tmp->cmds[i], ft_trim_quotations(input->data), FALSE);
			}
			input = input->next;
		}
		i++;
	}
	tmp->cmds[i] = 0;
	curr = *tabs;
	while (tabs && (*tabs)->next != NULL)
	{
		(*tabs) = (*tabs)->next;
	}
	(*tabs)->next = tmp;
	(*tabs) = curr;
}
