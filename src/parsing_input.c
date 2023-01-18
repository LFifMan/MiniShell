/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:38:40 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/18 17:50:57 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/* PARSING LV 1: split quotes from unquotes */

/*
parse_quotation receives the input string starting at the next element, the size of the said element, and its type (index)
i.e. index
- 1 if ""
- 2 if ''
- 0 if both

it returns the final string of the new element and sends it to ft_lstadd_back
*/
char	*parse_quotation(char *input, int index, int size)
{
	int		i;
	int		j;
	char	*data;

	i = 0;
	j = 0;
	if(index == DOUBLEQUOTE)
	{
		data = malloc(sizeof(char) * size + 3);
		data[i] = DOUBLEQUOTE;
		while (i < size)
		{
			data[i + 1] = input[i];
			i++;
		}
		i++;
		data[i++] = DOUBLEQUOTE;
		data[i] = 0;
	}
	else if (index == SINGLEQUOTE)
	{
		data = malloc(sizeof(char) * size + 3);
		data[i] = SINGLEQUOTE;
		while (i < size)
		{
			data[i + 1] = input[i];
			i++;
		}
		i++;
		data[i++] = SINGLEQUOTE;
		data[i] = 0;
	}
	else if (index == SPACE)
	{
		data = malloc(sizeof(char) * size + 1);
		while (i < size)
		{
			data[i] = input[i];
			i++;
		}
		data[i] = 0;
	}
	else
	{
		data = malloc(sizeof(char) * size + 1);
		while (i < size)
		{
			data[i] = input[i];
			i++;
		}
		data[i] = 0;
	}
	return (data);
}

/*
parsing_input receives the lst and the input. it splits the input into chunks of quotes / unquotes
it returns 1 if one of the quotation mark is not closed
*/
int	parsing_input(t_shell **shell, char *input)
{
	int i;
	int j;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i] == DOUBLEQUOTE)
		{
			i++;
			while (input[i + j] != 0 && input[i + j] != DOUBLEQUOTE)
				j++;
			if (input[i + j] == 0) // error check if there is a missing quotation
				return (1);
			ft_lstadd_back(shell, parse_quotation(&input[i], DOUBLEQUOTE, j));
			i++;
		}
		else if (input[i] == SINGLEQUOTE)
		{
			i++;
			while (input[i + j] != 0 && input[i + j] != SINGLEQUOTE)
				j++;
			if (input[i + j] == 0) // error check if there is a missing quotation
				return (1);
			ft_lstadd_back(shell, parse_quotation(&input[i], SINGLEQUOTE, j));
			i++;
		}
		else
		{
			while (input[i + j] != 0 && input[i + j] != SINGLEQUOTE && input[i + j] != DOUBLEQUOTE)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], 0, j));
		}
		i += j;
	}
	return (0);

}

/* PARSING LV 2: keep quotation strings, split unquotes */

/*
split_not_quotation splits unquotes, ignores all spaces, and add a new element to the list for each
*/
void	split_not_quotation(t_shell **shell, char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i] == SPACE)
		{
			while (input[i + j] == SPACE)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], SPACE, j));
		}
		else if (input[i] != 0)
		{
			while (input[i + j] != 0 && input[i + j] != SPACE)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], 0, j));
		}
		else
			return ;
		i += j;
	}
}


/*
parsing_not_quotation is pasring level two. It creates a new lst, splits unquoted strings and keeps strings in quotations. 
Note: it makes a "pointer being freed was not allocated" sometimes...
*/
t_shell	*parsing_not_quotation(t_shell **shell)
{
	t_shell *tmp;
	t_shell *new;

	new = malloc(sizeof(t_shell));
	new->next = NULL;
	tmp = (*shell)->next; // error check?
	if (!new)
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->index == 1) // if the data is a quotation string, just keep it as it is
			ft_lstadd_back(&new, tmp->data);
		else // otherwise, split it
			split_not_quotation(&new, tmp->data);
		tmp = tmp->next;
	}
	//free_lst(*shell); --> does not work, I'm lost in translation
	return (new);
}
