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
	if (!data[i] && envp[i] == '=') // added this condition to avoid shorter $NAME than variable name, eg USE instead of USER
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
	//printf("dollar = %c\n", data[i]);
	if (ft_find(&data[i], envp) == TRUE)
	{
		//printf("yope = %d\n", j);
		return (j);
	}
	//printf("nope = %c\n", data[i]);
	return (-1);
}

int	ft_dollar_len(char *data, int start)
{
	int	len;

	len = 0;
	while (data[start] && data[start] != DOUBLEQUOTE && data[start] != PIPE)
	{
		start++;
		len++;
	}
	return (len);
}

int	ft_env_len(char *envp, int start)
{
	int	len;

	len = 0;
	while (envp[start] && envp[start] != DOUBLEQUOTE && envp[start] != PIPE)
	{
		len++;
		start++;
	}
	//printf("envp %s and start_envp %d\n", envp, len);
	return (len);
}

int	ft_size_malloc(char *data, char *envp, int start_data, int start_envp)
{
	int	size_data;
	int	size_env;
	int	size_dollar;
	int	len;

	size_data = ft_strlen(data) - 1; // j'ai ajoute - 1, pas sur de oim
	size_env = ft_env_len(envp, start_envp);
	size_dollar = ft_dollar_len(data, start_data);
	len = size_data - size_dollar + size_env;
	//printf("size_data %d and size_env %d and size_dollar %d and len %d\n", size_data, size_env, size_dollar, len);
	return (len);
}

char	*ft_malloc_cpy(char *data, char *envp, int size)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	//printf("size_data %d", size + 1);
	ret = malloc(sizeof(char) * size + 1);
	if (!ret)
		exit (0); // TODO : deal with this error.
	//printf("\n\n\ndata tot %s\n", data);
	while (data[i] && data[i] != DOLLAR)
	{
		ret[i] = data[i];
		//printf("data now %c\n", ret[i]);
		i++;
	}

	while (envp[j] && envp[j] != '=')
		j++;
	j++;
	while (envp[j] && envp[j] != DOUBLEQUOTE && envp[j] != PIPE)
	{
		ret[i] = envp[j];
		j++;
		i++;
	}
	if (data[0] == DOUBLEQUOTE)
	{
		ret[i] = DOUBLEQUOTE;
		i++;
	}
	ret[i] = 0;
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