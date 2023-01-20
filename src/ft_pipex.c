#include "../includes/minishell.h"

void	ft_pipex(t_tabs *tabs, t_vars vars)
{
	int		fd[2];
	pid_t	child;
	int		i;
	int		status;
	int		var;

	var = -1;
	i = 0;
	while (tabs)
	{
		pipe(fd);
		child = fork();
		if (child < 0)
			printf("la sauce"); //ft_errors(3, tabs);
		if (child == 0)
		{
			if (i != 0)
				dup2(fd[0], 0);
			if (tabs->next != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			while (tabs->paths[i] && var < 0)
			{
				var = execve(tabs->paths[i], tabs->cmds, vars.envp);
				i++;
			}
			printf("bash: %s command not found\n", tabs->cmds[0]);//ft_errors(4, tabs);
		}
		else
		{
			if (i != 0)
				close(fd[0]);
			if (tabs->next != NULL)
				close(fd[1]);
		}
		tabs = tabs->next;
		i++;
	}
	while (i--)
		wait(&status);
}
