#include "../includes/minishell.h"

#define BUFFER_SIZE 1024
char *get_next_line(char *delimiter)
{
	char *line = NULL;
	char buffer[BUFFER_SIZE];
	ssize_t read_bytes;
	int i = 0;
	int j = 0;
	while ((read_bytes = read(STDIN_FILENO, buffer, sizeof buffer)) > 0)
	{
		for (j = 0; j < read_bytes; j++)
		{
			if (buffer[j] == '\n')
			{
				buffer[j] = '\0';
				if (ft_strcmp(buffer, delimiter) == 0)
					return line;
				if (line == NULL)
					line = ft_strdup(buffer, FALSE);
				else
					line = ft_strjoin(line, buffer, FALSE);
				i = 0;
				continue;
			}
			i++;
		}
	}
	return line;
}


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
				if (ft_strcmp(tabs->redop[j], "<<") == TRUE)
				{
					char	*delimiter;					
					char	*input; // store the input from readline
					// variable to store the file descriptor
					int fd;

					input_redirection = 1;
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
					char path[1024];
					getcwd(path, sizeof(path));
					// concatenate the current working directory with the file name
					strcat(path, "/tempfile");

					// open the file for writing
					fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
					
					write(fd, input, strlen(input)); // write the input to the file
					close(fd);
					in_fd = open("tempfile", O_RDONLY); // redirect input to the file
					dup2(in_fd, 0);
					close(in_fd);
					unlink("tempfile"); // remove the temporary file
					free(input);
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
			if (tabs->next && output_redirection == 0)
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
