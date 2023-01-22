#include "../includes/minishell.h"

void	ft_pipex(t_tabs *tabs, t_vars *vars)
{
	int		fd[2];
	pid_t	child;
	int		i;
	int		j;
	int		status;
	int		var;

	int in_fd, out_fd; //new
	int input_redirection, output_redirection;


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
			input_redirection = 0;
			output_redirection = 0;
			j = 0;
			while (tabs->redop[j])
			{
				if (ft_strcmp(tabs->redop[j], "<<") == TRUE) // not goot
				{
					input_redirection = 1;
					in_fd = open(tabs->redop[j + 1], O_RDONLY);
					dup2(in_fd, 0);
					close(in_fd);
				}
				else if (ft_strcmp(tabs->redop[j], ">>") == TRUE)
				{
					output_redirection = 1;
					out_fd = open(tabs->redop[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
					dup2(out_fd, 1);
					close(out_fd);
				}
				else if (ft_strcmp(tabs->redop[j], "<") == TRUE)
				{
					input_redirection = 1;
					in_fd = open(tabs->redop[j + 1], O_RDONLY);
					dup2(in_fd, 0);
					close(in_fd);
				}
				else if (ft_strcmp(tabs->redop[j], ">") == TRUE)
				{
					output_redirection = 1;
					out_fd = open(tabs->redop[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
					dup2(out_fd, 1);
					close(out_fd);
				}
				j++;
			}
			if (i != 0 && input_redirection == 0)
				dup2(fd[0], 0);
			if (tabs->next != NULL && output_redirection == 0)
				dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			if (ft_builtins(tabs, vars, tabs->cmds[0]) == TRUE)
				exit(1);
			else
			{
				while (tabs->paths[i] && var < 0)
				{
					var = execve(tabs->paths[i], tabs->cmds, vars->envp);
					i++;
				}
				write(1, "bash: ", ft_strlen("bash: "));
				write(1, tabs->cmds[0], ft_strlen(tabs->cmds[0]));
				write(1, " command not found\n", ft_strlen(": command not found\n"));
				exit(1);

				//printf("bash: %s command not found\n", tabs->cmds[0]);//ft_errors(4, tabs);
			}
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
