#include "../includes/minishell.h"

void	ft_pipex(t_tabs *tabs, t_vars *vars)
{
	int		fd[2];
	pid_t	child;
	int		i;
	int		j;
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
			vars->redir_in = 0;
			vars->redir_out = 0;
			j = 0;
			while (tabs->redop[j])
			{
				if (ft_strcmp(tabs->redop[j], "<<") == TRUE)
				{
					char	*delimiter;					
					char	*input; // store the input from readline
					char	path[1024];
					int		fd;

					vars->redir_in = 1;
					delimiter = tabs->redop[j + 1];
					input = NULL;
					while (1)
					{
						input = readline("");
						if (strcmp(input, delimiter) == 0)
						{
							break;
						}
						// add input to history
						add_history(input);
					}
					// get the current working directory
					getcwd(path, sizeof(path));
					// concatenate the current working directory with the file name
					strcat(path, "/tempfile");

					// open the file for writing
					fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
					
					write(fd, input, strlen(input)); // write the input to the file
					close(fd);
					vars->in_fd = open("tempfile", O_RDONLY); // redirect input to the file
					dup2(vars->in_fd, 0);
					close(vars->in_fd);
					unlink("tempfile"); // remove the temporary file
					free(input);
				}
				else if (ft_strcmp(tabs->redop[j], ">>") == TRUE)
				{
					vars->redir_out = 1;
					vars->out_fd = open(tabs->redop[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
					dup2(vars->out_fd, 1);
					close(vars->out_fd);
				}
				else if (ft_strcmp(tabs->redop[j], "<") == TRUE)
				{
					vars->redir_in = 1;
					vars->in_fd = open(tabs->redop[j + 1], O_RDONLY);
					dup2(vars->in_fd, 0);
					close(vars->in_fd);
				}
				else if (ft_strcmp(tabs->redop[j], ">") == TRUE)
				{
					vars->redir_out = 1;
					vars->out_fd = open(tabs->redop[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
					dup2(vars->out_fd, 1);
					close(vars->out_fd);
				}
				j++;
			}
			if (i != 0 && vars->redir_in == 0)
				dup2(fd[0], 0);
			if (tabs->next && vars->redir_out == 0)
				dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			if (ft_builtins(tabs, vars, tabs->cmds[0]) == TRUE)
			{
				/*
				int t = 0;
				while (vars->envp[t])
				{
					printf("%s\n", vars->envp[t]);
					t++;
				}
				*/
				exit(1);
			}
			else
			{
				var = execve(tabs->cmds[0], tabs->cmds, vars->envp);

				while (tabs->paths[i] && var < 0)
				{
					var = execve(tabs->paths[i], tabs->cmds, vars->envp);
					i++;
				}
				write(1, "bash: ", ft_strlen("bash: "));
				write(1, tabs->cmds[0], ft_strlen(tabs->cmds[0]));
				write(1, ": command not found\n", ft_strlen(": command not found\n"));
				exit(1);

				//printf("bash: %s command not found\n", tabs->cmds[0]);//ft_errors(4, tabs);
			}
		}
		else
		{
			waitpid(child, &status, 0);

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
