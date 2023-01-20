/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:45:45 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/20 03:49:21 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_lst(t_shell *lst)
{
	t_shell	*tmp;
	t_shell	*end;

	end = lst;
	lst = lst->next;
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->data);
		//free(tmp);
	}
	lst = end;
	lst->next = NULL;
	return (0);
}

int	free_lst_tabs(t_tabs *lst)
{
	t_tabs	*tmp;
	t_tabs	*end;
	int		i;

	end = lst;
	lst = lst->next;
	while (lst != NULL)
	{
		i = 0;
		tmp = lst;
		lst = lst->next;
		while (tmp->cmds[i])
		{
			free(tmp->cmds[i]);
			i++;
		}
		i = 0;
		while (tmp->paths[i])
		{
			free(tmp->paths[i]);
			i++;
		}
		//free(tmp);
	}
	lst = end;
	lst->next = NULL;
	return (0);
}
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

void	ft_lstadd_back(t_shell **lst, char *input)
{
	t_shell	*tmp;
	t_shell	*curr;
	int		i;

	tmp = malloc(sizeof(t_shell));
	if (!tmp)
		return ;
	tmp->next = NULL;
	if (input[0] == DOUBLEQUOTE || input[0] == SINGLEQUOTE || input[0] == PIPE || input[0] == SPACE) // create an index to know if the lst is a quotation or not
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
	free (input);
}

void	ft_lstregroup_back(	t_tabs **tabs, t_shell *input)
{
	t_tabs	*tmp;
	t_tabs	*curr;
	int		i;

	tmp = malloc(sizeof(t_tabs));
	if (!tmp)
		return ;
	tmp->next = NULL;
	i = 0;
	tmp->cmds = malloc (sizeof(char*) *ft_lst_count_spaces(input) + 1);
	//e = %d\n", ft_lst_count_spaces(input) + 1);
	if (!tmp->cmds)
		return ;
	while (input)
	{
		if (input && input->next && input->index == SPACE)
			input = input->next;
		if (input && input->index == PIPE)
			break ;
		tmp->cmds[i] = ft_strdup(input->data);
		input = input->next;
		while (input && input->index != SPACE && input->index != PIPE)
		{
			tmp->cmds[i] = ft_strjoin(tmp->cmds[i], ft_trim_quotations(input->data));
			input = input->next;
		}
		i++;
	}
	tmp->cmds[i] = 0;
	curr = *tabs;
	while (curr->next != NULL)
		curr = curr->next;
	//write (1, "hella\n", 6);
	curr->next = tmp;

}