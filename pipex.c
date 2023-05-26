#include "pipex.h"

int	main(int ac, char **av)
{
	int	i;
	int	fdin;
	int	fdout;
	int	pipefd[2];
	int	tmp;
	int	pid;
	char	**args;

	if (access(av[1], R_OK))
	{
		perror(av[1]);
		exit(1);
	}
	fdin = open(av[1], O_RDONLY);
	fdout = open(av[ac - 1], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if (ac < 4)
	{
		write(STDERR_FILENO, "Usage: ", 7);
		write(STDERR_FILENO, av[0], ft_strlen_chr(av[0], '\0'));
		write(STDERR_FILENO, "infile cmd1 cmd2 ...\n", 21);
		exit(1);
	}
	i = 0;
	tmp = fdin;
	while (++i < ac - 1)
	{
		if (i != ac - 2 && (pipe(pipefd) < 0))
		{
			perror("pipe");
			exit(1);
		}
		if ((pid = fork()) < 0)
		{
			perror("fork");
			exit(1);
		}
		if (!pid)
		{
			dup2(tmp, STDIN_FILENO);
			if (i != ac - 2)
				dup2(pipefd[1], STDOUT_FILENO);
			if (i == ac - 2)
				dup2(fdout, STDOUT_FILENO);
			close(fdout);
			close(tmp);
			close(pipefd[0]);
			close(pipefd[1]);
			args = ft_split(av[i], ' ');
			execvp(args[0], args);
		}
		tmp = dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
	}
	close(fdin);
	close(fdout);
}
