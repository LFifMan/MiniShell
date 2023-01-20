
int	ft_look_for_dollar(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == DOLLAR)
			return (TRUE);
		i++;
	}
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
		j++;
	if ((data[i + j] == DOUBLEQUOTE || data[i + j] == 0) && envp[j] == '=')
		return (TRUE);
	return (FALSE);
}

int	ft_dollar_len(char *data, int start)
{
	int	len;

	len = 0;
	while (data[start] && data[start] != DOUBLEQUOTE && data[start] != PIPE)
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
	while (envp[start] && envp[start] != PIPE)
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
	size_dollar = ft_dollar_len(data, start_data);
	len = size_data - size_dollar + size_env;
	return (len);
}

char	*ft_malloc_cpy(char *data, char *envp, int size)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * size);
	if (!ret)
		exit (0); // TODO : deal with this error.
	while (data[i] && data[i] != DOLLAR)
	{
		ret[i] = data[i];
		i++;
	}
	while (envp[j] && envp[j] != '=')
		j++;
	j++;
	while (envp[j] && envp[j] != DOUBLEQUOTE && envp[j] != PIPE)
		ret[i++] = envp[j++];
	if (data[0] == DOUBLEQUOTE)
		ret[i++] = DOUBLEQUOTE;
	ret[i] = 0;
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
	return (ret);
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
	{
		start++;
	}
	end = start + 1;
	while (data[end] && (data[end] == 95 || (data[end] >= 'a' && data[end] <= 'z') || (data[end] >= 'A' && data[end] <= 'Z') || (data[end] >= '0' && data[end] <= '9')))
		end++;
	//printf("start = %d \n", end);
	size = ft_strlen(data) - end + start;
	ret = malloc(sizeof(char) * size + 1);
	size = 0;
	i = 0;
	while (data[i] && size < start)
	{
		ret[size] = data[i];
		i++;
		size++;
	}
	while (data[end])
	{
		ret[size] = data[end];
		end++;
		size++;

	}
	ret[size] = 0;
	return (ret);
}

void	ft_dollars(t_shell **shell, t_vars *vars)
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