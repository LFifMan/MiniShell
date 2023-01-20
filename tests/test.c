
void	ft_child_process(t_tabs *tabs, int *end, t_vars vars)
{
	int		i;
	int		var;

	var = -1;
	/*
	dup2(tabs.fd_in, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	if (tabs.fd_in < 0 || end[1] < 0)
		ft_errors(3, tabs);
	close(tabs.fd_in);
	*/
	close(end[0]);
	i = 0;
	while (tabs->paths[i] && var < 0)
	{
		var = execve(tabs->paths[i], tabs->cmds, vars.envp);
		i++;
	}
	//ft_errors(3, tabs);
}

void	ft_parent_process(t_tabs *tabs, int *end, t_vars vars)
{
	int		i;
	int		var;

	var = -1;
	/*
	dup2(tabs.fd_out, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	if (tabs.fd_out < 0 || end[0] < 0)
		ft_errors(3, tabs);
	close(tabs.fd_out);
	*/
	close(end[1]);
	i = 0;
	while (tabs->paths[i] && var < 0)
	{
		var = execve(tabs->next->paths[i], tabs->next->cmds, vars.envp);
		i++;
	}
	//ft_errors(3, tabs);
}

void	ft_pipex(t_tabs **tmp, t_vars vars)
{
	int		end[2];
	pid_t	child;
	int		status;
	t_tabs	*tabs;

	tabs = (*tmp)->next;
	pipe(end);
	child = fork();
	if (child < 0)
		printf("la sauce"); //ft_errors(3, tabs);
	if (child == 0)
		ft_child_process(tabs, end, vars);
	else
		ft_parent_process(tabs, end, vars);
	waitpid(child, &status, 0);
}
