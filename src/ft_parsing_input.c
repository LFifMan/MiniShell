/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:38:40 by mstockli          #+#    #+#             */
/*   Updated: 2023/01/18 17:59:11 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//tour de controle
//{
//	parsing1(lst); //quotes
//	parsing2(lst); //spaces
//	parsing2.1(lst); //$
//	parsing3(lst); //regroup
//	parsing4(lst); //pipes
//	parsing4
//};


/*
lst de tabs

- vars→args =
    - separer chaque espace(s) en nouveau string
    - separer les pipes en nouvelle lst
    - transformer chaque $XXX en vars
- vars→path =
    - strjoin de chaque path avec vars→args[0]
    - si path= n existe pas, remplacer par /bin et /user/bin
*/
//void	ft_regroup(t_shell **shell)
//{
//	t_shell	*tmp;
//
//	tmp = (*shell)->next;
//	while (tmp)
//	{
//		/*look if
//	}
//}

/*
PARSING LV 1: split quotes from unquotes
parse_quotation receives the input string starting at the next element, the size of the said element, and its type (index)
i.e. index
- 1 if ""
- 2 if ''
- 0 if both

it returns the final string of the new element and sends it to ft_lstadd_back
*/
char	*parse_quotation(char *input, char index, int size, int i)
{
	char	*data;

	if (index == DOUBLEQUOTE || index == SINGLEQUOTE)
	{
		data = malloc(sizeof(char) * size + 3);
		data[i] = index;
		while (i < size)
		{
			data[i + 1] = input[i];
			i++;
		}
		data[++i] = index;
		data[++i] = 0;
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
	int		i;
	int		j;
	char	type;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i] == DOUBLEQUOTE || input[i] == SINGLEQUOTE)
		{
			type = input[i++];
			while (input[i + j] && input[i + j] != type)
				j++;
			if (!input[i + j]) // error check if there is a missing quotation
				return (FALSE);
			ft_lstadd_back(shell, parse_quotation(&input[i], type, j, 0));
			i++;
		}
		else
		{
			while (input[i + j] && input[i + j] != SINGLEQUOTE && input[i + j] != DOUBLEQUOTE)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], 0, j, 0));
		}
		i += j;
	}
	return (TRUE);
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
			ft_lstadd_back(shell, parse_quotation(&input[i], SPACE, j, 0));
		}
		else if (input[i])
		{
			while (input[i + j] && input[i + j] != SPACE)
				j++;
			ft_lstadd_back(shell, parse_quotation(&input[i], 0, j, 0));
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
	if (!new)
		return (NULL);
	new->next = NULL;
	tmp = (*shell)->next; // error check?
	while (tmp)
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
