#include "../includes/minishell.h"

int	ft_look_for_dollar(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == DOLLAR)
			if (data[i + 1] != SPACE && data[i + 1] != 0)
				return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_check_allowed_char(char c, int pos)
{
	if (c >= 'a' && c <= 'z')
		return (TRUE);
	if (c >= 'A' && c <= 'Z')
		return (TRUE);
	if (c == '_' || (c >= '0' && c <= '9' && pos != 1))
		return (TRUE);
	return (FALSE);
}

int	ft_look_in_envp(char *data, char *envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i] != DOLLAR)
		i++;
	i++;
	while (data[i + j] && envp[j] != '=' && data[i + j] == envp[j])
	{
		if (ft_check_allowed_char(data[i + j], i + j) == FALSE)
			break ;
		j++;
	}
	if (envp[j] == '=' && ft_check_allowed_char(data[i + j], i + j) == FALSE)
		return (TRUE);
	return (FALSE);
}

int	ft_dollar_len(char *data, int start)
{
	int	len;

	len = 0;
	while (data[start] && ft_check_allowed_char(data[start], start) == TRUE)
	{
		start++;
		len ++;
	}
	return (len);
}

int	ft_env_len(char *envp, int start)
{
	int	len;

	len = 0;
	while (envp[start])
	{
		start++;
		len++;
	}
	return (len);
}

int	ft_size_malloc(char *data, char *envp, int start_data, int start_envp)
{
	int	size_data;
	int	size_env;
	int	size_dollar;
	int	len;

	size_data = ft_strlen(data);
	size_env = ft_env_len(envp, start_envp);
	size_dollar = ft_dollar_len(data, start_data - 1);
	len = size_data - size_dollar + size_env;
	return (len);
}

char	*ft_malloc_cpy(char *data, char *envp, int size)
{
	int		iret;
	int		ienvp;
	int		idata;
	char	*ret;

	iret = 0;
	ret = malloc(sizeof(char) * size + 1);
	if (!ret)
		exit (EXIT_FAILURE);
	while (data[iret] && data[iret] != DOLLAR)
	{
		ret[iret] = data[iret];
		iret++;
	}
	ienvp = ft_dollar_len(data, iret + 1) + 1;
	idata = ienvp + iret;
	while (envp[ienvp])
	{
		ret[iret] = envp[ienvp];
		iret++;
		ienvp++;
	}
	while (data[idata])
	{
		ret[iret] = data[idata];
		iret++;
		ienvp++;
	}
	ret[iret] = 0;
	return (ret);
}

char	*ft_replace(char *data, char *envp)
{
	int		idata;
	int		ienvp;
	int		size_malloc;
	char	*ret;

	idata = 0;
	ienvp = 0;
	while (data[idata] && data[idata] != DOLLAR)
		idata++;
	idata++;
	while (envp[ienvp] == data[idata + ienvp])
		ienvp++;
	ienvp++;
	size_malloc = ft_size_malloc(data, envp, idata, ienvp);
	ret = ft_malloc_cpy(data, envp, size_malloc);
	free(data);
	return (ret);
}

int	ft_iteration(char c)
{
	if ((c == 95 || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| (c >= '0' && c <= '9')))
		return (TRUE);
	return (FALSE);
}

char	*ft_remove_dollar(char *data)
{
	char	*ret;
	int		start;
	int		end;
	int		size;
	int		i;

	start = 0;
	while (data[start] && data[start] != DOLLAR)
		start++;
	end = start + 1;
	while (data[end] && ft_iteration(data[end]) == TRUE)
		end++;
	size = (int)ft_strlen(data) - end + start;
	ret = malloc(sizeof(char) * size + 1);
	if (!ret)
		exit (EXIT_FAILURE);
	size = 0;
	i = 0;
	while (data[i] && size < start)
		ret[size++] = data[i++];
	while (data[end])
		ret[size++] = data[end++];
	free(data);
	ret[size] = 0;
	return (ret);
}

void	parsing_dollars(t_shell **shell, t_vars *vars)
{
	t_shell	*tmp;
	int		j;
	int		index;

	tmp = (*shell)->next;
	while (tmp)
	{
		if (tmp->index == DOUBLEQUOTE || tmp->index == CHARS)
		{
			while (ft_look_for_dollar(tmp->data) == TRUE)
			{
				j = 0;
				index = FALSE;
				while (vars->envp[j])
				{
					if (ft_look_in_envp(tmp->data, vars->envp[j]) == TRUE)
					{
						tmp->data = ft_replace(tmp->data, vars->envp[j]);
						index = TRUE;
						break ;
					}
					j++;
				}
				if (index == FALSE)
					tmp->data = ft_remove_dollar(tmp->data);
			}
		}
		tmp = tmp->next;
	}
}
