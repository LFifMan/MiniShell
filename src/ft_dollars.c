#include "../includes/minishell.h"

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

int	ft_find(char *data, char *envp)
{
	int	i;

	i = 0;
	while (envp[i] == data[i])
		i++;
	if (!data[i])
		return (TRUE);
	return (FALSE);
}

int	ft_look_in_envp(char *data, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i] != DOLLAR)
		i++;
	while (data[i] && envp[j])
	{
		if (ft_find(&data[i + 1], envp[j]) == TRUE)
			return (j);
		j++;
	}
	return (-1);
}

int	ft_dollar_len(char *data, int start)
{
	int	len;

	len = 0;
	while (data[start] && data[start] != DOUBLEQUOTE && data[start] != PIPE)
		len++;
	return (len);
}

int	ft_env_len(char *envp, int start)
{
	int	len;

	len = 0;
	while (envp[start] && envp[start] != DOUBLEQUOTE && envp[start] != PIPE)
		len++;
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
	ret = malloc(sizeof(char) * size + 1);
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
	{
		ret[i + j] = envp[j];
		j++;
	}
	if (data[0] == DOUBLEQUOTE)
		ret[i + j++] = DOUBLEQUOTE;
	ret[i + j] = 0;
	return (ret);
}

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
	while (envp[start_envp] && envp[start_envp] == data[start_data + start_envp + 1])
		start_envp++;
	size_malloc = ft_size_malloc(data, envp, start_data, start_envp + 1);
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
		while (vars->envp[j])
		{
			if (tmp->index == DOUBLEQUOTE || tmp->index == CHARS)
			{
				if (ft_look_for_dollar(tmp->data) == TRUE)
				{
					if (ft_look_in_envp(tmp->data, vars->envp) >= 0)
						tmp->data = ft_replace(tmp->data, vars->envp[j]);
				}
			}
			j++;
		}
		tmp = tmp->next;
	}
}