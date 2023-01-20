
char	*ft_replace(char *data, char *envp)
{
	int		start_data;
	int		start_envp;
	int		size_malloc;
	char	*ret;

	start_data = 0;
	start_envp = 0;
	while (data[start_data] && data[start_data] != DOLLAR)
		start_data++;
	while (envp[start_envp] != '=')
		start_envp++;
	start_envp++;
	start_data++;
	//printf("data %s and envp %s and start_data %d and start_envp %d\n", data, envp, start_data, start_envp);
	size_malloc = ft_size_malloc(data, envp, start_data, start_envp);
	ret = ft_malloc_cpy(data, envp, size_malloc + 1);
	return (ret);
}

void	ft_dollars(t_shell **shell, t_vars *vars)
{
	t_shell	*tmp;
	int		j;

	tmp = (*shell)->next;
	while (tmp)
	{
		j = 0;
		if (tmp->index == DOUBLEQUOTE || tmp->index == CHARS)
		{
			while (vars->envp[j])
			{
				//printf("envp[%d] = %s\n", j, vars->envp[j]);
				if (ft_look_for_dollar(tmp->data) == TRUE)
				{
					if (ft_look_in_envp(tmp->data, vars->envp[j]) >= 0) // else: error TODO
					{
						tmp->data = ft_replace(tmp->data, vars->envp[j]);
						break ;
					}
				}
				j++;
			}
		}
		tmp = tmp->next;
	}
}